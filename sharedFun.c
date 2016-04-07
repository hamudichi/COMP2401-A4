// Shared functions between client and server

#include "headers.h"

void SongStructToString (SongType song, char *string) {
  /* Converting SongType structure to string to send to server */
  /* song.name + song.artist + song.album + song.duration
   **/
  char *tempToSendString = (char*) malloc(sizeof(char));
  tempToSendString;
  strcat(song.name,song.artist);
  strcat(song.name,song.album);
  //strcat(song.name, 
  string = song.name;
  free(tempToSendString);
}

void StringToSongStruct (char string, SongType *song){
  /* Converting back to struct */
  
}
