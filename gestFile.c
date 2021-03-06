#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

///////////////////////////////////////////////////////////////////////////////
////////////////////////// Gestion des fichiers ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Cree un fichier dictionnaire
void CreateFile(Program* startup){
    startup->loadedFileName = malloc(sizeof(char) * 100);
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n      ------- Creer un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", startup->loadedFileName);
    strcat(startup->loadedFileName, ".dico");
    startup->f = fopen(startup->loadedFileName, "a+");
    rewind(startup->f);
    system("cls");
}

//Charge un fichier dictionnaire en m�moire
void LoadFile(Program* startup){
    char* fileName = malloc(sizeof(char) * 100);
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Charger un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", fileName);
    strcat(fileName, ".dico");
    FILE* f = fopen(fileName, "r+");
    if(f == NULL){
        system("cls");
        sprintf(startup->log, "/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
        fclose(f);
        return;
    }
    fclose(f);
    startup->loadedFileName = fileName;
    startup->f = fopen(startup->loadedFileName, "a+");
    rewind(startup->f);
    CleanDico(startup);
    FillDicoFromFile(startup);
    system("cls");
}

//Supprime du disque un fichier dictionnaire
void DeleteFile(Program* startup){
    system("cls");
    char* nameFile = malloc(sizeof(char) * 100);
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n    ------- Supprimer un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", nameFile);
    strcat(nameFile, ".dico");
    FILE* checkForDel = fopen(nameFile, "r");
    if (checkForDel == NULL){
        system("cls");
        sprintf(startup->log, "/!\\ : Le fichier dictionnaire n'existe pas.\n\n");
        return;
    }else{
        fclose(checkForDel);
        char choice;
        do{
            system("cls");
            printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n    ------- Supprimer un dictionnaire -------\n\n");
            if(startup->loadedFileName != NULL && strcmp(startup->loadedFileName, nameFile) == 0){
                printf("Etes-vous sur de vouloir supprimer ce fichier sur lequel vous etes? (o / n) : ");
            }else{
                printf("Etes-vous sur de vouloir supprimer ce fichier? (o / n) : ");
            }
            getchar();
            scanf("%c", &choice);
        }while(choice != 'o' && choice != 'n' && choice != 'O' && choice != 'N');
        switch(choice){
            case 'o':
                if(startup->loadedFileName != NULL && strcmp(startup->loadedFileName, nameFile) == 0){
                    CleanDico(startup);
                    fclose(startup->f);
                    startup->f = NULL;
                    free(startup->loadedFileName);
                    startup->loadedFileName = NULL;
                    remove(nameFile);
                }else{
                    remove(nameFile);
                }
                break;
            case 'n':
                system("cls");
                sprintf(startup->log, "/!\\ : Operation annulee.\n\n");
                return;
                break;
        }

    }
    system("cls");
    sprintf(startup->log, "/!\\ : Le fichier dictionnaire a ete detruit.\n\n");
    free(nameFile);
    return;
}

//Cree un fichier dictionnaire en fonction d'un texte dans un fichier .txt
void BuildALibFromText(Program* startup){
    char* fileName = malloc(sizeof(char) * 100);
    system("cls");
    printf("           ------- Dictionnaire C -------\n------- Gestion des fichiers dictionnaire -------\n     ------- Charger un dictionnaire -------\n\n");
    printf("Nom du fichier : ");
    scanf("%s", fileName);
    strcat(fileName, ".txt");
    FILE* f = fopen(fileName, "r+");
    if(f == NULL){
        if(startup->f != NULL){
            system("cls");
            sprintf(startup->log, "/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
            return;
        }
        system("cls");
        sprintf(startup->log, "/!\\ : Fichier non trouve, veuillez reessayer.\n\n");
        fclose(f);
        return;
    }
    fclose(f);
    startup->loadedFileName = fileName;
    startup->f = fopen(startup->loadedFileName, "a+");
    rewind(startup->f);
    FillDicoFromTextFile(startup);
    system("cls");
}

//Verifie si le fichier est vide
int IsFileEmpty(FILE *file){
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        rewind(file);
        return 1;
    }
    rewind(file);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
