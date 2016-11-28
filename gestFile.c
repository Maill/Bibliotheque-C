#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

void CreateFile(Program* startup){
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n      ------- Creer un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", (char*)startup->loadedFileName);
    strcat((char*)startup->loadedFileName, ".dico");
    startup->f = fopen((char*)startup->loadedFileName, "a+");
    rewind(startup->f);
    system("cls");
}

void LoadFile(Program* startup){
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Charger un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", (char*)startup->loadedFileName);
    strcat((char*)startup->loadedFileName, ".dico");
    FILE* f = fopen((char*)startup->loadedFileName, "r+");
    if(f == NULL){
        if(startup->f != NULL){
            system("cls");
            printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
            return;
        }
        *startup->loadedFileName = NULL;
        system("cls");
        printf("/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
        fclose(f);
        return;
    }
    fclose(f);
    startup->f = fopen((char*)startup->loadedFileName, "a+");
    rewind(startup->f);
    //CleanDico(startup);
    //FillDicoFromFile(startup);
    system("cls");
}
