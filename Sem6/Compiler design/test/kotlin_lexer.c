#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int braceCount = 0;
int parenthesisCount = 0;

typedef struct SymbolTable {
    char lexeme[100];
    char type[100];
    char scope[100];
} SymbolTable;

// Kotlin specific keyword list
int isKeyword(char* buffer) {
    char keywords[20][20] = {
        "package", "import", "class", "fun", "val", "var", 
        "if", "else", "when", "for", "while", "do", "return", 
        "true", "false", "null", "as", "is", "in", "this"
    };
    for(int i = 0; i < 20; i++) {
        if(strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

// Same lookup logic as before
int lookup(SymbolTable *table, char *buffer, int tableindex) {
    for(int i = 0; i < tableindex; i++) {
        if(strcmp(table[i].lexeme, buffer) == 0) return 1;
    }
    return 0;
}

void insert(SymbolTable *table, char *buffer, int tableindex) {
    strcpy(table[tableindex].lexeme, buffer);
    strcpy(table[tableindex].type, "IDENTIFIER");
    
    // Kotlin Scope Heuristics
    if (braceCount == 0)
        strcpy(table[tableindex].scope, "TOP-LEVEL/PACKAGE");
    else if (braceCount == 1)
        strcpy(table[tableindex].scope, "CLASS/OBJECT MEMBER");
    else
        strcpy(table[tableindex].scope, "LOCAL (FUNCTION)");
}

// ... printTable function remains the same ...

int main() {
    FILE *input = fopen("kotlin_sample.kt", "r"); 
    if(input == NULL) {
        printf("Error: Could not open sample.kt\n");
        return 0;
    }

    SymbolTable table[1000];
    int symboltableindex = 0;
    int c;

    while((c = fgetc(input)) != EOF) {
        
        // 1. Handle Comments (Same as Java/C)
        if(c == '/') {
            int next = fgetc(input);
            if(next == '/') {
                while((c = fgetc(input)) != EOF && c != '\n');
            }
            else if(next == '*') {
                while((c = fgetc(input)) != EOF) {
                    if(c == '*') {
                        if((c = fgetc(input)) == '/') break;
                        ungetc(c, input);
                    }
                }
            }
            else {
                ungetc(next, input);
                printf("[Operator: /]\n");
            }
        }
        
        // 2. String Templates (Kotlin specific: "${var}")
        else if(c == '"') {
            printf("[String: \"");
            while((c = fgetc(input)) != EOF && c != '"') {
                if(c == '$') printf("(Template)"); // Simple detection of $
                printf("%c", c);
            }
            printf("\"]\n");
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

            if(isKeyword(buffer)) {
                printf("[Keyword: %s]\n", buffer);
            } else {
                printf("[Identifier: %s]\n", buffer);
                if(!lookup(table, buffer, symboltableindex)) {
                    insert(table, buffer, symboltableindex++);
                }
            }
        }

        // 4. Kotlin Operators (?.  !!  ::  ->)
        else if(strchr("?.!:->", c)) {
            int next = fgetc(input);
            if(c == '?' && next == '.') printf("[Safe Call: ?.]\n");
            else if(c == '!' && next == '!') printf("[Null-Assert: !!]\n");
            else if(c == ':' && next == ':') printf("[Ref: ::]\n");
            else if(c == '-' && next == '>') printf("[Arrow: ->]\n");
            else {
                ungetc(next, input);
                if(strchr("{}();,", c)) {
                     printf("[Separator: %c]\n", c);
                     if(c == '{') braceCount++;
                     if(c == '}') braceCount--;
                } else {
                     printf("[Operator/Sym: %c]\n", c);
                }
            }
        }

        // 5. Handle Numbers (simplified)
        else if(isdigit(c)) {
            while((c = fgetc(input)) != EOF && (isdigit(c) || c == '.' || c == 'f' || c == 'L'));
            ungetc(c, input);
            printf("[Number Literal]\n");
        }
    }

    // ... printTable call ...
    return 0;
}