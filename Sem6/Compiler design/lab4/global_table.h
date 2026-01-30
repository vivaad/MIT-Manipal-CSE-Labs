#ifndef GLOBAL_TABLE_H
#define GLOBAL_TABLE_H

#define GSIZE 31

typedef struct GSymbol {
    char name[50];
    char type[20];
    char category[10];   // function / variable
    struct GSymbol *next;
} GSymbol;

void initGlobalTable();
void insertGlobal(char *name, char *type, char *category);
void displayGlobalTable();

#endif
