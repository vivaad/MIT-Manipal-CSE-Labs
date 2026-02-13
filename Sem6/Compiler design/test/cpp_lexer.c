#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int braceCount = 0;

typedef struct {
    char lexeme[100];
    char type[50];
} Symbol;

int isCppKeyword(char* buffer) {
    char keywords[22][20] = {
        "class", "struct", "template", "typename", "public", "private", 
        "protected", "virtual", "override", "nullptr", "this", "using", 
        "namespace", "inline", "friend", "bool", "constexpr", "explicit",
        "new", "delete", "operator", "try"
    };
    for(int i = 0; i < 22; i++) {
        if(strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

int main() {
    FILE *input = fopen("source.cpp", "r");
    if(!input) { printf("Error: source.cpp not found\n"); return 1; }

    int c;
    while((c = fgetc(input)) != EOF) {
        if(isspace(c)) continue;

        // 1. Comments & Division
        if(c == '/') {
            int next = fgetc(input);
            if(next == '/') {
                while((c = fgetc(input)) != EOF && c != '\n');
            } else if(next == '*') {
                while((c = fgetc(input)) != EOF) {
                    if(c == '*' && (c = fgetc(input)) == '/') break;
                }
            } else { ungetc(next, input); printf("[Operator: /]\n"); }
        }

        // 2. Preprocessor & Identifiers
        else if(isalpha(c) || c == '_' || c == '#') {
            char buffer[100]; int idx = 0;
            buffer[idx++] = c;
            while((c = fgetc(input)) != EOF && (isalnum(c) || c == '_')) buffer[idx++] = c;
            buffer[idx] = '\0';
            ungetc(c, input);

            if(buffer[0] == '#') printf("[Preprocessor: %s]\n", buffer);
            else if(isCppKeyword(buffer)) printf("[Keyword: %s]\n", buffer);
            else printf("[Identifier: %s]\n", buffer);
        }

        // 3. C++ Specific Operators
        else if(c == ':') {
            int next = fgetc(input);
            if(next == ':') printf("[Operator: :: (Scope)]\n");
            else { ungetc(next, input); printf("[Separator: :]\n"); }
        }
        else if(c == '-') {
            int next = fgetc(input);
            if(next == '>') printf("[Operator: -> (Member Access)]\n");
            else { ungetc(next, input); printf("[Operator: -]\n"); }
        }

        // 4. Braces & Delimiters
        else if(c == '{') { braceCount++; printf("[Separator: {]\n"); }
        else if(c == '}') { braceCount--; printf("[Separator: }]\n"); }
        else if(strchr("()[];,", c)) printf("[Separator: %c]\n", c);
    }
    fclose(input);
    return 0;
}