// To count the number of lines and characters in a file. 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE *fp;
	int ch;
	int lines = 0, characters=0;

	if(argc !=2){
		printf("Usage: %s <filename>\n", argv[0]);
        return 1;
	}

	fp = fopen(argv[1], "r");
	if(fp==NULL){
		perror("Error opening file!!");
		return 1;
	}

	while((ch=getc(fp)) != EOF){
		characters++;
		if(ch=='\n')
			lines++;
	}

	fclose(fp);

    printf("Number of lines      : %d\n", lines);
    printf("Number of characters : %d\n", characters);

    return 0;
}
