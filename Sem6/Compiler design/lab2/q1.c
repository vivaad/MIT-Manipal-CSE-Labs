#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fr, *fw;
    char ca, cb;

    // fr = fopen(argv[1], 'r');
    // fw = fopen(argv[2], 'w');

    fr = fopen("q1.c","r");
    fw = fopen("rq1.c","w");

    ca = getc(fr);
    while(ca!=EOF){
        if(ca==' '){
            if((cb= getc(fr))==' '){
                while((cb = getc(fr)) == ' ');
                putc('\t', fw);
            }
            putc(cb, fw);
        } else {
            putc(ca, fw);
        }
        ca = getc(fr);
    }

    fclose(fr);
    fclose(fw);
    return 0;
}