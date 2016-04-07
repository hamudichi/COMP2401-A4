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

#define VERSION "0.1a"
#define MAX_USER_NAME 32

/* Socket Related Defintions */
#define SERVER_IP "127.0.0.1"
#define SERVER_IP_n "SOME_NAT_IP!!!!"
#define SERVER_PORT 60003

/* Function ProtoTypes */
int mySocket;
void initClientSocket();
int extArguments(int, char **);   // Deals with command preprocessors
void getUserID(char *, int ); // gets userID from user
void dealWithIt();
void dispMenu(void);
void encryptSend(int , void *, size_t , int );

/* Ncurses Stuff */
#define WIDTH 30
#define HEIGHT 10
void initNcursesMenu(int, char*);

///* enumeration types */
//typedef enum err {
//   _SERVER_CONNECTION_FAILURE,
//   _SOCKET_ERROR
//} err;
//


/*
	┏┓╻┏━╸╻ ╻┏━┓┏━┓┏━╸┏━┓   ┏━╸┏━┓┏┳┓┏━┓┏━┓╻ ╻┏━┓╺┓
	┃┗┫┃  ┃ ┃┣┳┛┗━┓┣╸ ┗━┓   ┃  ┃ ┃┃┃┃┣━┛┏━┛┗━┫┃┃┃ ┃
	╹ ╹┗━╸┗━┛╹┗╸┗━┛┗━╸┗━┛   ┗━╸┗━┛╹ ╹╹  ┗━╸  ╹┗━┛╺┻╸
	the following is my implementation of the ncurses
        library for listing and viewing the songs plus
        sending comments
*/

#endif
