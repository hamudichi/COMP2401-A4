////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  come at me                                //      
//                  ▄▄▄▄  ▄▄▄▄▄▄ ▄▄▄▄▄  ▄    ▄ ▄▄▄▄▄▄ ▄▄▄▄▄                   //
//                 █▀   ▀ █      █   ▀█ ▀▄  ▄▀ █      █   ▀█                  //
//                 ▀█▄▄▄  █▄▄▄▄▄ █▄▄▄▄▀  █  █  █▄▄▄▄▄ █▄▄▄▄▀                  //
//                     ▀█ █      █   ▀▄  ▀▄▄▀  █      █   ▀▄                  //
//                 ▀▄▄▄█▀ █▄▄▄▄▄ █    ▀   ██   █▄▄▄▄▄ █    █                  //
//                                                                            //
//                                                                            //
//    Author: Mohamad Yassine, 2016                                           //
//                                                                            //
//    Purpose: To connect over TCP and store song information in a data       //
//             structure found in defs.h, in addition provide the client      //
//             with the songs that have been stored in the server.            //
//                                                                            //
//    Things to improve:                                                      //
//             - Store songs in a file and read when if a server failue       //
//               occurs. Also provides the ability of shutting down the       //
//               the server, which is pretty useful.                          //
//             - A better encryption method.                                  //
//             - Multiplex connections, to provide simontanous connections    //
//             - Provide a GUI or Ncurses page for easier use & navigation    //
//             - Implement the UDP protocol to transmit file and to not rely  //
//                                                                            //
//    Implemented Features:                                                   //
//             - Singly Linked List                                           //
//             - Command line options (check --help)                          //
//             - Organized Logging of client activity                         //
//             - Use of UNIX 80 character limit, as provided by IBM Punchcard //
//                 I googled it... !                                          //
//             - TO ADD LATER MORE BEFORE HANDING IN NOTICE ME SEMPAI!!       //
//                                                                            //
//    Compilation:                                                            //
//             $ gcc server.c -o server                                       //
//                                                                            //
//    Execution:                                                              //
//             $ ./server                                                     //
//                                                                            //
//    LICENSE: This program is licensed under GNU Public License, refer to    //
//             the LICENSE file provided in the main folder.                  //
//                                                                            //
//----------------------------just-a-little-meme------------------------------//
//                                                                            //
//  █▀                        ▀▄                                              //
// ▄▀                          ▀▄                                             //
// █     ███           ███      █                                             //
// █     ▀▀▀           ▀▀▀      █                                             //
//  █                          █                                              //
//   ▀                        ▀                                               //
//            ▀▀▀▀▀▀                                                          //
//                                                                            //
//  █▀                               ▀▄                                       //
// ▄▀                                 ▀▄   ▄            ███████       ███████ //
// █            ███           ███      █    ▀▀▀▄▄ ▄▄▄▄▄▄███████       ███████ //
// █            ▀▀▀           ▀▀▀      █    ▄▄▄▀▀ ▀     ███████  ▀▀▀  ███████ //
//  █                                 █    ▀            ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀ //
//   ▀                               ▀                                        //
//                   ▀▀▀▀▀▀                                                   //
//  █▀                               ▀▄                                       //
// ▄▀         ███████       ███████   ▀▄                                      //
// █    ▄▄▄▄▄▄███████       ███████    █  deal with it                        //
// █    ▀     ███████       ███████    █                                      //
//  █         ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀   █                                       //
//   ▀                               ▀                                        //
//                   ▀▀▀▀▀▀                                                   //
////////////////////////////////////////////////////////////////////////////////


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

/* Definitions */
#define MY_PORT 60003

/* TO BE PUT IN A SEPERATE HEADER */
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

void giveMeTime () {
  /*
   * Prints out time in Sun Aug 19 02:56:02 2012 
   * Note, this is only useful to log things over the server, if in case the server
   * is able to multiplex and receive simontantious connections from users.
   * However, I thought it would look cool over at the server end
   * Yes it would look cool and I am sure no one in the class is even doing anything
   * close to how I am doing this assignment.
   * In fact, I am treating this assignment as if it was worth 100% of my totoal mark
   *
   * You can find the tutorial for printing out time using time.h over here
   * http://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm */

  time_t rtime;         // rawtime;
  struct tm *info;
  char buffer[80];

  time (&rtime);
  info = localtime(&rtime);
  strftime(buffer, 80, "%c", info);
  printf("%s",buffer);
}

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
  if (argc > 1) {
     if(sizeof(argv[1]) > 0) {
         if(strcmp(argv[1], "--help") == 0) {
             printf("You have reached the help page\n");
             return 0;
         } else {
             printf(ANSI_BOLD ANSI_COLOR_RED ANSI_ITALIC "%s" ANSI_COLOR_RESET
                    " is not understood.\n", argv[1]);
	     return 0;
         }
     }
  }

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
        printf(ANSI_COLOR_RED "User " ANSI_COLOR_RESET ANSI_GREY_BCK "%s" ANSI_COLOR_RESET ANSI_COLOR_RED" has disconnected..." 
               ANSI_ITALIC , userID);
	giveMeTime(); printf(ANSI_COLOR_RESET "\n");
        break;
      } else if(strcmp(buffer, "/h") == 0) {
        printf(ANSI_COLOR_BLUE "User " ANSI_COLOR_RESET ANSI_GREY_BCK "%s" ANSI_COLOR_RESET ANSI_COLOR_RED " has requested help page.\n" ANSI_COLOR_RESET, userID); 
      } else if (strcmp(buffer, "/s") == 0) {
        /* The user has requested to send a song to the server */
	printf(ANSI_COLOR_YELLOW ANSI_ITALIC "User '%s' is sending a song over.\n" ANSI_COLOR_RESET, userID);
      } else {
        printf(ANSI_COLOR_GREY "User" ANSI_COLOR_CYAN ": %s" ANSI_COLOR_RESET ":  %s\n", userID, buffer);
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
