#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int braceCount = 0;

int isCSharpKeyword(char* buffer) {
    char keywords[25][20] = {
        "abstract", "as", "base", "bool", "break", "byte", "case",
        "catch", "checked", "class", "const", "continue", "decimal",
        "default", "delegate", "do", "double", "else", "enum", "event",
        "finally", "fixed", "foreach", "get", "set"
    };
    for(int i = 0; i < 25; i++) {
        if(strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

int main() {
    FILE *input = fopen("source.cs", "r");
    if(!input) { printf("Error: source.cs not found\n"); return 1; }

    int c;
    while((c = fgetc(input)) != EOF) {
        if(isspace(c)) continue;

        // 1. Verbatim Strings (@"...")
        if(c == '@') {
            int next = fgetc(input);
            if(next == '"') {
                printf("[Verbatim String: @\"");
                while((c = fgetc(input)) != EOF && c != '"') printf("%c", c);
                printf("\"]\n");
            } else ungetc(next, input);
        }

        // 2. Standard Strings
        else if(c == '"') {
            printf("[String: \"");
            while((c = fgetc(input)) != EOF && c != '"') printf("%c", c);
            printf("\"]\n");
        }

        // 3. Keywords & Identifiers
        else if(isalpha(c) || c == '_') {
            char buffer[100]; int idx = 0;
            buffer[idx++] = c;
            while((c = fgetc(input)) != EOF && (isalnum(c) || c == '_')) buffer[idx++] = c;
            buffer[idx] = '\0';
            ungetc(c, input);

            if(isCSharpKeyword(buffer)) printf("[Keyword: %s]\n", buffer);
            else printf("[Identifier: %s]\n", buffer);
        }

        // 4. Operators & Symbols
        else if(strchr("=+-*/!<>?&|.", c)) {
            int next = fgetc(input);
            if(c == '?' && next == '?') printf("[Operator: ?? (Null-coalescing)]\n");
            else if(c == '=' && next == '>') printf("[Operator: => (Lambda)]\n");
            else { ungetc(next, input); printf("[Operator: %c]\n", c); }
        }

        // 5. Braces
        else if(c == '{') { braceCount++; printf("[Separator: {]\n"); }
        else if(c == '}') { braceCount--; printf("[Separator: }]\n"); }
        else if(strchr("()[];,", c)) printf("[Separator: %c]\n", c);
    }
    fclose(input);
    return 0;
}