#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *w) {
    char *k[] = {
        "auto", "break", "case", "char", "const", "continue", "default", 
        "do", "double", "else", "enum", "extern", "float", "for", "goto", 
        "if", "int", "long", "register", "return", "short", "signed", 
        "sizeof", "static", "struct", "switch", "typedef", "union", 
        "unsigned", "void", "volatile", "while"
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

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    char ch, w[100];
    int i = 0, j;
    
    while ((ch = fgetc(f)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            w[i++] = ch;
        } else {
            if (i > 0) {
                w[i] = '\0';
                if (isKeyword(w)) {
                    for (j = 0; w[j]; j++)
                        w[j] = toupper(w[j]);
                }
                printf("%s", w);
                i = 0;
            }
            printf("%c", ch);
        }
    }
    
    fclose(f);
    return 0;
}