#include "socklib.h"
#include <stdlib.h>
#include <pthread.h>
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) {perror(msg); exit(1);}

int server_requests;
time_t server_started;
int server_bytes_sent;

void* handle_call(void* fdptr);
void setup(pthread_attr_t* attrp);

void process_rq(char request[], int fd) {
	if (fork() == 0) {
		dup2(fd, 1);
		close(fd);
		execlp("date", "date", NULL);
		oops("execlp date");
	}
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
	FILE* fpin;
	char request[BUFSIZ];
	int fd;

	fd = *(int*)fdptr;
	free(fdptr);
	
	fpin = fdopen(fd, "r");
	//fgets(request, BUFSIZ, fpin);
	strcpy(request,"hello");
	printf("got a call on %d: request = %s",fd ,request);

	process_rq(request, fd);
	fclose(fpin);

	return NULL;
}
