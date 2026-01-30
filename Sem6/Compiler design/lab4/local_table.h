#ifndef LOCAL_TABLE_H
#define LOCAL_TABLE_H

#define LSIZE 31

typedef struct LSymbol {
    char name[50];
    char type[20];
    int size;
    struct LSymbol *next;
} LSymbol;

typedef struct LocalTable {
    char func[50];
    LSymbol *table[LSIZE];
    struct LocalTable *next;
} LocalTable;

void initLocalTables();
void createLocalTable(char *func);
void insertLocal(char *func, char *name, char *type);
void displayLocalTables();

#endif
