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

#include "headers.h"

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
