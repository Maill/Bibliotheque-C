#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Structures ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Structure pour rangement ordonne des mots en memoire.
//Le but etant de faciliter l'acces des mots par rapport a un fichier.
//Cela permet de pouvoir chercher/ajouter/trier un mot sans a avoir a traiter un fichier entier et/ou tableau entier
#define INIT_CAPACITY 50 //Capacite de base du tableau de mots
struct Library {
	char letter; //1 lettre de l'alphabet qui determine la place d'un mot dans sa structure approprie
	int capacity;
	int size; //Taille du dictionnaire
	char** words; //Tableau de mots
};
typedef struct Library Lib;

//Structure principale du programme.
//Cette structure a pour interet de pouvoir acceder toutes
//nos données en 1 seul point
struct Program {
	char* loadedFileName; //Nom du fichier charge en memoire
	FILE* f; //Pointeur du fichier
	Lib* dictionary; //Tableau de "Library"
	int totalWords; //Nombre de mots total
	char* log;
};
typedef struct Program Program;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Prototypes ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Prototypes main.c
void FileMenu(Program*);
void DicoMenu(Program*);
Program* InitMain();

//Prototypes gestBib.c
//  - Load Lib
void InitLibrary(Program*);
void FillDicoFromFile(Program*);
void FillDico(Program*);
void FillDicoFromTextFile(Program*);
//  - Lib's operations
void CountTotalWords(Program*);
void ToLowerCase(char*);
void SortDico(Program*, int);
int CheckIfExists(Program*, int, char*);
void WriteOnFile(Program*);
void OverrideCapacity(Program*, int);
void CleanDico(Program*);
void SearchWord(Program*);

//Prototypes gestFile.c
void CreateFile(Program*);
void LoadFile(Program*);
void DeleteFile(Program*);
void BuildALibFromText(Program*);
int IsFileEmpty(FILE*);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif // INIT_H_INCLUDED
