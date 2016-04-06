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

/* All headers used by this program can be found here */
#include "headers.h"

/*-----------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
  char str[MAX_STR];
  char userID[MAX_USER_NAME];
  char buffer[MAX_BUFF];
  const char s[3] = "/me";
  char *token;

  dealWithIt();
  
  printf(ANSI_CLEAR
         ANSI_COLOR_RED
         ANSI_COLOR_RED  "▄    ▄  ▄▄▄▄  ▄▄▄▄▄▄ ▄    ▄"
         ANSI_COLOR_BLUE "  ▄▄▄▄  ▄▄▄▄▄    ▄▄▄ \n"
         ANSI_COLOR_RED  "██  ██ ▄▀  ▀▄ █      █    █" 
         ANSI_COLOR_BLUE " █▀   ▀   █    ▄▀   ▀\n"
         ANSI_COLOR_RED  "█ ██ █ █    █ █▄▄▄▄▄ █    █"
         ANSI_BOLD
         ANSI_COLOR_BLUE " ▀█▄▄▄    █    █     \n"
         ANSI_COLOR_RED  "█ ▀▀ █ █    █ █      █    █"
         ANSI_COLOR_BLUE "     ▀█   █    █      "
         ANSI_BOLD ANSI_ITALIC "CLIENT" ANSI_COLOR_RESET
         ANSI_COLOR_RED  "\n█    █  █▄▄█  █▄▄▄▄▄ ▀▄▄▄▄▀"
         ANSI_COLOR_BLUE " ▀▄▄▄█▀ ▄▄█▄▄   ▀▄▄▄▀"
         " Version %s \n\n"
         ANSI_COLOR_RESET, 
         VERSION
  );
  
  /* External Preprocessor commands */
  if (extArguments (argc,argv) == 0) {return 0;}
  
  /* Welcome Screen and ask for username */
  getUserID(userID, (unsigned) sizeof(userID));

  /* Initiats connections */
  initClientSocket();

  /* Display confirmation for user */
  printf(ANSI_COLOR_GREEN
         "Establising connection to server %s:%d \n\n"
         "For further assistance or "
         "help, please visit the help page by simply typing "
         ANSI_COLOR_YELLOW 
         "'/h'"
         ANSI_COLOR_RESET" \n", SERVER_IP, SERVER_PORT);

  /* SEND USER THAT WE GOT FROM THE ABOVE fgets */
  userID[strlen(userID)-1] = '\0'; // add a terminator at the end of the char[]
  strcpy(buffer, userID);
  send(mySocket, buffer, strlen(buffer), 0);

  /* get input from user and send to server */
  while (1) {
    printf("Please enter message: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    encrypt(str);
    strcpy(buffer, str);
    send(mySocket, buffer, strlen(buffer), 0);
    
    if (strcmp(str, "/h") == 0) {
      printf(ANSI_COLOR_CYAN
             "Welcome to the help page. This is a beta-help page\n"
             "With later releases the help page should be using\n"
             "the ncurses library.\n"
             "Commands include :\n"
             ANSI_COLOR_RED
             "\t/h\t: For this lovely page\n"
             "\t/s\t: Send song to server"
             "\t/q\t: Closes this program.\n"
             ANSI_COLOR_RESET
            );
    } else if (strcmp(str, "/s") == 0 ) {
      printf("So you want to send a song to server ... eh?\n");
    } else if (strcmp(str, "/e") == 0 ) {
      printf("GREAT!! finally someone cares about proper encrytion\n");
      fgets(str, sizeof(str), stdin);
      printf("Your original message %s ", str);
      encrypt(str); 
      printf(", your encrypted message %s\n", str);
    } else if (strcmp(str, "/clear") == 0){
      /* clear the screen so that only MOEUSIC logo is shown */ 
    } else if (strcmp(token, "/me") == 0) {
      // do something funny
    } else if (strcmp(str, "/q") == 0) {
      /* Soft-quiting */
      break;
    }
  }

  close(mySocket);

  return 0;
}

