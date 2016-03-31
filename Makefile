EXECS= server client 

all:	$(EXECS)

server:	server.c defs.h client.h
	gcc $(DEBUG) -o server server.c

client:	client.c defs.h client.h
	gcc $(DEBUG) -o client client.c

clean:
	rm -f $(EXECS)
