#include "socklib.h"
#include "serverlib.h"
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) {perror(msg); exit(1);}

int server_requests;
time_t server_started;
int server_bytes_sent;

void* handle_call(void* fdptr);
void setup(pthread_attr_t* attrp);

int process_rq(int fd) {
 	char id[1000], pwd[1000], fname[1000], buf[1000];	
	FILE* fin;
	FILE* fout;
	int rq = -1;

	FILE* f;
	int c = 0, i = 0;
	char str[1000];

	while(1){
		fin = fdopen(dup(fd), "r");
		fout = fdopen(dup(fd), "w");

		fscanf(fin, "%d",&rq);

		printf("got a call on %d: request = %d\n",fd ,rq);
		printf("%d\n",rq);
		fflush(stdout);

		switch(rq){
			case SIGNUP :
				fscanf(fin, "%s %s",id, pwd);
				getc(fin);
				
				printf("%s %s\n",id ,pwd);
				
				if(sign_up(id,pwd) == 0){
					fprintf(fout, "%d", 0); // sign up failed 같은 아이디 존재
				}
				else{
					fprintf(fout, "%d",1); // sign up success
				}
				break;
			case LOGIN :
				
				fscanf(fin, "%s %s",id, pwd);
				getc(fin);
				printf("%s %s\n",id ,pwd);
				if(log_in(id, pwd) == 0){
					fprintf(fout, "%d", 0);
				}
				else{
					fprintf(fout, "%d",1);
				}
				break;
			case LOGOUT :
				fprintf(fout, "%d",1);
				server_requests--;
				fclose(fout);
				fclose(fin);
				return 0;
				break;
			case LS:
				break;
			case LOAD:

				fscanf(fin,"%s",fname);
				printf("%s",fname);
				c=getc(fin);
				putc(c,stdout);
				fflush(stdout);
				sprintf(str,"./%s/%s",id,fname);

				if((f = fopen(str,"r"))==NULL){
					fprintf(fout, "%d",0); // dir에 파일이 존재하지 않을 때
					printf("야\n");
					fflush(stdout);
					break;
				}else {
					fprintf(fout, "%d",1); // dir에 파일이 존재할 때
					printf("임마\n");
					fflush(stdout);
				} 
				printf("%s\n",str);
				fflush(stdout);
				
				if(fout != NULL && f != NULL){
					while((c=getc(f))!=EOF){
						putc(c,fout);
						putc(c,stdout);
					}
				}
				
				fclose(f);
				break;
			case SAVE:
				fscanf(fin,"%s",fname);
				getc(fin);
				sprintf(str,"./%s/%s",id,fname);
				
				if((f = fopen(str,"w"))==NULL){
					perror("save fopen");
					exit(1);
				}
				printf("%s\n",str);

				if(fin != NULL && f != NULL){
					while(c=getc(fin)){
						if (c == '\r') {
							if ((c =getc(fin)) == '\n') {
								break;
							}
						}
						putc(c,f);
						fflush(f);
					}
				}

				fclose(f);
				fprintf(fout, "%d",1);
				break;
			case DELETE:
				break;
		}
		fprintf(fout,"\r\n");
		fflush(fout);
		fclose(fout);


		fclose(fin);
	}
	return 1;
}

int main(int argc, char* argv[]) {
	int sock, fd;
	int *fdptr;
	pthread_t worker;
	pthread_attr_t attr;

	if((sock = make_server_socket(PORTNUM)) == -1)
		oops("make_server_socket");
	
	setup(&attr);
	while (1) {
		fd = accept(sock, NULL, NULL);
		server_requests++;
		
		if (fd == -1) break;
		
		fdptr = malloc(sizeof(int));
		*fdptr = fd;
		printf("server requests %d\n",server_requests);
		pthread_create(&worker, &attr, handle_call, fdptr);

	}
}

void setup(pthread_attr_t* attrp)
{
	pthread_attr_init(attrp);
	pthread_attr_setdetachstate(attrp, PTHREAD_CREATE_DETACHED);

	time(&server_started);
	server_requests = 0;
	server_bytes_sent = 0;
}

void* handle_call(void* fdptr)
{
	int fd;
	
	fd = *(int*)fdptr;
	free(fdptr);
	
	process_rq(fd);
	
	return NULL;
}
