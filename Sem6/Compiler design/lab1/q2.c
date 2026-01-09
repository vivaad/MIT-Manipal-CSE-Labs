#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv) {
    FILE *sourceFile, *destFile;
    char ch;
    long fileSize, i;


    sourceFile = fopen( "q1.c", "r");
    if (sourceFile == NULL) {
        printf("Error: Could not open source file.\n");
        return 1;
    }


    destFile = fopen("output.txt", "w");
    if (destFile == NULL) {
        printf("Error: Could not open destination file.\n");
        fclose(sourceFile);
        return 1;
    }

    fseek(sourceFile, 0, SEEK_END);
    fileSize = ftell(sourceFile); 

    printf("The size of the file is: %ld bytes\n", fileSize);

    for (i = fileSize - 1; i >= 0; i--) {
        fseek(sourceFile, i, SEEK_SET); 
        ch = fgetc(sourceFile);      
        fputc(ch, destFile);    
    }

    printf("File reversed successfully and stored in 'output.txt'.\n");

    fclose(sourceFile);
    fclose(destFile);

    return 0;
}
