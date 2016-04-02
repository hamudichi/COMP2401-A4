////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//            ▄▄▄  ▄      ▄▄▄▄▄  ▄▄▄▄▄▄ ▄▄   ▄▄▄▄▄▄▄▄        ▄    ▄           //
//          ▄▀   ▀ █        █    █      █▀▄  █   █           █    █           //
//          █      █        █    █▄▄▄▄▄ █ █▄ █   █           █▄▄▄▄█           //
//          █      █        █    █      █  █ █   █     ▀▀▀   █    █           //
//           ▀▄▄▄▀ █▄▄▄▄▄ ▄▄█▄▄  █▄▄▄▄▄ █   ██   █           █    █           //
//                                                                            //
// Contains: ANSI COLORING and styles, client error, ncurses prototypes       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* Include Gaurds - used for making sure the file is only read once or included once */
#ifndef client_h
#define client_h

#define MAX_USER_NAME 32


/* enumeration types */
typedef enum err {
   _SERVER_CONNECTION_FAILURE,
   _SOCKET_ERROR
} err;


/* The following are definition to colors using ANSI */
/* http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c */
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_BLUE  "\x1b[34m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREY  "\x1b[40m"
#define ANSI_GREY_BCK "\x1b[01;40m"
#define ANSI_ITALIC "\x1b[03m"
#define ANSI_UNDER "\x1b[04m"
#define ANSI_BOLD "\x1b[01m"

/* Declarations */


/*
	┏┓╻┏━╸╻ ╻┏━┓┏━┓┏━╸┏━┓   ┏━╸┏━┓┏┳┓┏━┓┏━┓╻ ╻┏━┓╺┓
	┃┗┫┃  ┃ ┃┣┳┛┗━┓┣╸ ┗━┓   ┃  ┃ ┃┃┃┃┣━┛┏━┛┗━┫┃┃┃ ┃
	╹ ╹┗━╸┗━┛╹┗╸┗━┛┗━╸┗━┛   ┗━╸┗━┛╹ ╹╹  ┗━╸  ╹┗━┛╺┻╸
	the following is my implementation of the ncurses
        library for listing and viewing the songs plus
        sending comments
*/

#endif
