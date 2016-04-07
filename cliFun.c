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
#include "ncurses.h"

/*----------------------------------------------------------------------------*/
void dispMenu(void){
  printf("Choose from the follwing options: \n"
         "a. Add Song\n"
         "b. Delete a Song\n"
         "c. View Song(s)\n"
         "d. Exit\n"
        );
}

/*----------------------------------------------------------------------------*/
void getUserID (char *userid, int size) {

  /* Welcome Screen */
  printf("Welcome, this is the client end of MOEUSIC.\n"
         ANSI_COLOR_CYAN
         "Please enter your username [under 32 characters]: "
         ANSI_COLOR_RESET);

  /* Gets username from user */
  fgets(userid, size, stdin);

}
/*----------------------------------------------------------------------------*/
int extArguments (int argc, char **argv) {

  /* Reset any previous ANSI COLORING done by the bash */
  printf(ANSI_COLOR_RESET);

  /* If there are any arguments, check what they are */
  if (argc > 1) {
    if (strcmp(argv[1], "--help") == 0) {
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

  return 1;

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
void initNcursesMenu(int num_content, char *content) {
    /* THE FOLLOWING IS AN ACTION PLAN
     * TODO: The general design would include:
     *   - A menu which includes SEND / GET SONGS that ask the server to send or
     *     receive songs.
     *   - The menu has to have color.
     *   - The menu should also include the other commands such as (but not 
     *     limited to) a help option (optional since it is a menu ... lol),
     *   - Client ID aka username in the top corner along with IP and Port.
     *   - Others to include later.
     */
  
    /* First we need the number of choices from content */
    // int num_content = sizeof(&content) / sizeof(char *);
    int startx , starty;

    int x, y;
    
    /* We need to make a window */
    WINDOW *menu_win;

    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    raw();
    start_color();
    noecho();
    cbreak();
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0,0,"COMP2401 - MOEUSIC\n Use the up/down arrow keys to navigate\n");  
    refresh();
    
    /* Printing Menu */
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (int i = 0; i < num_content; ++i) {
       if (highlight == i + 1) {
          wattron(menu_win, A_REVERSE);
          mvwprintw(menu_win, y, x, "%s", &content[i]);
          wattron(menu_win, A_REVERSE);
       } else {
          mvwprintw(menu_win, y, x, "%s", &content[i]);
       }
       ++y;
    }
    wrefresh(menu_win);
/*
    printw("Choose from the follwing options: \n"
           "a. Add Song\n"
           "b. Delete a Song\n"
           "c. View Song(s)\n"
           "d. Exit\n"
          );
*/
    clrtoeol();
    refresh();
    endwin();
}
/*----------------------------------------------------------------------------*/

