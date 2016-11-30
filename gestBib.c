#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////// "Constructeur" de la structure //////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Initialisation du tableau de la bibliotheque
void InitLibrary(Program* startup){
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	startup->dictionary = malloc(sizeof(Lib) * 26);
	int i;
	for (i = 0; i < 26; i++) {
		startup->dictionary[i].letter = alphabet[i];
		startup->dictionary[i].capacity = INIT_CAPACITY;
		startup->dictionary[i].size = 0;
		startup->dictionary[i].words = malloc(sizeof(char*) * startup->dictionary[i].capacity);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///////////////////////// Traitement des fichiers /////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Remplit le tableau lors de l'initialisation d'un fichier dictionnaire
void FillDicoFromFile(Program* startup){
    if(IsFileEmpty(startup->f) == 1){
        CountTotalWords(startup);
        return;
    }
    while(!feof(startup->f) && !ferror(startup->f)){
        char* word = malloc(sizeof(char) * 30);
        fscanf(startup->f, "%s", word);
        ToLowerCase(word);
        int indexLib = word[0] - 97;
        int sizeLib = startup->dictionary[indexLib].size;
        if(sizeLib == (startup->dictionary[indexLib].capacity - 3)){
            OverrideCapacity(startup, indexLib);
        }
        if(CheckIfExists(startup, indexLib, word) == 0){
            startup->dictionary[indexLib].words[sizeLib] = word;
            startup->dictionary[indexLib].size++;
        }
    }
    CountTotalWords(startup);
    int i;
    for(i = 0; i < 26; i++){
        SortDico(startup, i);
    }
    WriteOnFile(startup);
}

//Remplit le tableau via la saisie utilisateur
void FillDico(Program* startup){
    char* wordIns = malloc(sizeof(char) * 30);
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Inserer un mot dans le dictionnaire -------\n\n");
    printf("Mot a inserer : ");
    scanf("%s", wordIns);
    ToLowerCase(wordIns);
    int indexLib = wordIns[0] - 97;
    int sizeLib = startup->dictionary[indexLib].size;
    if(CheckIfExists(startup, indexLib, wordIns) == 1){
        system("cls");
        printf("/!\\ : Le mot \"%s\" existe deja.\n\n", wordIns);
        return;
    }
    startup->dictionary[indexLib].words[sizeLib] = wordIns;
    startup->dictionary[indexLib].size++;
    CountTotalWords(startup);
    SortDico(startup, indexLib);
    WriteOnFile(startup);
    system("cls");
    printf("-- Le mot \"%s\" a ete insere dans le dictionnaire. --\n\n", wordIns);
    free(wordIns);
}

//Remplit le tableau à l'aide d'un texte
void FillDicoFromTextFile(Program* startup){
    char* nameOutExt;
    while(!feof(startup->f) && !ferror(startup->f)){
        char* word = malloc(sizeof(char) * 30);
        fscanf(startup->f, "%30[a-zA-Z-']%*[^a-zA-Z'-]", word);
        ToLowerCase(word);
        int indexLib = word[0] - 97;
        int sizeLib = startup->dictionary[indexLib].size;
        if(sizeLib == (startup->dictionary[indexLib].capacity - 3)){
            OverrideCapacity(startup, indexLib);
        }
        if(CheckIfExists(startup, indexLib, word) == 0){
            startup->dictionary[indexLib].words[sizeLib] = word;
            startup->dictionary[indexLib].size++;
        }
    }
    nameOutExt = strtok(startup->loadedFileName, ".");
    strcat(nameOutExt, ".dico");
    startup->loadedFileName = nameOutExt;
    CountTotalWords(startup);
    int i;
    for(i = 0; i < 26; i++){
        SortDico(startup, i);
    }
    WriteOnFile(startup);

}

//Ecrit le tableau en mémoire dans le fichier dictionnaire
void WriteOnFile(Program* startup){
    fclose(startup->f);
    fopen(startup->loadedFileName, "w+");
    int i;
    int first = 0;
    for(i = 0; i < 26; i++){
        int j;
        for(j = 0; j < startup->dictionary[i].size; j++){
            if(first == 0){
                fprintf(startup->f, "%s", startup->dictionary[i].words[j]);
                first = 1;
                continue;
            }
            fprintf(startup->f, "\n%s", startup->dictionary[i].words[j]);
        }
    }
    fclose(startup->f);
    fopen(startup->loadedFileName, "a+");
    rewind(startup->f);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///////////////////////// Operations sur tableaux /////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Allocation dynamique de la memoire des tableaux
void OverrideCapacity(Program* startup, int indexLib){
    startup->dictionary[indexLib].capacity *= 2;
    startup->dictionary[indexLib].words = realloc(startup->dictionary[indexLib].words, sizeof(char*) * startup->dictionary[indexLib].capacity);
}

//Nettoie les valeurs du tableau
void CleanDico(Program* startup){
    int i = 0;
    for(; i < 26; i++){
        int j;
        for(j = 0; j < startup->dictionary[i].size; j++){
            free(startup->dictionary[i].words[j]);
        }
        free(startup->dictionary[i].words);
        startup->dictionary[i].size = 0;
        startup->dictionary[i].capacity = INIT_CAPACITY;
        startup->dictionary[i].words = malloc(sizeof(char*) * startup->dictionary[i].capacity);
    }
    startup->totalWords = 0;
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

//Verifie si un mot existe deja dans les tableaux
int CheckIfExists(Program* startup, int indexLib, char* wordToCheck){
    int i;
    for(i = 0; i < startup->dictionary[indexLib].size;i++){
        if(strcmp(startup->dictionary[indexLib].words[i], wordToCheck) == 0){
            return 1;
        }
    }
    return 0;
}

//Compte le nombre total de mots
void CountTotalWords(Program* startup){
    int total = 0;
    int i;
    for(i = 0; i < 26; i++){
        total += startup->dictionary[i].size;
    }
    startup->totalWords = total;
}

//Fonction de recherche d'un mot
void SearchWord(Program* startup){
    char* wordSearch = malloc(sizeof(char) * 30);
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Rechercher un mot dans le dictionnaire -------\n\n");
    printf("Mot a rechercher : ");
    scanf("%s", wordSearch);
    ToLowerCase(wordSearch);
    int indexLib = wordSearch[0] - 97;
    if(CheckIfExists(startup, indexLib, wordSearch) == 1){
        system("cls");
        printf("-- Le mot \"%s\" est dans le dictionnaire. --\n\n", wordSearch);
    }else{
        system("cls");
        printf("-- Le mot \"%s\" n'existe pas dans le dictionnaire. --\n\n", wordSearch);
    }
    free(wordSearch);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////////////////////////// Tri sur tableaux /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Fonction de comparaison pour qsort()
//Note : cette fonction consiste a comparer 2 mots selon leurs poids
// ==> Grossierement : cela nous evite de calculer la somme du mot et de le
//      comparer a un autre mot
static int compare(const void *a, const void *b){
   //Définie des pointeurs type et initialise avec les paramètres
   const char *pa = *(const char**)a;
   const char *pb = *(const char**)b;

   //Évalue et retourne l'état de l'évaluation (tri croissant)
   return strcmp(pa, pb);
}

//Trie les tableaux dans l'ordre croissant
void SortDico(Program* startup, int indexLib){
    qsort(startup->dictionary[indexLib].words, startup->dictionary[indexLib].size, sizeof(char*), compare);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
