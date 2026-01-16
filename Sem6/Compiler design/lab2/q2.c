#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *fr, *fw;
    char line[1024];
    
    fr = fopen("q1.c", "r");
    fw = fopen("qr2.c", "w");
    
    while (fgets(line, sizeof(line), fr) != NULL) {
        char *ptr = line;
        
        while (*ptr && isspace(*ptr)) {
            ptr++;
        }
        
        if (*ptr != '#') {
            fputs(line, fw);
        }
    }
    
    fclose(fr);
    fclose(fw);
    
    return 0;
}