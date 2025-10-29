#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b){
	if(a==0||b==0)
		return a>b?a:b;
	int i = a>b ? b : a;
	while(a%i!=0||b%i!=0){
		i--;
	}
	return i;
}

void main(){
	int a, b;
	printf("Enter 2 numbers:");
	scanf("%d %d", &a, &b);
	printf("GCD: %d", gcd(a,b));
}
