//Wap that merges lines alternatively from 2 files and stores it in a resultant file. 

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024

int main() {
    FILE *f1, *f2, *res;
    char line1[MAX_LINE], line2[MAX_LINE];
    int file1_done = 0, file2_done = 0;

    f1 = fopen("q1.c", "r");
    f2 = fopen("q2.c", "r");
    res = fopen("merged.txt", "w");

    if (f1 == NULL || f2 == NULL || res == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    while (!file1_done || !file2_done) {
        if (fgets(line1, MAX_LINE, f1) != NULL) {
            fputs(line1, res);
        } else {
            file1_done = 1;
        }

        if (fgets(line2, MAX_LINE, f2) != NULL) {
            fputs(line2, res);
        } else {
            file2_done = 1;
        }
    }

    printf("Files merged alternatively into 'merged.txt' successfully.\n");

    fclose(f1);
    fclose(f2);
    fclose(res);

    return 0;
}
