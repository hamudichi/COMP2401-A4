// So since both the client and server both use the same logo,
//  why not put it in one file and let them both access it?!

#include "headers.h" 

void printLogo(char *userAgent) {
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
         ANSI_BOLD ANSI_ITALIC
        );

  printf("%s" 
         ANSI_COLOR_RESET
         ANSI_COLOR_RED  "\n█    █  █▄▄█  █▄▄▄▄▄ ▀▄▄▄▄▀"
         ANSI_COLOR_BLUE " ▀▄▄▄█▀ ▄▄█▄▄   ▀▄▄▄▀"
         " Version %s \n\n"
         ANSI_COLOR_RESET, userAgent, VERSION );
}
/*----------------------------------------------------------------------------*/
void dealWithIt() {
  printf( ANSI_CLEAR
   "\n" ANSI_COLOR_BLUE
   " █▀                        ▀▄     looks around      \n"
   "▄▀                          ▀▄    see's you looking \n"
   "█     ███           ███      █                      \n"
   "█     ▀▀▀           ▀▀▀      █    looks at you      \n"
   " █                          █                       \n"
   "  ▀                        ▀                        \n"
   "           ▀▀▀▀▀▀                                   \n");
  sleep(1);
  printf( ANSI_CLEAR
   ANSI_COLOR_YELLOW
   " █▀                             ▀▄                                       \n"
   "▄▀                               ▀▄   ▄            ███████       ███████ \n"
   "█            ███         ███      █    ▀▀▀▄▄ ▄▄▄▄▄▄███████       ███████ \n"
   "█            ▀▀▀         ▀▀▀      █    ▄▄▄▀▀ ▀     ███████  ▀▀▀  ███████ \n"
   " █                               █    ▀            ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀ \n"
   "  ▀                             ▀      puts on glasses...like a boss     \n"
   "                  ▀▀▀▀▀▀                            \n");
  sleep(1);
  printf( ANSI_CLEAR
   ANSI_COLOR_RED
   " █▀                               ▀▄                \n"
   "▄▀         ███████       ███████   ▀▄               \n"
   "█    ▄▄▄▄▄▄███████       ███████    █  deal with it \n"
   "█    ▀     ███████       ███████    █               \n"
   " █         ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀   █                \n"
   "  ▀                               ▀                 \n"
   "                  ▀▀▀▀▀▀                            \n"
   ANSI_COLOR_RESET
  );
  sleep(3);
}

