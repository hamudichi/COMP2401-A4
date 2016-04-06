EXECS= server client 
LIBS= -lncurses
FUNC_H= encryption.h logo.h
FUNC=  encryption.c logo.c

all:	$(EXECS)

server:	server.c defs.h client.h colors.h $(FUNC_H) 
	gcc -o server server.c servFun.c $(FUNC)

client:	client.c defs.h client.h colors.h cliFun.c $(FUNC_H)
	gcc -o client client.c cliFun.c $(FUNC) $(LIBS) 

clean:
	rm -f $(EXECS)
