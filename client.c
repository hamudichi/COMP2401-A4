 /*
  * Features:
  *          - upload/download songs to the server
  *          - get list of songs
  *          - implements ncurser's window library
  *          - have the option to change the server (i.e change port or ip)
  *          - also be aware if this client at a given time is queued or has a direct
  *            connection with the server
  *          - get ID from user, and send it to the server (
		i.e username...Bob or Moe..etc)
  *          - to be determined later you dummyyy **REMOVE**
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* Check man pages for inet and close */
#include <unistd.h>    // Added for close() "implicit declaration"
#include <arpa/inet.h> // Added for inet_addr "implicit declaration"

/* For macro ... va_list ..etc*/
#include <stdarg.h>

/* Defintions */

#define SERVER_IP "127.0.0.1"
#define SERVER_IP_n "99.246.96.212"
#define SERVER_PORT 60003

/* Unofficial header files*/
#include "client.h"
#include "defs.h"

/* FOR LATER RELEASES 
  const unsigned SERVER_IP = {"127.0.0.1"};
*/

int  mySocket;
void initClientSocket();
void ncurses(int , ...);

int main(int argc, char **argv)
{
  err *currErr;
  char str[MAX_STR];
  char userID[MAX_USER_NAME];
  char buffer[MAX_BUFF];
  const char s[3] = "/me";
  char *token;
  /* If there are any arguments, check what they are */
  if (argc > 1) {
    
    if (strcmp(argv[1], "--ncurses") == 0) {
     printf(ANSI_ITALIC "You have chosen to use the ncurses interface.\n" 
            ANSI_COLOR_RESET );
     ncurses(3,20,20,100);
     return 0;

    } else if(strcmp(argv[1], "--help") == 0) {
      /* Help Page */
       printf(ANSI_UNDER ANSI_BOLD "MOEUSIC" ANSI_ITALIC " v0.1\n" ANSI_COLOR_RESET);
       printf( "You have reached the external help page of the client.\n"
               " Here are the possible arguments: "
               ANSI_COLOR_GREEN "\n\t --help "    ANSI_COLOR_RESET
               "\t: brings you to this lovely page"
               ANSI_COLOR_GREEN "\n\t --ncurses " ANSI_COLOR_RESET
               "\t: uses the ncurses interface.\n"
               ANSI_COLOR_RESET );
       return 0;
  
    } else if(sizeof(argv[1]) >  0) {
       printf("Woops, it seems you the argument you tried to run the client in is \n"
              ANSI_COLOR_RED" '%s'" ANSI_COLOR_RESET" , except I am stupid and no linglish... :( . " 
              ANSI_COLOR_GREEN ANSI_BOLD "\nTry --help" ANSI_COLOR_RESET "\n", argv[1]);
       return 0;
   }

  } else { 
       printf("You have not chosen any external parameters " 
              "to run the client under.\n");
  }

  printf("Welcome, this is the client end of MOEUSIC.\n" ANSI_COLOR_CYAN
         "Please enter your username [under 32 characters]: " ANSI_COLOR_RESET);

  /* Gets username from user */
  fgets(userID, sizeof(userID), stdin);

  printf(ANSI_COLOR_GREEN
         "Establising connection to server %s:%d \n"
         ANSI_COLOR_RESET, SERVER_IP,SERVER_PORT);

  printf("\nFor further assistance or help, please visit the help page by"" simply typing " 
         ANSI_COLOR_GREEN "'/h'" ANSI_COLOR_RESET" \n");



  initClientSocket();
  /* SEND USER THAT WE GOT FROM THE ABOVE fgets */
  userID[strlen(userID)-1] = '\0'; // add a terminator at the end of the char[]
  strcpy(buffer, userID);
  send(mySocket, buffer, strlen(buffer), 0);


/* get input from user and send to server */
  while (1) {
    printf("Please enter message: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';

    strcpy(buffer, str);
    send(mySocket, buffer, strlen(buffer), 0);
    
    token = strtok (str, s);
    printf("%s", token);

    if (strcmp(str, "/h") == 0) {
      printf(ANSI_COLOR_CYAN
             "Welcome to the help page. This is a beta-help page\n"
             "With later releases the help page should be using\n"
             "the ncurses library.\n"
             "Commands include :\n" ANSI_COLOR_RED "\t/h\t: For this"
             " lovely page\n\t/q\t: Closes this program.\n"
             ANSI_COLOR_RESET );
    } else if (strcmp(token, "/me") == 0) {
 
//      fgets(str, sizeof(str), stdin);
      printf("%s %s", userID, str);
    
    } else if (strcmp(str, "/q") == 0) {
      break;
    }
  }

  close(mySocket);

  return 0;
}

void initClientSocket()
{
  struct sockaddr_in  addr;
  int i;

/* create socket */
  mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (mySocket < 0) {

    printf("couldn't open socket\n");    
    exit(-1);
  }

/* setup address */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  addr.sin_port = htons((unsigned short) SERVER_PORT);

/* connect to server */

  i = connect(mySocket, 
              (struct sockaddr *) &addr,
              sizeof(addr));
  if (i<0) {
    printf("client could not connect!\n");
    exit(-1);
  }
}



/*
 * So... This is just an alpha, I don't know how I will implement it just yet
 * So calm down Yo!
 * For personal refrence;  ... is a macro and accepts n number of arguments
 *  just like how printf is implemented.
 *  I googled it.
 *  If you don't believe me google or man printf it, yes I just did that
 *  Ok this comment is way too long and I am having a conversation with you (marker),
 *  soo .. Hi bye
 */
void ncurses(int count,  ...) {
    va_list args;
    int i;
    int sum = 0;

    va_start(args, count);
    for(i = 0; i < count; i++)
        sum += va_arg(args, int);
    //  printf("%s",va_arg(args, char));
    va_end(args);

    printf("%d\n", sum);
}

