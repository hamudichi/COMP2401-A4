// Server Functions

/* Essential Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

/* Check man pages for inet and close */
#include <unistd.h>    // Added for close() "implicit declaration"
#include <arpa/inet.h> // Added for inet_addr "implicit declaration"

/* Local header files */
#include "colors.h"
#include "defs.h"
#include "server.h"



int myListenSocket, clientSocket;

void closeMySocket(int i) {
  if (i == 0) close(clientSocket); else close(myListenSocket);
}


void giveMeTime () {
  /*
   * Prints out time in Sun Aug 19 02:56:02 2012 
   * Note, this is only useful to log things over the server, if in case the 
   * server is able to multiplex and receive  simontantious connections from 
   * users. However, I thought it would look cool over at the server end.Yes 
   * it  would  look  cool  and  I am sure no one in the class is even doing 
   * anything close to how I am doing this assignment.In fact, I am treating
   * this assignment as if it was worth 100% of my totoal mark
   *
   * You can find the tutorial for  printing out time using time.h over here
   *http://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm 
   */

  time_t rtime;         // rawtime;
  struct tm *info;
  char buffer[80];

  time (&rtime);
  info = localtime(&rtime);
  strftime(buffer, 80, "%c", info);
  printf("%s",buffer);
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
      printf(ANSI_COLOR_RED
             "Woops... I'm sorry, something went terribly wrong.\n"
             ANSI_COLOR_RESET ANSI_COLOR_GREY
             "ERROR: Couldn't bind socket\n"
             ANSI_COLOR_RESET);
    exit(-1);
  }

  /* listen */
  i = listen(myListenSocket, 5);

  if (i < 0) {
    printf(ANSI_COLOR_RED
           "Woops... I'm sorry, something went terribly wrong.\n"
           ANSI_COLOR_RESET
           "couldn't listen\n");
    exit(-1);
  }

  printf(ANSI_COLOR_GREEN
         "The server has been successfully initalized. For further help please "
         "type /h on the client end\n"
         ANSI_COLOR_RESET);

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
  /* Get Client IP address */
  // printf("\nIP address is: %s\n", inet_ntoa((struct in_addr *) &clientAddr));

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

