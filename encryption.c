// Hello, I will encrypt the crap out of anything.
// You are freaken welcome boss
#include "headers.h" // don't worry, the include guards are there

/*
 * This is a very very weak and simple encryption, the only reason for it 
 * to exist in my code, so that I can get into the habbit of encryption any
 * program that needs tor "reach-out" or in other words use the network.
 */

void encrypt(char *pass){
 for (int i = 0; i < strlen(pass); ++i) { pass[i] = pass[i] + 1; }
}

void decrypt(char *pass){
 for (int i = 0; i < strlen(pass); ++i) { pass[i] = pass[i] - 1; }
}

