////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//            ▄▄▄  ▄      ▄▄▄▄▄  ▄▄▄▄▄▄ ▄▄   ▄▄▄▄▄▄▄▄        ▄    ▄           //
//          ▄▀   ▀ █        █    █      █▀▄  █   █           █    █           //
//          █      █        █    █▄▄▄▄▄ █ █▄ █   █           █▄▄▄▄█           //
//          █      █        █    █      █  █ █   █     ▀▀▀   █    █           //
//           ▀▄▄▄▀ █▄▄▄▄▄ ▄▄█▄▄  █▄▄▄▄▄ █   ██   █           █    █           //
//                                                                            //
// Contains: client error, ncurses prototypes                                 //
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
