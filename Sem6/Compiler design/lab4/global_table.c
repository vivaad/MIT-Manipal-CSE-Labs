#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_table.h"

GSymbol *gtable[GSIZE];

static int hash(char *s) {
    int h = 0;
    for (int i = 0; s[i]; i++)
        h = (h + s[i]) % GSIZE;
    return h;
}

void initGlobalTable() {
    for (int i = 0; i < GSIZE; i++)
        gtable[i] = NULL;
}

void insertGlobal(char *name, char *type, char *category) {
    int idx = hash(name);
    GSymbol *t = gtable[idx];

    while (t) {
        if (strcmp(t->name, name) == 0)
            return;
        t = t->next;
    }

    GSymbol *n = malloc(sizeof(GSymbol));
    strcpy(n->name, name);
    strcpy(n->type, type);
    strcpy(n->category, category);
    n->next = gtable[idx];
    gtable[idx] = n;
}

void displayGlobalTable() {
    printf("\nGLOBAL SYMBOL TABLE\n");
    printf("-------------------------------------------\n");
    printf("NAME\t\tTYPE\t\tCATEGORY\n");
    printf("-------------------------------------------\n");

    for (int i = 0; i < GSIZE; i++) {
        GSymbol *t = gtable[i];
        while (t) {
            printf("%-12s %-12s %s\n",
                   t->name, t->type, t->category);
            t = t->next;
        }
    }
}
