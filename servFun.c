////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//          ▄▄▄▄  ▄▄▄▄▄▄ ▄▄▄▄▄  ▄    ▄ ▄▄▄▄▄▄ ▄▄▄▄▄         ▄▄▄▄▄▄            //
//         █▀   ▀ █      █   ▀█ ▀▄  ▄▀ █      █   ▀█        █                 //
//         ▀█▄▄▄  █▄▄▄▄▄ █▄▄▄▄▀  █  █  █▄▄▄▄▄ █▄▄▄▄▀  ▄▄▄▄  █▄▄▄▄▄            //
//             ▀█ █      █   ▀▄  ▀▄▄▀  █      █   ▀▄        █                 //
//         ▀▄▄▄█▀ █▄▄▄▄▄ █    ▀   ██   █▄▄▄▄▄ █    ▀        █     unctions    //
//                                                                            //
// Contains: Server's functions                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* All headers used by this program can be found here*/
#include "headers.h"


int myListenSocket, clientSocket;

void closeMySocket(int i) {
  if (i == 0) close(clientSocket); else close(myListenSocket);
}

/*----------------------------------------------------------------------------*/

void giveMeTime () {
  /*
   * Prints out time in Sun Aug 19 02:56:02 2012 
   * Note, this is only useful to log things over the server, if in case the 
   * server is able to multiplex and receive  simontantious connections from 
   * users. However, I thought it would look cool over at the server end.Yes 
   * it  would  look  cool  and  I am sure no one in the class is even doing 
   * anything close to how I am doing this assignment.In fact, I am treating
   * this assignment as if it was worth 100% of my totoal mark
   *
   * You can find the tutorial for  printing out time using time.h over here
   *http://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm 
   */

  time_t rtime;         // rawtime;
  struct tm *info;
  char buffer[80];

  time (&rtime);
  info = localtime(&rtime);
  strftime(buffer, 80, "%c", info);
  printf("%s",buffer);
}
/*----------------------------------------------------------------------------*/
/* Initializes connection with the client. 
 * - TODO : ADD a function to get the ip address of the client in connection
 */
void initServerSocket()
{
  struct sockaddr_in  myAddr;
  int i;

  /* create socket */
  myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (myListenSocket < 0) {
      printf("couldn't open socket\n");
      exit(-1);
  }

  /* setup my server address */
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons((unsigned short) MY_PORT);

  /* bind my listen socket */
  i = bind(myListenSocket,
           (struct sockaddr *) &myAddr,
           sizeof(myAddr));
  if (i < 0) {
      printf(ANSI_COLOR_RED
             "Woops... I'm sorry, something went terribly wrong.\n"
             ANSI_COLOR_RESET ANSI_COLOR_GREY
             "ERROR: Couldn't bind socket\n"
             ANSI_COLOR_RESET);
    exit(-1);
  }

  /* listen */
  i = listen(myListenSocket, 5);

  if (i < 0) {
    printf(ANSI_COLOR_RED
           "Woops... I'm sorry, something went terribly wrong.\n"
           ANSI_COLOR_RESET
           "couldn't listen\n");
    exit(-1);
  }

  printf(ANSI_COLOR_GREEN
         "The server has been successfully initalized. For further help please "
         "type /h on the client end\n"
         ANSI_COLOR_RESET);

}
/*----------------------------------------------------------------------------*/

void waitForConnection()
{
  struct sockaddr_in clientAddr;
  int addrSize;

  printf("waiting for connection... \n");

  /* wait for connection request */
  clientSocket = accept(myListenSocket,
                        (struct sockaddr *) &clientAddr,
                        &addrSize);
  if (clientSocket < 0) {
    printf("couldn't accept the connection\n");
    exit(-1);
  }

  printf("got one!\n");
  /* Get Client IP address */
  // printf("\nIP address is: %s\n", inet_ntoa((struct in_addr *) &clientAddr));

}
/*----------------------------------------------------------------------------*/

void recvText(char *text)
{
  char buff[MAX_BUFF];
  int bytesRcv;

  buff[0] = '\0';

  bytesRcv = recv(clientSocket, buff, sizeof(buff), 0);
  buff[bytesRcv] = '\0';
  strcpy(text, buff);
}

/*----------------------------------------------------------------------------*/
/* Just to make our lifes easier and allow us to compare the whole structure 
** at once.
**/
int compareSongs (SongType a, SongType b) {
   if (a.name == b.name && a.artist == b.artist && a.album == b.album &&
       a.duration == b.duration) 
       return 0; 
   else 
       return 1;
}
/*----------------------------------------------------------------------------*/

/* Singly Linked List Functions */

void insertSong(Node *song, SongType info) {
    /* Iterate through the list */
    while( song != NULL) {
         song = song -> next;
    }

    /* Allocate new memory for the new node*/
    song -> next = (Node *)malloc(sizeof(Node)); // mem allocations
    song = song -> next;       // the current song, becomes the new song
    song -> data = info;       // Insert new song information, sent by client
    song -> next = NULL;       // Set the next pointer to NUll for the new node
}
/*----------------------------------------------------------------------------*/

void removeSong(Node *song, SongType info) {
    /* Iterate through the list*/
    while(song -> next != NULL && compareSongs((song -> next) -> data,info) == 1){
        song = song -> next;
    }

    /* In the case of not finding the song in the list */
    if (song -> next == NULL) { 
        printf(ANSI_COLOR_YELLOW
               "Uhm...awkward... I couldn't find that song in my list :(.\n"
               ANSI_COLOR_RESET );
        return; // exit
    }

    /*
     * To clean up our mess. We need to make a temporary node and save the info
     * into that temporary node, until we can move the "next" node, and then we
     * are able to restore the info we put in temp.
     */

    Node *tempNode; 
    tempNode = song -> next;           // points to the removed node
    song -> next = tempNode -> next;   // relink

    /*
     * At this point we have cleaned up our mess and relinked the list, we can
     * now free tempNode into memory land it always belonged to. In boring
     * terms deallocate the memory.
     */

    free(tempNode);
}
/*----------------------------------------------------------------------------*/

void showMeSong(Node *song) {
    /* 
     * We need to know whats inside a song...don't we ?! I mean what the heck is
     * the whole point if we didn't.... :(
     */
    if (song == NULL) {printf("NULL YOUR LIFE YOU FREEK!!!"); return;}
  
    /* If all is good, it is then time to crack open SongType into strings */
    printf(ANSI_COLOR_RESET
           "Name:%10s\n"
           "Artist:%10s\n"
           "Album:%10s\n"
           "Duration:%10d\n"
           ,song -> data.name, song -> data.artist 
           ,song -> data.album, song -> data.duration);

}
/*----------------------------------------------------------------------------*/
/* the use of an int function is to simulate a bool*/
int findSong(Node *song, SongType info){
   /* Finding the song using SongType */
   while (song != NULL) {
      if ( compareSongs(song -> data, info) == 0) { return 1;}
      song = song -> next;     // go into the next node
   }
   /* In the case in which the node was not found*/
   return 0;
}
/*----------------------------------------------------------------------------*/

