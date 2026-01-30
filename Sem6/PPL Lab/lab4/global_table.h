#ifndef GLOBAL_TABLE_H
#define GLOBAL_TABLE_H

#define GSIZE 30

typedef struct GSymbol {
    char lexeme[50];        // function name
    char returnType[20];
    struct GSymbol *next;
} GSymbol;

void initGlobalTable();
void insertGlobal(char *lexeme, char *retType);
GSymbol* searchGlobal(char *lexeme);
void displayGlobalTable();

#endif

