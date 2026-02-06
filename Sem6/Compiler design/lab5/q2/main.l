%{
#include <stdio.h>
int w = 0, c = 0, b = 0, l = 1;
%}

%option noyywrap

%%
[A-Za-z]+     { w++; c += yyleng; }
[ \t]+        { b += yyleng; c += yyleng; }
\n            { l++; c++; }
.             { c++; }
%%

int main() {
    yylex();

    printf("\nWords      : %d\n", w);
    printf("Characters : %d\n", c);
    printf("Blanks     : %d\n", b);
    printf("Lines      : %d\n", l);

    return 0;
}
