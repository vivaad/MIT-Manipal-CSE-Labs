/* analyser.c */
#include <stdio.h>
#include <string.h>

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

        /* ===== Store unique KEYWORDS ===== */
        if (strcmp(t.type, "KEYWORD") == 0) {
            if (!alreadySeen(seenKeywords, seenKeywordCount, t.lexeme)) {
                tokens[tokenCount++] = t;
                markSeen(seenKeywords, &seenKeywordCount, t.lexeme);
            }
        }

        /* ===== Store unique OPERATORS ===== */
        else if (strstr(t.type, "OP") != NULL) {
            if (!alreadySeen(seenOperators, seenOperatorCount, t.lexeme)) {
                tokens[tokenCount++] = t;
                markSeen(seenOperators, &seenOperatorCount, t.lexeme);
            }
        }

        /* ===== Store unique SPECIAL SYMBOLS ===== */
        else if (strcmp(t.type, "SPECIAL_SYMBOL") == 0) {
            if (!alreadySeen(seenSymbols, seenSymbolCount, t.lexeme)) {
                tokens[tokenCount++] = t;
                markSeen(seenSymbols, &seenSymbolCount, t.lexeme);
            }
        }

        /* ===== Store all other tokens ===== */
        else {
            tokens[tokenCount++] = t;
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

    return 0;
}

