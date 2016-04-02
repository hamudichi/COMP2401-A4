////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//          ▄▄▄▄  ▄▄▄▄▄▄ ▄▄▄▄▄  ▄    ▄ ▄▄▄▄▄▄ ▄▄▄▄▄         ▄    ▄            //
//         █▀   ▀ █      █   ▀█ ▀▄  ▄▀ █      █   ▀█        █    █            //
//         ▀█▄▄▄  █▄▄▄▄▄ █▄▄▄▄▀  █  █  █▄▄▄▄▄ █▄▄▄▄▀  ▄▄▄▄  █▄▄▄▄█            //
//             ▀█ █      █   ▀▄  ▀▄▄▀  █      █   ▀▄        █    █            //
//         ▀▄▄▄█▀ █▄▄▄▄▄ █    ▀   ██   █▄▄▄▄▄ █    ▀        █    █            //
//                                                                            //
// Contains: Server function's prototypes                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


/* Socket Related defintions*/
#define MY_PORT 60003
#define _DEFAULT_USER_ID "USER_TROLL_9000"

/* Socket releated functions*/
void initServerSocket();      // Intializes socket connection
void waitForConnection();
void recvText(char*);        
void closeMySocket(int);

/* Interface Functions */
/* DEPRECATED */ 
//  void _Help();


/* Linked-List Control Mechanisims */
void insertSong(Node *song, SongType info);
void findSong(Node *song, SongType info);

/* Similar to find, except it frees the memory of the song found,
 * hence removing the song.
 */
void removeSong(Node *song, SongType info);
void printSongInfo(Node *song);

/* Misc. Functions */
void giveMeTime();  // Prints out the current time, refer to servFun.c for more


