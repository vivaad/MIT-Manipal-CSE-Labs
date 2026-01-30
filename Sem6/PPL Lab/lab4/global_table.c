#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_table.h"

GSymbol *gTable[GSIZE];

int ghash(char *s) {
    int sum = 0;
    for (int i = 0; s[i]; i++)
        sum += s[i];
    return sum % GSIZE;
}

void initGlobalTable() {
    for (int i = 0; i < GSIZE; i++)
        gTable[i] = NULL;
}

GSymbol* searchGlobal(char *lexeme) {
    int idx = ghash(lexeme);
    GSymbol *t = gTable[idx];
    while (t) {
        if (strcmp(t->lexeme, lexeme) == 0)
            return t;
        t = t->next;
    }
    return NULL;
}

void insertGlobal(char *lexeme, char *retType) {
    if (searchGlobal(lexeme))
        return;

    GSymbol *n = malloc(sizeof(GSymbol));
    strcpy(n->lexeme, lexeme);
    strcpy(n->returnType, retType);
    n->next = NULL;

    int idx = ghash(lexeme);
    n->next = gTable[idx];
    gTable[idx] = n;
}

void displayGlobalTable() {
    printf("\nGLOBAL SYMBOL TABLE\n");
    printf("----------------------------------\n");
    printf("LEXEME\t\tRETURN TYPE\n");
    printf("----------------------------------\n");

    for (int i = 0; i < GSIZE; i++) {
        GSymbol *t = gTable[i];
        while (t) {
            printf("%-12s %s\n", t->lexeme, t->returnType);
            t = t->next;
        }
    }
}

