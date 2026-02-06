%{
#include <stdio.h>
int words=0, lines=0;
%}

%option noyywrap

%%
[A-Za-z]+   { words++; }
\n          { lines++; }
.           
%%

int main(){
    yylex();
    printf("Words:%d\nLines:%d\n",words,lines);
    return 0;
}
