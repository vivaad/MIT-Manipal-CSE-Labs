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
    char keywords[35][20] = {
        "let", "const", "var", "function", "async", "await",
        "if", "else", "for", "while", "return", "class", 
        "export", "import", "default", "from", "try", "catch",
        "new", "this", "switch", "case", "break", "interface", 
        "type", "enum", "implements", "public", "private", 
        "protected", "readonly", "as", "namespace", "abstract", "any"
    };
    for(int i = 0; i < 35; i++) {
        if(strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

void insert(SymbolTable *table, char *buffer, int *tableindex) {
    strcpy(table[*tableindex].lexeme, buffer);
    strcpy(table[*tableindex].type, "IDENTIFIER");
    strcpy(table[*tableindex].scope, (braceCount == 0) ? "GLOBAL/MODULE" : "BLOCK/CLASS");
    (*tableindex)++;
}

int main() {
    FILE *input = fopen("app.ts", "r");
    if(!input) return 1;

    SymbolTable table[1000];
    int symboltableindex = 0;
    int c;

    while((c = fgetc(input)) != EOF) {
        
        // 1. Comments (Same as JS)
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
        
        // 2. String Literals & Backticks (Same as JS)
        else if(c == '"' || c == '\'' || c == '`') {
            char quoteType = c;
            printf("[String: ");
            while((c = fgetc(input)) != EOF && c != quoteType) printf("%c", c);
            printf("]\n");
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
                int found = 0;
                for(int i=0; i<symboltableindex; i++) 
                    if(strcmp(table[i].lexeme, buffer) == 0) found = 1;
                if(!found) insert(table, buffer, &symboltableindex);
            }
        }

        // 4. TS Specific Operators (?. , !. , ===, =>)
        else if(strchr("!?.=:<>", c)) {
            int next = fgetc(input);
            if(c == '?' && next == '.') printf("[Operator: ?. (Optional Chain)]\n");
            else if(c == '!' && next == '.') printf("[Operator: !. (Non-null)]\n");
            else if(c == '=' && next == '>') printf("[Operator: => (Arrow)]\n");
            else if(c == ':' ) { printf("[Separator: : (Type Annotation)]\n"); ungetc(next, input); }
            else {
                ungetc(next, input);
                printf("[Symbol/Op: %c]\n", c);
            }
        }

        // 5. Braces & Scoping
        else if(c == '{') { printf("[Separator: {]\n"); braceCount++; }
        else if(c == '}') { printf("[Separator: }]\n"); braceCount--; }
        else if(strchr("()[];,", c)) printf("[Separator: %c]\n", c);
    }
    
    fclose(input);
    return 0;
}