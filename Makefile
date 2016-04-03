EXECS= server client 

all:	$(EXECS)

server:	server.c defs.h client.h colors.h servFun.c
	gcc -o server server.c servFun.c

client:	client.c defs.h client.h colors.h cliFun.c
	gcc -o client client.c cliFun.c

clean:
	rm -f $(EXECS)
