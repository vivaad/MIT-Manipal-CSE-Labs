#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "global_table.h"
#include "local_table.h"

typedef struct {
    char lexeme[50];
    char type[30];
    int row;
    int col;
} Token;

void removeComments(FILE *, FILE *);
void removePreprocessor(FILE *, FILE *);
Token getNextToken(FILE *);

char currentFunction[50] = "";
int insideFunction = 0;
char lastType[20] = "";

int main() {
    FILE *src, *noComments, *clean;
    Token t;

    initGlobalTable();
    initLocalTables();

    src = fopen("input.c", "r");
    noComments = fopen("nocomments.c", "w");
    clean = fopen("clean.c", "w");

    if (!src || !noComments || !clean) {
        printf("Error opening files.\n");
        return 1;
    }

    removeComments(src, noComments);
    fclose(src);
    fclose(noComments);

    noComments = fopen("nocomments.c", "r");
    removePreprocessor(noComments, clean);
    fclose(noComments);
    fclose(clean);

    clean = fopen("clean.c", "r");
    if (!clean) {
        printf("Error opening cleaned file.\n");
        return 1;
    }

    while (1) {
        t = getNextToken(clean);
        if (strcmp(t.type, "EOF") == 0)
            break;

        if (strcmp(t.type, "KEYWORD") == 0 &&
           (!strcmp(t.lexeme, "int") ||
            !strcmp(t.lexeme, "bool") ||
            !strcmp(t.lexeme, "void"))) {
            strcpy(lastType, t.lexeme);
        }

        if (strcmp(t.type, "IDENTIFIER") == 0) {
            Token next = getNextToken(clean);

            if (!insideFunction && strcmp(next.lexeme, "(") == 0) {
                insertGlobal(t.lexeme, lastType, "function");
                createLocalTable(t.lexeme);
                strcpy(currentFunction, t.lexeme);
                insideFunction = 1;
            }
            else if (!insideFunction) {
                insertGlobal(t.lexeme, lastType, "variable");
            }
            else {
                insertLocal(currentFunction, t.lexeme, lastType);
            }

            fseek(clean, -strlen(next.lexeme), SEEK_CUR);
        }

        if (strcmp(t.lexeme, "}") == 0 && insideFunction) {
            insideFunction = 0;
            currentFunction[0] = '\0';
        }
    }

    fclose(clean);

    displayGlobalTable();
    displayLocalTables();

    return 0;
}
