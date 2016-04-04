////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//            ▄▄▄  ▄      ▄▄▄▄▄  ▄▄▄▄▄▄ ▄▄   ▄▄▄▄▄▄▄▄        ▄▄▄▄▄▄           //
//          ▄▀   ▀ █        █    █      █▀▄  █   █           █                //
//          █      █        █    █▄▄▄▄▄ █ █▄ █   █           █▄▄▄▄            //
//          █      █        █    █      █  █ █   █     ▀▀▀   █                //
//           ▀▄▄▄▀ █▄▄▄▄▄ ▄▄█▄▄  █▄▄▄▄▄ █   ██   █           █     unctions   //
//                                                                            //
// Contains: client functions                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/* All header files */
#include "headers.h"

/*----------------------------------------------------------------------------*/
void getUserID (char *userid, int unsigned size) {

  /* Welcome Screen */
  printf("Welcome, this is the client end of MOEUSIC.\n"
         ANSI_COLOR_CYAN
         "Please enter your username [under 32 characters]: "
         ANSI_COLOR_RESET);

  /* Gets username from user */
  printf("\n%d\n", sizeof((void *) &userid));
  fgets(userid, size, stdin);
  printf("\n%d\n", sizeof(userid));
}


/*----------------------------------------------------------------------------*/
int extArguments (int argc, char **argv) {

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



}


/*----------------------------------------------------------------------------*/
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


/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
