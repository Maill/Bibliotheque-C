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

//Fonction de comparaison pour qsort()
static int compare(const void *a, const void *b){
   //Définie des pointeurs type et initialise avec les paramètres
   const char *pa = *(const char**)a;
   const char *pb = *(const char**)b;

   //Évalue et retourne l'état de l'évaluation (tri croissant)
   return strcmp(pa, pb);
}

void SortDico(Program* startup, int indexLib){
    qsort(startup->dictionary[indexLib].words, startup->dictionary[indexLib].size, sizeof(char*), compare);
}

//Remplit le tableau lors de l'initialisation d'un fichier
void FillDicoFromFile(Program* startup){
    while((!feof(startup->f) && !ferror(startup->f))){
        char* word = malloc(sizeof(char) * 30);
        fscanf(startup->f, "%s", word);
        ToLowerCase(word);
        int indexLib = word[0] - 97;
        int sizeLib = startup->dictionary[indexLib].size;
        startup->dictionary[indexLib].words[sizeLib] = word;
        startup->dictionary[indexLib].size++;
    }
    CountTotalWords(startup);
    int i;
    for(i = 0; i < 26; i++){
        SortDico(startup, i);
    }
    rewind(startup->f);
}

//Transforme les majuscules en minuscules
void ToLowerCase(char* word){
    int i;
    for(i = 0; i < strlen(word); i++){
        if(word[i] >= 65 && word[i] <= 90){
            word[i] += 32;
        }
    }
}

void CountTotalWords(Program* startup){
    int total = 0;
    int i;
    for(i = 0; i < 26; i++){
        total += startup->dictionary[i].size;
    }
    startup->totalWords = total;
}
