#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "local_table.h"

LocalTable *head = NULL;

int lhash(char *s) {
    int sum = 0;
    for (int i = 0; s[i]; i++)
        sum += s[i];
    return sum % LSIZE;
}

LocalTable* getTable(char *func) {
    LocalTable *t = head;
    while (t) {
        if (strcmp(t->funcName, func) == 0)
            return t;
        t = t->next;
    }
    return NULL;
}

void initLocalTables() {
    head = NULL;
}

void createLocalTable(char *funcName) {
    LocalTable *lt = malloc(sizeof(LocalTable));
    strcpy(lt->funcName, funcName);

    for (int i = 0; i < LSIZE; i++)
        lt->table[i] = NULL;

    lt->next = head;
    head = lt;
}

void insertLocal(char *funcName, char *lexeme, char *type) {
    LocalTable *lt = getTable(funcName);
    if (!lt) return;

    int idx = lhash(lexeme);
    LSymbol *t = lt->table[idx];

    while (t) {
        if (strcmp(t->lexeme, lexeme) == 0)
            return;
        t = t->next;
    }

    LSymbol *n = malloc(sizeof(LSymbol));
    strcpy(n->lexeme, lexeme);
    strcpy(n->type, type);
    n->size = 4;
    n->next = lt->table[idx];
    lt->table[idx] = n;
}

void displayLocalTables() {
    LocalTable *lt = head;

    while (lt) {
        printf("\nLOCAL SYMBOL TABLE : %s\n", lt->funcName);
        printf("-----------------------------\n");
        printf("LEXEME\tTYPE\tSIZE\n");

        for (int i = 0; i < LSIZE; i++) {
            LSymbol *t = lt->table[i];
            while (t) {
                printf("%-8s %-6s %d\n",
                       t->lexeme, t->type, t->size);
                t = t->next;
            }
        }
        lt = lt->next;
    }
}

