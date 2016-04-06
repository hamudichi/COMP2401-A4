// Hello, I will encrypt the crap out of anything.
// You are freaken welcome boss
#include "headers.h" // don't worry, the include guards are there

/*
 * This is a very very weak and simple encryption, the only reason for it 
 * to exist in my code, so that I can get into the habbit of encryption any
 * program that needs tor "reach-out" or in other words use the network.
 *
 * Also since I am here let me spit out some logic of encryption, yo'
 * Ok we get a BIIGGG string of random characters, and randomly BUT
 * in known steps (which negates it being random but whatever :)
 * replace and move our message and integrate it with the massive string
 * that way if someone tries to sniff out packets, they won't be able to
 * know what the hell is going on ! Except if it was me ... well then
 * MUAHAHAHHAHAHAHAH ... 
 *
 * I think I need help, I enjoy programming like this... I do not believe it
 * professional ... is it?! 
 */


void encrypt(char *pass){
 for (int i = 0; i < strlen(pass); ++i) { pass[i] = pass[i] + 0xFE1; }
}

void decrypt(char *pass){
 for (int i = 0; i < strlen(pass); ++i) { pass[i] = pass[i] - 0xFE1; }
}

