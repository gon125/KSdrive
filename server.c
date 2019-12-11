#include "socklib.h"
#include <stdlib.h>
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) {perror(msg); exit(1);}

void process_request(int fd) {
	if (fork() == 0) {
		dup2(fd, 1);
		close(fd);
		execlp("date", "date", NULL);
		oops("execlp date");
	}
}

int main(int argc, char* argv[]) {
	int sock, fd;

	if((sock = make_server_socket(PORTNUM)) == -1)
		oops("make_server_socket");
	
	while (1) {
		fd = accept(sock, NULL, NULL);
		if (fd == -1) break;
		process_request(fd);
		close(fd);
	}
}
