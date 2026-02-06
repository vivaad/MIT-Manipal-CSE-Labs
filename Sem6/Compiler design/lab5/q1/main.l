%{
int ccount=0;
int vcount=0;
%}


%%
[aeiouAEIOU] {vcount++;}
[a-zA-Z] {ccount++;}
\n {return 0;}
%%


int yywrap(){}

int main(){
	yylex();
	printf("Vowels:%d, \tConsonents:%d\n", vcount, ccount);
	return 0;
}

