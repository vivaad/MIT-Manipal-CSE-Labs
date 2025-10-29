#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int opcount=0;
int* primfacts(int n){

	int* factors=(int*)malloc(100*sizeof(int));
	int t=n;
	int count=0;

	while(n%2==0){
		n=n/2;
		count++;
		factors[0]=count;
		factors[count]=2;
		opcount++;
	}
	for(int i=3;i*i<=n;i=i+2)
	{
		while(n%i==0)
		{
			count++;
			factors[count]=i;
			n=n/i;
			opcount++;
		}
	}
	if(n>2){
		opcount++;
		count++;
		factors[count]=n;
	}
	factors[0]=count;
	return factors;
}
void gcd(int* a, int* b){
	int gcd=1;
	for(int i=1;i<=a[0];i++){
		for(int j=1;j<=b[0];j++){
			if(a[i]==b[j] && b[j]!=-1 && a[i]!=-1){
				gcd*=a[i];
				a[i]=-1;
				b[j]=-1;
				break;
			}
		}
	}
	printf("%d \n",gcd);
}

int main(){
	int m,n;
	printf("Enter 2 nos \n");
	scanf("%d%d",&m,&n);
	int* a=primfacts(m);
	int* b=primfacts(n);
	for(int i=0;i<=a[0];i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	for(int i=0;i<=b[0];i++){
		printf("%d ",b[i]);
	}
	printf("\n");
	gcd(a,b);
}
