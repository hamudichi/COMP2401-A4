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


// CLEARLY I NEED TO REVIEW LINKED LISTS LOL
// THATS OK I WILL USE THIS TIME TO WORK ON THE CLIENT END SINCE IT IS THE MOST IMPORTANT THING FOR THIS TIME, AND I CAN IMPLEMENT THE NEEDED CODE IN THE SERVER LATER ON.



/* ListType */
typedef struct  {
  SongType *song;
  SongType *head;
  SongType *tail;
} ListType;

/* Node */
typedef struct node {

} node;
