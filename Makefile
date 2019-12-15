SERVERNAME = server
CLIENTNAME = client
.PHONY: clean

RM = rm -f

$(SERVERNAME): server.c socklib.o serverlib.o
	gcc -o $(SERVERNAME) $(SERVERNAME).c socklib.o serverlib.o -lpthread

$(CLIENTNAME): $(CLIENTNAME).c socklib.o
	gcc -o $(CLIENTNAME) $(CLIENTNAME).c socklib.o

socklib.o: socklib.c socklib.h
	gcc -Wall -c socklib.c

serverlib.o: serverlib.c serverlib.h
	gcc -Wall -c serverlib.c

clean:
	$(RM) *.o
