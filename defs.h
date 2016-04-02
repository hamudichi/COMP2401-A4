////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//               ▄▄▄▄   ▄▄▄▄▄▄ ▄▄▄▄▄▄  ▄▄▄▄         ▄    ▄                    //
//               █   ▀▄ █      █      █▀   ▀        █    █                    //
//               █    █ █▄▄▄▄▄ █▄▄▄▄▄ ▀█▄▄▄         █▄▄▄▄█                    //
//               █    █ █      █          ▀█  ▀▀▀   █    █                    //
//               █▄▄▄▀  █▄▄▄▄▄ █      ▀▄▄▄█▀        █    █                    //
//                                                                            //
// Contains; Data structures                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/* Include guards - 
    used for making sure the header file is only read once if included multiple
    times
*/
#ifndef defs_h
#define defs_h

/* Definetions*/
#define MAX_STR   32
#define MAX_BUFF  256


/* SongType  */
typedef struct  { 
  char name[MAX_STR];
  char artist[MAX_STR];
  char album[MAX_STR];
  int duration;
  char eInfo[1024]; // Extra info about the song
} SongType;

/* Node */
typedef struct node {
  SongType data;
  struct Node *next;
} Node;

/* ListType */
typedef struct  {
  struct Node *Node;
} ListType;



#endif // Include guard
