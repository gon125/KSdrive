#include "socklib.h"
#define oops(msg) {perror(msg);exit(1);}


void talk_with_server(int fd) {
	char buf[LEN];
	int n;
	n = read(fd, buf, LEN);
	write(1, buf, n);
}

int main(int argc, char* argv[]) {
	int fd;

	fd = connect_to_server(host, port);
	if (fd == -1)	exit(1);
	talk_with_server(fd);
	close(fd);
}

