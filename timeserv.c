#include "socklib.h"
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

void child_waiter(int signum) {
	while (waitpid(-1, NULL, WNOHANG) > 0) ;
}

int main(int argc, char* argv[]) {
	int sock, fd;

	signal(SIGCHLD, child_waiter);
	if((sock = make_server_socket(port)) == -1)
		oops("make_server_socket");
	
	while (1) {
		fd = accept(sock, NULL, NULL);
		if (fd == -1) break;
		process_request(fd);
		close(fd);
	}
}
