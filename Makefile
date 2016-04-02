EXECS= server client 

all:	$(EXECS)

server:	server.c defs.h client.h
	gcc -o server server.c

client:	client.c defs.h client.h
	gcc -o client client.c

clean:
	rm -f $(EXECS)
