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

char* getUserPassword() {
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
    
    fprintf(fout, "%d %s %s ", SIGNUP, id, pwd);
    fflush(fout);
    fscanf(fin, "%d", &signUpSuccess);
    
    if (signUpSuccess) {
        printf("signUp Success\n");
    } else {
        printf("signUp Failed\n");
    }
    
    fflush(fout);
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
    
    fprintf(fout, "%d %s %s ", LOGIN, id, pwd);
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
    int saveSuccess = 0;
    int c;
    FILE* fin, *fout, *file;
       
    prompt(SAVE);
    printf("file name:\n");
    fileName = getUserInput();
    
    if ((file = fopen(fileName, "r")) == NULL) {perror("save fopen"); exit(1);}
    if ((fout = fdopen(fd, "w")) == NULL) {perror("save fdopen"); exit(1);}
    if ((fin = fdopen(fd, "r")) == NULL) {perror("save fdopen"); exit(1);}
    
    fprintf(fout, "%d %s ", SAVE, fileName);
    
    if(fout!=NULL && file!=NULL){
        while((c=fgetc(file))!= EOF){
            fputc(c,fout);
            fputc(c,stdout);
        }
        fprintf(fout, "\r\n");
        fflush(fout);
        fclose(fout);
        fclose(file);
        saveSuccess = 1;
    }

    if (saveSuccess) {
        printf("save Success\n");
    } else {
        printf("save Failed\n");
    }
    fclose(fout);
    fclose(fin);
}

void load(int fd) {
    char* fileName;
    int fileExist = 0;
    int loadSuccess = 0;
    int c;
    FILE* fin, *fout, *file;
       
    prompt(LOAD);

    printf("file name:\n");
    fileName = getUserInput();
       
    if ((file = fopen(fileName, "w")) == NULL) {perror("load fopen"); exit(1);}
    
    if ((fout = fdopen(fd, "w")) == NULL) {perror("load fdopen"); exit(1);}
    if ((fin = fdopen(fd, "r")) == NULL) {perror("load fdopen"); exit(1);}
    
    fprintf(fout, "%d %s ", LOAD, fileName);
    
    fscanf(fin, "%d", &fileExist);
    
    if (!fileExist) {
        printf("file not exist on server. : %s\n", fileName);
        return;
    }
    
    if(fin!=NULL && file!=NULL){
        while((c=getc(fin))!=EOF){
            if (c == '\r') {
                if ((c=getc(fin)) == '\n') {
                    break;
                }
            }
            putc(c,file);
        }
        fclose(fin);
        fclose(file);
        loadSuccess = 1;
    }
    
    if (loadSuccess) {
        printf("load Success\n");
    } else {
        printf("load Failed\n");
    }
    fclose(fout);
    fclose(fin);
}
void ls(int fd) {
    int lsSuccess = 0;
    int c;
    FILE* fin, *fout;
       
    prompt(LS);
    
    if ((fout = fdopen(fd, "w")) == NULL) {perror("load fdopen"); exit(1);}
    if ((fin = fdopen(fd, "r")) == NULL) {perror("load fdopen"); exit(1);}
    
    fprintf(fout, "%d", LS);
    
    if(fin!=NULL){
        while((c=getc(fin))!=EOF){
            putc(c,stdout);
        }
        fclose(fin);
        
        lsSuccess = 1;
    }
    if (lsSuccess) {
        printf("load Success\n");
    } else {
        printf("load Failed\n");
    }
    fclose(fout);
    fclose(fin);
}
void del(int fd) {
    
}

int logoutS(int fd) {
    int logoutSuccess = 0;
    FILE* fin, *fout;
    
    prompt(LOGOUT);
    
    if ((fout = fdopen(fd, "w")) == NULL) {perror("logout fdopen"); exit(1);}
    if ((fin = fdopen(fd, "r")) == NULL) {perror("logout fdopen"); exit(1);}
    
    fprintf(fout, "%d", LOGOUT);
    fflush(fout);
    fscanf(fin, "%d", &logoutSuccess);
    
    if (logoutSuccess) {
        printf("logout Success\n");
    } else {
        printf("logout Failed\n");
    }
    fclose(fout);
    fclose(fin);
    return logoutSuccess;
}

void talk_with_server(int fd) {
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
                signup(dup(fd));
                break;
            case LOGIN:
                quit = loginS(dup(fd));
                break;
            default:
                printf("try again. you put : %s", input);
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
                quit = logoutS(dup(fd));
            break;

            case SAVE:
                prompt(SAVE);
                save(dup(fd));
            break;

            case LOAD:
                prompt(LOAD);
                load(dup(fd));
            break;

            case LS:
                prompt(LS);
                ls(dup(fd));
            break;

            case DELETE:
                prompt(DELETE);
                del(dup(fd));
            break;

            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    int fd;

    fd = connect_to_server(argv[1], 13000);
    if (fd == -1)    exit(1);
    talk_with_server(fd);
    close(fd);
}
