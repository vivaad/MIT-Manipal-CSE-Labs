#ifndef LOCAL_TABLE_H
#define LOCAL_TABLE_H

#define LSIZE 30

typedef struct LSymbol {
    char lexeme[50];
    char type[20];
    int size;
    struct LSymbol *next;
} LSymbol;

typedef struct LocalTable {
    char funcName[50];
    LSymbol *table[LSIZE];
    struct LocalTable *next;
} LocalTable;

void initLocalTables();
void createLocalTable(char *funcName);
void insertLocal(char *funcName, char *lexeme, char *type);
void displayLocalTables();

#endif

