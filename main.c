#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"

Program* InitMain() {
	Program* startup = malloc(sizeof(Lib) * 1);
	startup->loadedFileName = NULL;
	startup->f = NULL;
	startup->totalWords = 0;
	return startup;
}

int main()
{
    Program* startup = InitMain();
    InitLibrary(startup);
    do{
        int choice;
        printf("------- Dictionnaire C -------\n\n");
        printf("Fichier charge : ");
        if (startup->loadedFileName == NULL) {
            printf("Aucun fichier charge\n");
        }else {
            printf("%s\n", (char*)startup->loadedFileName);
        }
        printf("Nombre total de mots : %i\n\n", startup->totalWords);
        printf("1. Fichier du dictionnaire\n2. Gestion du dictionnaire\n3. DEBUG : Vider la memoire\nChoix : ");
        scanf("%i", &choice);
        switch(choice){
            case 1:
                FileMenu(startup);
                break;
            case 2:
                //DicoMenu(startup);
                break;
            case 3:
                //CleanDico(startup);
                break;
        }
    }while (1);
    return 0;
}

void FileMenu(Program* startup){
    int choice;
    system("cls");
    printf("     ------- Dictionnaire C -------\n------- Gestion des dictionnaires -------\n\n");
    printf("1. Creer un dictionnaire\n2. Charger un dictionnaire\n3. Supprimer un dictionnaire\nChoix : ");
    scanf("%i", &choice);
    switch(choice){
        case 1:
            CreateFile(startup);
            break;
        case 2:
            LoadFile(startup);
            break;
        case 3:
            //DeleteFile(startup);
            break;
    }
}

/*void DicoMenu(Program* startup){
    if(startup->f == NULL){
        system("cls");
        printf("/!\\ : Aucun fichier dictionnaire charge, veuillez charger un fichier dictionnaire !\n\n");
        return;
    }
    int choice;
    system("cls");
    printf("     ------- Dictionnaire C -------\n------- Gestion des dictionnaires -------\n\n");
    printf("1. Inserer un mot dans le dictionnaire\n2. Rechercher un mot dans le dictionnaire\nChoix : ");
    scanf("%i", &choice);
    switch(choice){
        case 1:
            FillDico(startup);
            break;
        case 2:
            SearchWord(startup);
            break;
    }
}*/
