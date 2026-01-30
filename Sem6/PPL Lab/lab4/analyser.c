/* analyser.c */
#include <stdio.h>
#include <string.h>

#include "global_table.h"
#include "local_table.h"

/* ===== Must match Token definition in lib.c ===== */
typedef struct {
    char lexeme[50];
    char type[30];
    int row;
    int col;
} Token;

/* ===== Function declarations from lib.c ===== */
void removeComments(FILE *, FILE *);
void removePreprocessor(FILE *, FILE *);
Token getNextToken(FILE *);

/* ===== Token storage ===== */
Token tokens[1000];
int tokenCount = 0;

/* ===== Seen tables for unique tokens ===== */
char seenKeywords[50][30];
int seenKeywordCount = 0;

char seenOperators[50][30];
int seenOperatorCount = 0;

char seenSymbols[50][30];
int seenSymbolCount = 0;

/* ===== Helper: check if already seen ===== */
int alreadySeen(char table[][30], int count, char *lexeme) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i], lexeme) == 0)
            return 1;
    }
    return 0;
}

/* ===== Helper: mark as seen ===== */
void markSeen(char table[][30], int *count, char *lexeme) {
    strcpy(table[*count], lexeme);
    (*count)++;
}

int main() {

	initGlobalTable();
	initLocalTables();

	char currentFunction[50] = "";
	int insideFunction = 0;
	char lastType[20] = "";

    FILE *src, *noComments, *clean;
    Token t;

    /* ===== Open files ===== */
    src = fopen("input.c", "r");
    noComments = fopen("nocomments.c", "w");
    clean = fopen("clean.c", "w");

    if (!src || !noComments || !clean) {
        printf("Error opening files.\n");
        return 1;
    }

    /* ===== Step 1: Remove comments ===== */
    removeComments(src, noComments);
    fclose(src);
    fclose(noComments);

    /* ===== Step 2: Remove preprocessor directives ===== */
    noComments = fopen("nocomments.c", "r");
    removePreprocessor(noComments, clean);
    fclose(noComments);
    fclose(clean);

    /* ===== Step 3–5: Lexical analysis ===== */
    clean = fopen("clean.c", "r");
    if (!clean) {
        printf("Error opening cleaned file.\n");
        return 1;
    }

    while (1) {
    t = getNextToken(clean);
    if (strcmp(t.type, "EOF") == 0)
        break;

    /* Save last seen datatype */
    if (strcmp(t.type, "KEYWORD") == 0 &&
        (!strcmp(t.lexeme,"int") || !strcmp(t.lexeme,"bool") || !strcmp(t.lexeme,"void"))) {
        strcpy(lastType, t.lexeme);
    }

    /* Function detection */
    if (strcmp(t.type, "IDENTIFIER") == 0) {
        Token next = getNextToken(clean);

        if (strcmp(next.lexeme, "(") == 0 && !insideFunction) {
            insertGlobal(t.lexeme, lastType);
            createLocalTable(t.lexeme);
            strcpy(currentFunction, t.lexeme);
            insideFunction = 1;
        } 
        else {
            /* Normal identifier */
            if (insideFunction) {
                insertLocal(currentFunction, t.lexeme, lastType);
            }
        }

        fseek(clean, -strlen(next.lexeme), SEEK_CUR);
    }

    /* Exit function */
    if (strcmp(t.lexeme, "}") == 0 && insideFunction) {
        insideFunction = 0;
        strcpy(currentFunction, "");
    }
}


    fclose(clean);

    /* ===== Output ===== */
    printf("\nLEXEME\t\tTYPE\t\t\tROW\tCOL\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < tokenCount; i++) {
        printf("%-12s %-24s \t%d\t%d\n",
               tokens[i].lexeme,
               tokens[i].type,
               tokens[i].row,
               tokens[i].col);
    }

    displayGlobalTable();
    displayLocalTables();

    return 0;
}

