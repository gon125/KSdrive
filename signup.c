#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

struct client_if{
	char id[100];
	char pswd[100];
};

void sign_up(); //sign up
int check(char*); //check id already exist 
int log_in(); //log in


void sign_up(){
	int ch=0;
	int fd;
	int flag;
	char* fname="client.txt";
	char* id="bbbb";
	char* pw="password";
	FILE* f;
    struct client_if client;
	/*
	get id pswd
	*/
	
	if(check(id)==1)exit(0); // check id already exist 

	strcpy(client.id,id); // input id pw
	strcpy(client.pswd,pw);

	//write file
	if ((fd=open(fname,O_RDWR|O_CREAT,0644))==-1){
		printf("fopen err"); exit(0);
	}
	if((flag=fcntl(fd,F_GETFL))==-1){
		perror("fcntlfailed");
		exit(1);
	}
	flag |=O_APPEND;
	if ((fcntl(fd, F_SETFL, flag)) == -1) {
	    perror("fcntl failed");
	    exit(1);
	}
	write(fd,(struct client_if*)&client,sizeof(client));

	close(fd);
}

int check(char* id){//check id already exist -> exist 1 : not 0
	int ch=-1;
	struct client_if client;
	FILE* f;
	char* fname="client.txt";
	if ((f=fopen(fname,"r"))==NULL){
		if((f=fopen(fname,"w"))==NULL){
			return -1;
		}
	}
	while(!feof(f)){
		if (1 != fread(&client,sizeof(struct client_if),1,f)) {
			perror("");
			exit(1);	
		}
		if(!strcmp(client.id,id)){
			printf("이미 있는 아이디 입니다.\n");
			ch=1;
			break;
		}
	}
	fclose(f);
	return ch;
}

int log_in(){
	char* fname="client.txt";
	char* id;
	char* pswd;
	FILE* f;
	int c,i=0;
    struct client_if client,client2;
	
	/*
	get id pswd
	*/
	
	if ((f=fopen(fname,"r"))==NULL){
		printf("fopen err"); exit(0);
	}
	while(!feof(f)){
		if (1 != fread(&client,sizeof(struct client_if),1,f)) {
			perror("");
			exit(1);	
		}
		if (!strcmp(id,client.id) && !strcmp(pswd,client.pswd)){
			fclose(f);
			return 1;	
		}
	}
	printf("로그인 실패\n");
	fclose(f);
	return -1;
}
void main(){
	sign_up();
	log_in();
}
/*
void do_cat(char* f, int fd){
	char* extension = file_type(f);
	char* type = "text/plain";
	FILE* fpsock,*fpfile;
	int c;
	int bytes = 0;

	if(strcmp(extension,"html")==0) type = "tex/html";
	else if(strcmp(extension, "gif")==0) type = "image/gif";
	else if(strcmp(extension, "jpg")==0) type = "image/jpg";
	else if(strcmp(extension, "jpeg")==0) type = "image/jpeg";

	fpsock = fdopen(fd,"w");
	fpfile = fopen(fd,"r");
	if(fpsock != NULL&& fpfile!=NULL){
		bytes = http_reply(fd,&fpsock,200,"OK",type,NULL);
		while((c=getc(fpfile))!=EOF){
			putc(c,fpsock);
			bytes++;
		}
		fclose(fpsock);
		fclose(fpfile);
	}
	server_bytes_sent +=bytes;
}*/
