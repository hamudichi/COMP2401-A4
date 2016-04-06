EXECS= server client 
LIBS= -lncurses

all:	$(EXECS)

server:	server.c defs.h client.h colors.h servFun.c encryption.c
	gcc -o server server.c servFun.c encryption.c

client:	client.c defs.h client.h colors.h cliFun.c encryption.c
	gcc -o client client.c cliFun.c encryption.c $(LIBS) 

clean:
	rm -f $(EXECS)
