
SERVERNAME = timeserv 
CLIENTNAME = timeclnt


$(CLIENTNAME): $(CLIENTNAME).c socklib.o
	gcc -o $(CLIENTNAME) $(CLIENTNAME).c socklib.o

$(SERVERNAME): $(SERVERNAME).c socklib.o
	gcc -o $(SERVERNAME) $(SERVERNAME).c socklib.o
socklib.o: socklib.c socklib.h
	gcc -Wall -c socklib.c

