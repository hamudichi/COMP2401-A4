////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  come at me                                // 
//                     ▄▄▄  ▄      ▄▄▄▄▄  ▄▄▄▄▄▄ ▄▄   ▄▄▄▄▄▄▄▄                //
//                   ▄▀   ▀ █        █    █      █▀▄  █   █                   // 
//                   █      █        █    █▄▄▄▄▄ █ █▄ █   █                   //
//                   █      █        █    █      █  █ █   █                   //
//                    ▀▄▄▄▀ █▄▄▄▄▄ ▄▄█▄▄  █▄▄▄▄▄ █   ██   █                   //
//                                                                            //
//                                                                            //
//    Author: Mohamad Yassine, 2016                                           //
//                                                                            //
//    Purpose: To connect over TCP and store song information in a data       //
//             structure found in defs.h, in addition provide the client      //
//             with the songs that have been stored in the server.            //
//                                                                            //
//    Client:  This is the client end, which is much more fancier than the    //
//             server end. You are welcome.                                   //
//                                                                            //
//    Things to improve:                                                      //
//             - Read an MP3 file and read it's headers for song info         //
//               and then convert the file into binary and send it over.      //
//             - Usage of a GUI library, such as GTK or QT                    //
//             - Play sounds (that is haha)                                   //
//             - Dynamically change the server, without closing the client    //
//             - TO BE DETERMINED                                             //
//                                                                            //
//    Implemented Features:                                                   //
//             - Storing a song in provided data structures in defs.h         //
//             - Requesting Song list from the server                         //
//             - Encryption of packets sent over TCP                          //
//             - /me ate an apple                                             //
//             - Command line options (check --help)                          //
//             - Ncurses library, for eye-candy                               //
//        TBD  - ALSA library                                                 //
//             - Use of UNIX 80 character limit, as provided by IBM Punchcard //
//                 I googled it... !                                          //
//             - TO ADD LATER MORE BEFORE HANDING IN NOTICE ME SEMPAI!!       //
//                                                                            //
//    Compilation:                                                            //
//             $ gcc client.c -o client -lncurses -lmenu                      //
//                                                                            //
//    Execution:                                                              //
//             $ ./client                                                     //
//                                                                            //
//    LICENSE: This program is licensed under GNU Public License, refer to    //
//             the LICENSE file provided in the main directory.               //
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

  /* Reset any previous ANSI COLORING done by the bash */
  printf(ANSI_COLOR_RESET);

  /* If there are any arguments, check what they are */
  if (argc > 1) {    
    if (strcmp(argv[1], "--ncurses") == 0) {
     printf(ANSI_ITALIC 
            "You have chosen to use the ncurses interface.\n" 
            ANSI_COLOR_RESET );
     /* TEMOPRARY  */
     ncurses(3,20,20,100);
     return 0;

    } else if(strcmp(argv[1], "--help") == 0) {
      /* Help Page */
       printf(ANSI_UNDER ANSI_BOLD 
              "MOEUSIC" 
              ANSI_ITALIC 
              " v0.1\n" 
              ANSI_COLOR_RESET
              "You have reached the external help page of the client.\n"
              " Here are the possible arguments: "
              ANSI_COLOR_GREEN 
              "\n\t --help "
              ANSI_COLOR_RESET
              "\t: brings you to this lovely page"
              ANSI_COLOR_GREEN 
              "\n\t --ncurses "
              ANSI_COLOR_RESET
              "\t: uses the ncurses interface.\n"
              ANSI_COLOR_RESET );
       return 0;
  
    } else if(sizeof(argv[1]) >  0) {
      /* checks if user entered the wrong argument i.e ./server ksdjfksj */
       printf("Woops, it seems you the argument you tried to run the client in"
              " is \n"
              ANSI_COLOR_RED
              " '%s'" 
              ANSI_COLOR_RESET
              " , except I am stupid and no linglish... :( . "
              ANSI_COLOR_GREEN ANSI_BOLD 
              "\nTry --help"
              ANSI_COLOR_RESET
              "\n", argv[1]);
       return 0;
   }
  } else { // if argc < 1  
       printf("You have not chosen any external parameters " 
              "to run the client under.\n");
  }
  /* Welcome Screen */ 
  printf("Welcome, this is the client end of MOEUSIC.\n"
         ANSI_COLOR_CYAN
         "Please enter your username [under 32 characters]: "
         ANSI_COLOR_RESET);

  /* Gets username from user */
  fgets(userID, sizeof(userID), stdin);

  printf(ANSI_COLOR_GREEN
         "Establising connection to server %s:%d \n\nFor further assistance or "
         "help, please visit the help page by simply typing "
         ANSI_COLOR_GREEN 
         "'/h'"
         ANSI_COLOR_RESET" \n", ANSI_COLOR_RESET, SERVER_IP,SERVER_PORT);

  /* Initiats connections */
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
             "Commands include :\n"
             ANSI_COLOR_RED
             "\t/h\t: For this lovely page\n\t/q\t: Closes this program.\n"
             ANSI_COLOR_RESET);

    } else if (strcmp(token, "/me") == 0) {
  /*  Its fate is to be determined 
      fgets(str, sizeof(str), stdin);
      printf("%s %s", userID, str);
   */  
    } else if (strcmp(str, "/q") == 0) {
      /* Soft-quiting */
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
 *  Ok this comment is way too long and I am having a conversation with you 
 *  (marker).... soo .. Hi bye
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

