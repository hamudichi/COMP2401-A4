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
  SongType tempSong;
  
  /* Ncurses Menu */
  char *mContent[] = {
                      "Add Song", 
                      "Delete Song", 
                      "View Song(s)",
                      "Quit"
                     };
  
//  dealWithIt();
  printLogo("CLIENT", CLEAR);
  
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

  /* Display Menu - Keep this if not using dup / dup2*/
  dispMenu();

  while (1) {
    /* For eye candy */
    // printLogo("CLIENT", NO_CLEAR);

    /* Display Menu first */
    // dispMenu();
    // initNcursesMenu((sizeof(mContent) / sizeof(char*)),*mContent);
    printf("Please choose from the menu above: ");

    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';
    /* Deprecated 
     * if (strcmp(str, "/h") == 0) {
     *  printf(ANSI_COLOR_CYAN
     *       "Welcome to the help page. This is a beta-help page\n"
     *       "With later releases the help page should be using\n"
     *       "the ncurses library.\n"
     *       "Commands include :\n"
     *       ANSI_COLOR_RED
     *       "\t/h\t: For this lovely page\n"
     *       "\t/q\t: Closes this program.\n"
     *       ANSI_COLOR_RESET
     *      );
     * } else
     */
 
    strcpy(buffer, str);
    /*Encryption - Usually one would use a key, but not in this case.*/
 //   encrypt(buffer);
 //   send(mySocket, buffer, strlen(buffer), 0); 
    encryptSend(mySocket, buffer, strlen(buffer),0);
    if (strcmp(str, "/q") == 0) {
      /* Soft-quiting */
      break;
    } else if (strcmp(str, "a") == 0) {
      /* Add Song */
      printf("You are about to send a song over: Please enter the following: \n"
             ANSI_COLOR_YELLOW 
             "Name  : ");
      fgets(str, sizeof(str), stdin);
      str[strlen(str) - 1] = '\0';
      encryptSend(mySocket, str, strlen(str),0);

      printf("Artist: ");
      fgets(str, sizeof(str), stdin);
      str[strlen(str) - 1] = '\0';
      encryptSend(mySocket, str, strlen(str),0);

      printf("Album : ");
      fgets(str, sizeof(str), stdin);
      str[strlen(str) - 1] = '\0';
      encryptSend(mySocket, str, strlen(str),0);
    
      printf("Duration (mins) : ");
      /* Just to make sure the user will use integars, if it is not the case
       * then he/she will be promted again to repeat their input.
       */
      for(;;){
       short *illegals = 0;
       fgets(str, sizeof(str), stdin);
       /* Check if str contains any non-ints*/
       for (int i = 0; i < strlen(str) - 1; ++i) {
         if(!isdigit(str[i])) ++illegals;
       } 
       /* If everything seems to be good, then exit*/
       if ( illegals == 0) {
         tempSong.duration = atoi(str);
      //   fgets(str, sizeof(str), stdin);
         str[strlen(str) - 1] = '\0';
         encryptSend(mySocket, str, strlen(str),0);

         /* Free illegals ... */
         free(illegals);
         break;
       }
       printf(ANSI_COLOR_RED 
              "EYYY!!! YO CHILL MAN!!"
              ANSI_COLOR_RESET 
              " Only Integar values!\nLet's try that again...\n"
              ANSI_COLOR_YELLOW
              "Duration (mins) : "
             );
      } // end sentinital loop ( I don't know how to spell, don't judge sheesh )
      
      printf(ANSI_COLOR_GREEN 
             "We are all good. Converting your song to send over\n"
             ANSI_COLOR_RESET
            );
    } else if (strcmp(str, "b") == 0) {
      /* Delete Song */
      printf(ANSI_COLOR_YELLOW);
      printf("Which song do you want to delete?\n"
             "Name ? : ");
      fgets(str, sizeof(str), stdin);
      str[strlen(str) - 1] = '\0';
      encryptSend(mySocket, str, strlen(str),0);

      printf("Artist : ");
      fgets(str, sizeof(str), stdin);
      str[strlen(str) - 1] = '\0';
      encryptSend(mySocket, str, strlen(str),0);

      printf("That should be enough info\n");
      printf(ANSI_COLOR_RESET);      
    } else if (strcmp(str, "c") == 0) {
      /* View Song(s) */
      fgets(str, sizeof(str), stdin);
      str[strlen(str) - 1] = '\0';
      encryptSend(mySocket, str, strlen(str),0);
      
    } else if (strcmp(str, "d") == 0) {
      break;
    }
 }
  close(mySocket);
  return 0;
}

