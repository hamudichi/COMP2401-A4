
 /*
  * SERVER END
  * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MY_PORT 6003
#define INIT_SUCCESS "\x1b[32m"
#define INIT_FAIL    "\x1b[33m"
#define INIT_DESC    "\x1b[31m"
#define COLOR_RESET  "\x1b[0m"

#define _DEFAULT_USER_ID "USER_TROLL_9000"

#include "client.h"
#include "defs.h"

void initServerSocket();
void waitForConnection();
void recvText(char*);


int myListenSocket, clientSocket;
void _help();

int main(int argc, char **argv)
{
  char buffer[MAX_BUFF];
  char userID[MAX_USER_NAME] = _DEFAULT_USER_ID;

  /* Default arguments to start the server with. To implement argc argv,
   * to inlcude custom parameters to run the server under.
   * (i.e --limit x ; which would limit the number of songs a user can enter
   * --permission ; which would only allow a user to store a song and protect it
   *                from being accessed by other users. [by userID only]
   *                which means its not secure, but gives the illusion of security :p
   *
   */

  initServerSocket();


  while (1) {

/*  waiting for next client to connect  */

   // printf("\n%s\n",_DEFAULT_USER_ID);
    waitForConnection();

    recvText(userID);
    printf(ANSI_ITALIC "User %s has joined the server.\n" ANSI_COLOR_RESET);
/*  a client has connected  */

/* read messages from client and do something with it  */
    while (1) {
      recvText(buffer);
      //printf(ANSI_COLOR_GREEN "lol :  %s\n" ANSI_COLOR_RESET, buffer);
      if(strcmp(buffer,"/q") == 0) {
        printf(ANSI_COLOR_RED "User " ANSI_COLOR_RESET ANSI_GREY_BCK "%s" ANSI_COLOR_RESET ANSI_COLOR_RED" has disconnected...\n" ANSI_COLOR_RESET, userID);
        break;
      } else if(strcmp(buffer, "/h") == 0) {
        printf(ANSI_COLOR_BLUE "User " ANSI_COLOR_RESET ANSI_GREY_BCK "%s" ANSI_COLOR_RESET ANSI_COLOR_RED " has requested help page.\n" ANSI_COLOR_RESET, userID); 
      } else if (strcmp(buffer, "/s") == 0) {
        /* The user has requested to send a song to the server */
	printf(ANSI_COLOR_YELLOW ANSI_ITALIC "User '%s' is sending a song over.\n" ANSI_COLOR_RESET, userID);
      } else {
        printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET ":  %s\n", userID, buffer);
      }
    }

/*  closing this client's connection  */
    close(clientSocket);
  }

/*  all done, no more clients will be connecting  */
  close(myListenSocket);

  return 0;
}

void initServerSocket()
{
  struct sockaddr_in  myAddr;
  int i;

/* create socket */
  myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (myListenSocket < 0) {
    printf("couldn't open socket\n");
    exit(-1);
  }

/* setup my server address */
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons((unsigned short) MY_PORT);

/* bind my listen socket */
  i = bind(myListenSocket,
           (struct sockaddr *) &myAddr,
           sizeof(myAddr));
  if (i < 0) {
    printf(INIT_FAIL "Woops... I'm sorry, something went terribly wrong.\n" COLOR_RESET);
    printf(INIT_DESC "ERROR: Couldn't bind socket\n" COLOR_RESET);
    exit(-1);
  }

/* listen */
  i = listen(myListenSocket, 5);
  if (i < 0) {
    printf(INIT_FAIL "Woops... I'm sorry, something went terribly wrong.\n" COLOR_RESET);
    printf("couldn't listen\n");
    exit(-1);
  }
  printf(INIT_SUCCESS "The server has been successfully initalized. For further help please type /h on the client end\n" COLOR_RESET);

}

void waitForConnection()
{
  struct sockaddr_in clientAddr;
  int addrSize;

  printf("waiting for connection... \n");

/* wait for connection request */
  clientSocket = accept(myListenSocket,
                        (struct sockaddr *) &clientAddr,
                        &addrSize);
  if (clientSocket < 0) {
    printf("couldn't accept the connection\n");
    exit(-1);
  }

  printf("got one!\n");
 // Get Client IP address
//  printf("\nIP address is: %s\n", inet_ntoa((struct in_addr *) &clientAddr));

}

void recvText(char *text)
{
  char buff[MAX_BUFF];
  int bytesRcv;

  buff[0] = '\0';

  bytesRcv = recv(clientSocket, buff, sizeof(buff), 0);
  buff[bytesRcv] = '\0';
  strcpy(text, buff);
}
