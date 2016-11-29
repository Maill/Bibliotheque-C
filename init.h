#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#define INIT_CAPACITY 50

struct Library {
	char letter; //Première lettre des mots du tableau
	int capacity;
	int size; //Taille du dictionnaire
	char** words; //Tableau de mots
};

typedef struct Library Lib;


struct Program {
	char* loadedFileName;
	FILE* f;
	Lib* dictionary;
	int totalWords;
};

typedef struct Program Program;

//Protorypes main.c
void FileMenu(Program*);
void DicoMenu(Program*);

//Prototypes gestBib.c
//  - Load Lib
void InitLibrary(Program*);
void FillDicoFromFile(Program*);
void FillDico(Program*);
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

#endif // INIT_H_INCLUDED
