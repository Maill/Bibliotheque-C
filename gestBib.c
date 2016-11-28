#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

//Initialisation du tableau de la bibliotheque
void InitLibrary(Program* startup){
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	startup->dictionary = malloc(sizeof(Lib) * 26);
	int i;
	for (i = 0; i < 26; i++) {
		startup->dictionary[i].letter = alphabet[i];
		startup->dictionary[i].capacity = 30000;
		startup->dictionary[i].size = 0;
		startup->dictionary[i].words = malloc(sizeof(char*) * startup->dictionary[i].capacity);
	}
}
