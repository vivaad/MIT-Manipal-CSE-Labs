#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "local_table.h"

static LocalTable *head = NULL;

static int hash(char *s) {
    int h = 0;
    for (int i = 0; s[i]; i++)
        h = (h + s[i]) % LSIZE;
    return h;
}

static LocalTable* findTable(char *func) {
    LocalTable *t = head;
    while (t) {
        if (strcmp(t->func, func) == 0)
            return t;
        t = t->next;
    }
    return NULL;
}

void initLocalTables() {
    head = NULL;
}

void createLocalTable(char *func) {
    LocalTable *lt = malloc(sizeof(LocalTable));
    strcpy(lt->func, func);
    for (int i = 0; i < LSIZE; i++)
        lt->table[i] = NULL;
    lt->next = head;
    head = lt;
}

void insertLocal(char *func, char *name, char *type) {
    LocalTable *lt = findTable(func);
    if (!lt) return;

    int idx = hash(name);
    LSymbol *t = lt->table[idx];

    while (t) {
        if (strcmp(t->name, name) == 0)
            return;
        t = t->next;
    }

    LSymbol *n = malloc(sizeof(LSymbol));
    strcpy(n->name, name);
    strcpy(n->type, type);
    n->size = 4;
    n->next = lt->table[idx];
    lt->table[idx] = n;
}

void displayLocalTables() {
    LocalTable *lt = head;

    while (lt) {
        printf("\nLOCAL SYMBOL TABLE : %s\n", lt->func);
        printf("-----------------------------\n");
        printf("NAME\tTYPE\tSIZE\n");

        for (int i = 0; i < LSIZE; i++) {
            LSymbol *t = lt->table[i];
            while (t) {
                printf("%-8s %-6s %d\n",
                       t->name, t->type, t->size);
                t = t->next;
            }
        }
        lt = lt->next;
    }
}
