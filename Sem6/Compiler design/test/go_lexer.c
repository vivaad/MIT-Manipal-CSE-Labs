#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int braceCount = 0;

typedef struct SymbolTable {
    char lexeme[100];
    char type[100];
    char scope[100];
} SymbolTable;

int isKeyword(char* buffer) {
    char keywords[25][20] = {
        "break", "default", "func", "interface", "select",
        "case", "defer", "go", "map", "struct",
        "chan", "else", "goto", "package", "switch",
        "const", "fallthrough", "if", "range", "type",
        "continue", "for", "import", "return", "var"
    };
    for(int i = 0; i < 25; i++) {
        if(strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

void insert(SymbolTable *table, char *buffer, int *tableindex) {
    strcpy(table[*tableindex].lexeme, buffer);
    strcpy(table[*tableindex].type, "IDENTIFIER");
    
    // Go Scoping (Simplified)
    if (braceCount == 0)
        strcpy(table[*tableindex].scope, "PACKAGE LEVEL");
    else
        strcpy(table[*tableindex].scope, "FUNCTION/LOCAL");
    
    (*tableindex)++;
}

int main() {
    FILE *input = fopen("main.go", "r");
    if(!input) return 1;

    SymbolTable table[1000];
    int symboltableindex = 0;
    int c;

    while((c = fgetc(input)) != EOF) {
        
        // 1. Comments (Same as C)
        if(c == '/') {
            int next = fgetc(input);
            if(next == '/') {
                while((c = fgetc(input)) != EOF && c != '\n');
            } else if(next == '*') {
                while((c = fgetc(input)) != EOF) {
                    if(c == '*') {
                        if((c = fgetc(input)) == '/') break;
                        ungetc(c, input);
                    }
                }
            } else {
                ungetc(next, input);
                printf("[Operator: /]\n");
            }
        }
        
        // 2. Raw String Literals (Backticks)
        else if(c == '`') {
            printf("[Raw String: `");
            while((c = fgetc(input)) != EOF && c != '`') {
                printf("%c", c);
            }
            printf("`]\n");
        }

        // 3. Identifiers & Keywords
        else if(isalpha(c) || c == '_') {
            char buffer[100];
            int idx = 0;
            buffer[idx++] = c;
            while((c = fgetc(input)) != EOF && (isalnum(c) || c == '_')) {
                buffer[idx++] = c;
            }
            buffer[idx] = '\0';
            ungetc(c, input);

            if(isKeyword(buffer)) printf("[Keyword: %s]\n", buffer);
            else {
                printf("[Identifier: %s]\n", buffer);
                int found = 0;
                for(int i=0; i<symboltableindex; i++) 
                    if(strcmp(table[i].lexeme, buffer) == 0) found = 1;
                if(!found) insert(table, buffer, &symboltableindex);
            }
        }

        // 4. Go Specific Operators (:=, <-, ...)
        else if(strchr(":=<>-!&|", c)) {
            int next = fgetc(input);
            if(c == ':' && next == '=') printf("[Operator: := (Short Decl)]\n");
            else if(c == '<' && next == '-') printf("[Operator: <- (Channel)]\n");
            else if(c == '&' && next == '^') printf("[Operator: &^ (Bit Clear)]\n");
            else {
                ungetc(next, input);
                printf("[Operator: %c]\n", c);
            }
        }

        // 5. Braces & Scope
        else if(c == '{') { printf("[Separator: {]\n"); braceCount++; }
        else if(c == '}') { printf("[Separator: }]\n"); braceCount--; }
        else if(strchr("()[];,", c)) printf("[Separator: %c]\n", c);
        
        else if(isspace(c)) continue;
    }
    
    fclose(input);
    return 0;
}