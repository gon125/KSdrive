#include "socklib.h"
#define oops(msg) {perror(msg);exit(1);}
#define MAX_STRING 100

void prompt(int type) {
    
    switch (type) {
        case SIGNUP:
            break;

        case LOGIN:
            break;

        case LOGOUT:
            break;

        case SAVE:
            break;

        case LOAD:
            break;

        case LS:
            break;

        case DELETE:
            break;

        case DEFAULT:
            printf("")
            break;
            
        default:
            printf("TRY AGAIN! YOU'VE SELECTETD : %d\n", type);
            break;
    }
    return;
}

char* getUserInput() {
    
}

void talk_with_server(int fd) {
	char buf[BUFSIZ];
    buf[0] = '1';
    buf[1] = '\0';
	int n;
    char input[MAX_STRING];
    // quit value
    int quit = 0;
    //while (!quit) {
    //    prompt();
    //    input = getUserInput();
        
    //}
	n = write(fd, buf, BUFSIZ);
	write(1, buf, n);
    n = read(fd, buf, BUFSIZ);
    write(1, buf, n);
}

int main(int argc, char* argv[]) {
	int fd;

	fd = connect_to_server(argv[1], 13000);
	if (fd == -1)	exit(1);
	talk_with_server(fd);
	close(fd);
}

