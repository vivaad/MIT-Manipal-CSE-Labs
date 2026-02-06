%{
#include <stdio.h>
int digits=0, letters=0, others=0;
%}

%option noyywrap

%%
[0-9]        { digits++; }
[a-zA-Z]     { letters++; }
\n           { return 0; }
.            { others++; }
%%

int main(){
    yylex();
    printf("Digits:%d\nLetters:%d\nOthers:%d\n",digits,letters,others);
    return 0;
}
