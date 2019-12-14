#include "socklib.h"
#include <stdio.h>
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
            printf("CHOOSE MENU:\n");
            printf("1. Login\t2. SignUp\n");
            break;
        case MENU:
            printf("CHOOSE MENU:\n");
            printf("1. SAVE\t2. LOAD\t3. LS\n4. DELETE\t5. LOGOUT\n");
            break;
        default:
            printf("TRY AGAIN! YOU'VE SELECTETD : %d\n", type);
            break;
    }
    return;
}

int typeOf(char* input, int promptType) {
    int type = -1;
    
    type = atoi(input);
    
    switch (promptType) {
        case DEFAULT:
            switch (type) {
                case 1:
                    type = LOGIN;
                    break;
                case 2:
                    type = SIGNUP;
                    break;
                default:
                    perror("typeOf : default type error");
                    exit(1);
                    break;
            }
        break;
        case MENU:
            switch (type) {
                case 1:
                    type = SAVE;
                    break;
                case 2:
                    type = LOAD;
                    break;
                case 3:
                    type = LS;
                    break;
                case 4:
                    type = DELETE;
                    break;
                case 5:
                    type = LOGOUT;
                    break;
                default:
                    perror("typeOf : menu type error");
                    exit(1);
                break;
            }
         break;
        default:
            perror("typeOf : prompt type error");
            exit(1);
            break;
    }
    
    return type;
}

char* getUserInput() {
    char* input = (char*)malloc(sizeof(char)*MAX_STRING);
    int n;
    n = scanf("%s", input);
    if (n > MAX_STRING) { perror("input_max overflow"); exit(1);}
    //
    
    return input;
}

int signup(int fd) {
    //
    char* id;
    char* pwd;
    int signUpSuccess = 0;
    FILE* fin, *fout;
    
    prompt(SIGNUP);
    printf("id: ");
     id = getUserInput();
    printf("password: ");
     pwd = getUserInput();
    
    if ((fout = fdopen(fd, "w")) == NULL) {perror("signup fdopen"); exit(1);}
    if ((fin = fdopen(fd, "r")) == NULL) {perror("signup fdopen"); exit(1);}
    
    fprintf(fout, "%d %s %s\n", SIGNUP, id, pwd);
    fflush(fout);
    fscanf(fin, "%d", &signUpSuccess);
    
    if (signUpSuccess) {
        printf("signUp Success\n");
    } else {
        printf("signUp Failed\n");
    }
    fclose(fout);
    fclose(fin);
    
    return signUpSuccess;
}

int loginS(int fd) {
    char* id;
    char* pwd;
    int loginSuccess = 0;
    FILE* fin, *fout;
    
    prompt(LOGIN);
    printf("id: ");
     id = getUserInput();
    printf("password: ");
     pwd = getUserInput();
    
    if ((fout = fdopen(fd, "w")) == NULL) {perror("login fdopen"); exit(1);}
    if ((fin = fdopen(fd, "r")) == NULL) {perror("login fdopen"); exit(1);}
    
    fprintf(fout, "%d %s %s\n", LOGIN, id, pwd);
    fflush(fout);
    fscanf(fin, "%d", &loginSuccess);
    
    if (loginSuccess) {
        printf("login Success\n");
    } else {
        printf("login Failed\n");
    }
    fclose(fout);
    fclose(fin);
    return loginSuccess;
}

void save(int fd) {
    char* fileName;
    int loginSuccess = 0;
    int c;
    FILE* fin, *fout, *file;
       
    prompt(SAVE);

    printf("file name:\n");
    fileName = getUserInput();
    
       
    if ((file = fopen(fileName, "r")) == NULL) {perror("save fopen"); exit(1);}
    
    if ((fout = fdopen(fd, "w")) == NULL) {perror("save fdopen"); exit(1);}
    if ((fin = fdopen(fd, "r")) == NULL) {perror("save fdopen"); exit(1);}
    fprintf(fout, "%d ", SAVE);
    
    if(fout!=NULL && file!=NULL){
        while((c=getc(file))!=EOF){
            putc(c,fout);
        }
        fclose(fout);
        fclose(file);
    }
       
    if (loginSuccess) {
        printf("login Success\n");
    } else {
        printf("login Failed\n");
    }
    fclose(fout);
    fclose(fin);
}

void load(int fd) {
    
}
void ls(int fd) {
    
}
void del(int fd) {
    
}

void talk_with_server(int fd) {
    char buf[BUFSIZ];
    buf[0] = '1';
    buf[1] = '\0';
    int n;
    char* input;
    int type;
    // quit value
    int quit = 0;
    while (!quit) {
        prompt(DEFAULT);
        input = getUserInput();
        type = typeOf(input, DEFAULT);
        // login fisrt
        switch (type) {
            case SIGNUP:
                signup(fd);
            break;
            case LOGIN:
                quit = loginS(fd);
            default:
                exit(1);
            break;
        }
    }
    
    
    
    //reset quit
    quit = 0;
     while (!quit) {
        // select menu
        prompt(MENU);
        input = getUserInput();
        type = typeOf(input, MENU);
        switch (type) {
            case LOGOUT:
                prompt(LOGOUT);
                //logout();
            break;

            case SAVE:
                prompt(SAVE);
                save(fd);
            break;

            case LOAD:
                prompt(LOAD);
                load(fd);
            break;

            case LS:
                prompt(LS);
                ls(fd);
            break;

            case DELETE:
                prompt(DELETE);
                del(fd);
            break;

            default:
                break;
        }
    }
    n = write(fd, buf, BUFSIZ);
    write(1, buf, n);
    n = read(fd, buf, BUFSIZ);
    write(1, buf, n);
}

int main(int argc, char* argv[]) {
    int fd;

    fd = connect_to_server(argv[1], 13000);
    if (fd == -1)    exit(1);
    talk_with_server(fd);
    close(fd);
}

