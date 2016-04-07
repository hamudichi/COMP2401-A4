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

/* All headers used by this program can be found here */
#include "headers.h"


/*----------------------------------------------------------------------------*/
/* Definitions */
//#define MY_PORT 60003
//#define _DEFAULT_USER_ID "USER_TROLL_9000"

//int myListenSocket, clientSocket;


int main(int argc, char **argv)
{
  char buffer[MAX_BUFF];
  char **songINFO =  malloc(sizeof(SongType *));
  char userID[MAX_USER_NAME] = _DEFAULT_USER_ID;

  /* Default arguments to start the server with. To implement argc argv,
   * to inlcude custom parameters to run the server under.
   *  (i.e --limit x ; which would limit the number of songs a user can enter
   *
   *  --permission ; which would  only  allow  a  user  to  store  a song and 
          *          protect it from being accessed by other users, by userID
          *          which  means it's not secure,  but gives the illusion of 
          *          security :p
   * --help ; displays a helpful page 
   */

  if (argc > 1) {
     if(sizeof(argv[1]) > 0) {
         if(strcmp(argv[1], "--help") == 0) {
             printf("You have reached the help page\n");
            return 0;
         } else {
             printf(ANSI_BOLD ANSI_COLOR_RED ANSI_ITALIC 
                    "%s" 
                    ANSI_COLOR_RESET
                    " is not understood.\n", argv[1]);
	     return 0;
         }
     }
  }

  //  dealWithIt();
  printLogo("SERVER", CLEAR);

  /* Initiat Socket Connection */
  initServerSocket();

  while (1) {

    /* waiting for next client to connect  */

    waitForConnection();

    recvText(userID);

    printf(ANSI_ITALIC 
          "User %s has joined the server.\n" 
           ANSI_COLOR_RESET, userID);

    /* read messages from client and do something with it  */

    while (1) {
      recvText(buffer);
      decrypt(buffer);
      if(strcmp(buffer,"d") == 0) {
          printf(ANSI_COLOR_RED 
                 "User " 
                 ANSI_COLOR_RESET ANSI_GREY_BCK 
                 "%s" 
                 ANSI_COLOR_RESET ANSI_COLOR_RED
                 " has disconnected..." 
                 ANSI_ITALIC , userID);

	  giveMeTime();
          printf(ANSI_COLOR_RESET "\n");
          break;
     } else if (strcmp(buffer, "a") == 0) {
          /* The user has requested to send a song to the server */
          printf(ANSI_COLOR_YELLOW ANSI_ITALIC 
                 "User '%s' is sending a song over.\n"
                 ANSI_COLOR_RESET, userID);
          printf(ANSI_ITALIC ANSI_COLOR_CYAN
                 "Receiving the next buffer from client,"
                 " it should be the song information.\n"
                 ANSI_COLOR_RESET);
      } else if (strcmp(buffer, "b") == 0) {
         /* Delete Song */
      } else if (strcmp(buffer, "c") == 0) {
         /* Send Songs */
      } else {
          /* Print the user input, including his username */ 
          printf(ANSI_COLOR_GREY 
                 "User" 
                 ANSI_COLOR_CYAN 
                 ": %s"
                 ANSI_COLOR_RESET
                 ":  %s\n", userID, buffer);
      }
    }

    /* closing this client's connection  */
    closeMySocket(0);
  }

  /* all done, no more clients will be connecting  */
  closeMySocket(1);

  return 0;
}

