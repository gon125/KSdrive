#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct client_if{
	char id[100];
	char pswd[100];
};

void sign_up(); //sign up
int check(char*); //check id already exist 
int log_in(); //log in


void sign_up(){
	int ch=0;
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
	if ((f=fopen(fname,"a"))==NULL){
		printf("fopen err"); exit(0);
	}
	
	fwrite(&client,sizeof(struct client_if),1,f);

	fclose(f);
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
