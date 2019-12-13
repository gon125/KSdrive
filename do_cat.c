void do_cat(char* f, int fd){
	char* extension = file_type(f);
	char* type = "text/plain"';
	FILE* fpsoc,*fpfile;
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
		while((c=getc(fpfile))!EOF){
			putc(c,fpscok);
			bytes++;
		}
		fclose(fpsock);
		fclose(fpfile);
	}
	server_bytes_sent +=bytes;
}
