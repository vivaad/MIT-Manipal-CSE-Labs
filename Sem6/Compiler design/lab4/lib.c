/* lib.c */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* ================= TOKEN STRUCT ================= */

typedef struct {
    char lexeme[50];
    char type[30];
    int row;
    int col;
} Token;

/* ================= KEYWORD CHECK ================= */

int isKeyword(char *w) {
    char *k[] = {
        "auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"
    };

    int l = 0, r = 31, m, c;

    while (l <= r) {
        m = l + (r - l) / 2;
        c = strcmp(w, k[m]);
        if (c == 0) return 1;
        if (c < 0) r = m - 1;
        else l = m + 1;
    }
    return 0;
}

/* ================= COMMENT REMOVAL ================= */

void removeComments(FILE *src, FILE *dst) {
    char c, next;

    while ((c = fgetc(src)) != EOF) {

        /* Possible comment start */
        if (c == '/') {
            next = fgetc(src);

            /* Single-line comment */
            if (next == '/') {
                while ((c = fgetc(src)) != '\n' && c != EOF);
            }

            /* Multi-line comment */
            else if (next == '*') {
                char prev = 0;
                while ((c = fgetc(src)) != EOF) {
                    if (prev == '*' && c == '/')
                        break;
                    prev = c;
                }
            }

            /* Not a comment */
            else {
                fputc(c, dst);
                fseek(src, -1, SEEK_CUR);
            }
        }

        /* Normal character */
        else {
            fputc(c, dst);
        }
    }
}


/* ================= PREPROCESSOR REMOVAL ================= */

void removePreprocessor(FILE *src, FILE *dst) {
    char c;
    while ((c = fgetc(src)) != EOF) {
        if (c == '#') {
            while (c != '\n' && c != EOF)
                c = fgetc(src);
        } else {
            fputc(c, dst);
        }
    }
}

/* ================= TOKEN HELPERS ================= */

int isArithmetic(char c) {
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='%');
}

int isSpecialSymbol(char c) {
    char s[] = ";,(){}[]";
    for (int i = 0; s[i]; i++)
        if (c == s[i]) return 1;
    return 0;
}

int isIdentifier(char *w) {
    if (!isalpha(w[0]) && w[0] != '_') return 0;
    for (int i = 1; w[i]; i++)
        if (!isalnum(w[i]) && w[i] != '_') return 0;
    return 1;
}

int isNumber(char *w) {
    int dot = 0;
    for (int i = 0; w[i]; i++) {
        if (w[i] == '.') dot++;
        else if (!isdigit(w[i])) return 0;
    }
    return dot <= 1;
}

/* ================= GET NEXT TOKEN ================= */

Token getNextToken(FILE *fp) {
    Token t;
    char c, buffer[50];
    int i = 0;
    static int row = 1, col = 0;

    t.lexeme[0] = '\0';

    while ((c = fgetc(fp)) != EOF) {
        col++;

        if (c == '\n') {
            row++;
            col = 0;
            continue;
        }

        if (isspace(c)) continue;

        t.row = row;
        t.col = col;

        /* String literal (ignored content) */
        if (c == '"') {
            while ((c = fgetc(fp)) != '"' && c != EOF);
            strcpy(t.lexeme, "\"...\"");
            strcpy(t.type, "STRING_LITERAL");
            return t;
        }

        /* Identifier / Keyword */
        if (isalpha(c) || c == '_') {
            buffer[i++] = c;
            while (isalnum(c = fgetc(fp)) || c == '_') {
                buffer[i++] = c;
                col++;
            }
            buffer[i] = '\0';
            fseek(fp, -1, SEEK_CUR);

            strcpy(t.lexeme, buffer);
            strcpy(t.type, isKeyword(buffer) ? "KEYWORD" : "IDENTIFIER");
            return t;
        }

        /* Number */
        if (isdigit(c)) {
            buffer[i++] = c;
            while (isdigit(c = fgetc(fp)) || c == '.') {
                buffer[i++] = c;
                col++;
            }
            buffer[i] = '\0';
            fseek(fp, -1, SEEK_CUR);

            strcpy(t.lexeme, buffer);
            strcpy(t.type, "NUMBER");
            return t;
        }

        /* Arithmetic operator */
        if (isArithmetic(c)) {
            t.lexeme[0] = c;
            t.lexeme[1] = '\0';
            strcpy(t.type, "ARITHMETIC_OP");
            return t;
        }

        /* Relational operator */
        if (c=='<'||c=='>'||c=='='||c=='!') {
            char n = fgetc(fp);
            buffer[0] = c;
            buffer[1] = n;
            buffer[2] = '\0';

            if (!strcmp(buffer,"<=")||!strcmp(buffer,">=")||
                !strcmp(buffer,"==")||!strcmp(buffer,"!=")) {
                strcpy(t.lexeme, buffer);
            } else {
                fseek(fp, -1, SEEK_CUR);
                t.lexeme[0] = c;
                t.lexeme[1] = '\0';
            }
            strcpy(t.type, "RELATIONAL_OP");
            return t;
        }

        /* Special symbol */
        if (isSpecialSymbol(c)) {
            t.lexeme[0] = c;
            t.lexeme[1] = '\0';
            strcpy(t.type, "SPECIAL_SYMBOL");
            return t;
        }
    }

    strcpy(t.type, "EOF");
    return t;
}

