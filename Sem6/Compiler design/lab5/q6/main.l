%{
#include <stdio.h>
int numbers=0;
%}

%option noyywrap

%%
[0-9]+   { numbers++; }
\n       { return 0; }
.        
%%

int main(){
    yylex();
    printf("Numbers:%d\n",numbers);
    return 0;
}
