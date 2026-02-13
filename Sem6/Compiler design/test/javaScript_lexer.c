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
        "let", "const", "var", "function", "async", "await",
        "if", "else", "for", "while", "return", "class", 
        "export", "import", "default", "from", "try", "catch",
        "new", "this", "switch", "case", "break", "yield", "of"
    };
    for(int i = 0; i < 25; i++) {
        if(strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

void insert(SymbolTable *table, char *buffer, int *tableindex) {
    strcpy(table[*tableindex].lexeme, buffer);
    strcpy(table[*tableindex].type, "IDENTIFIER");
    
    if (braceCount == 0)
        strcpy(table[*tableindex].scope, "GLOBAL");
    else
        strcpy(table[*tableindex].scope, "BLOCK/FUNCTION SCOPE");
    
    (*tableindex)++;
}

int main() {
    FILE *input = fopen("script.js", "r");
    if(!input) return 1;

    SymbolTable table[1000];
    int symboltableindex = 0;
    int c;

    while((c = fgetc(input)) != EOF) {
        
        // 1. Single & Multi-line Comments (Identical to C/Java/Kotlin)
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
        
        // 2. Strings & Template Literals (Backticks)
        else if(c == '"' || c == '\'' || c == '`') {
            char quoteType = c;
            printf("[String Literal: %c", quoteType);
            while((c = fgetc(input)) != EOF && c != quoteType) {
                if(quoteType == '`' && c == '$') {
                    int next = fgetc(input);
                    if(next == '{') printf("${interpolation}");
                    else ungetc(next, input);
                }
                printf("%c", c);
            }
            printf("%c]\n", quoteType);
        }

        // 3. Identifiers & Keywords
        else if(isalpha(c) || c == '_' || c == '$') {
            char buffer[100];
            int idx = 0;
            buffer[idx++] = c;
            while((c = fgetc(input)) != EOF && (isalnum(c) || c == '_' || c == '$')) {
                buffer[idx++] = c;
            }
            buffer[idx] = '\0';
            ungetc(c, input);

            if(isKeyword(buffer)) printf("[Keyword: %s]\n", buffer);
            else {
                printf("[Identifier: %s]\n", buffer);
                // Simple check: don't duplicate in symbol table
                int found = 0;
                for(int i=0; i<symboltableindex; i++) 
                    if(strcmp(table[i].lexeme, buffer) == 0) found = 1;
                if(!found) insert(table, buffer, &symboltableindex);
            }
        }

        // 4. Strict Equality and Arrow Functions (===, !==, =>)
        else if(strchr("=!<>+-&|", c)) {
            char buffer[4] = {c, '\0', '\0', '\0'};
            int n1 = fgetc(input);
            int n2 = fgetc(input);

            if(c == '=' && n1 == '=' && n2 == '=') sprintf(buffer, "===");
            else if(c == '!' && n1 == '=' && n2 == '=') sprintf(buffer, "!==");
            else if(c == '=' && n1 == '>') { sprintf(buffer, "=>"); ungetc(n2, input); }
            else if((c == '=' || c == '!' || c == '<' || c == '>') && n1 == '=') {
                sprintf(buffer, "%c=", c); ungetc(n2, input);
            } else {
                ungetc(n2, input); ungetc(n1, input);
            }
            printf("[Operator: %s]\n", buffer);
        }

        // 5. Braces for Scope
        else if(c == '{') { printf("[Separator: {]\n"); braceCount++; }
        else if(c == '}') { printf("[Separator: }]\n"); braceCount--; }
        else if(strchr("()[];,", c)) printf("[Separator: %c]\n", c);
    }
    
    // Final step: printTable(table, symboltableindex);
    fclose(input);
    return 0;
}