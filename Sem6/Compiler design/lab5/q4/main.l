%{
#include <stdio.h>
int id=0;
%}

%option noyywrap

%%
[a-zA-Z_][a-zA-Z0-9_]*   { id++; }
\n                       { return 0; }
.                        
%%

int main(){
    yylex();
    printf("Identifiers:%d\n",id);
    return 0;
}
