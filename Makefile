SERVERNAME = server
CLIENTNAME = client
.PHONY: clean

RM = rm -f

$(SERVERNAME): server.c socklib.o
	gcc -o $(SERVERNAME) $(SERVERNAME).c socklib.o

$(CLIENTNAME): $(CLIENTNAME).c socklib.o
	gcc -o $(CLIENTNAME) $(CLIENTNAME).c socklib.o

socklib.o: socklib.c socklib.h
	gcc -Wall -c socklib.c

clean:
	$(RM) *.o
