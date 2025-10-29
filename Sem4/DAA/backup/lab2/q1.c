#include <stdio.h>
int opcount=0;
int gcd(int m,int n){
	int t;
	if(m<=n)
		t=m;
	else
		t=n;
	int r;
	while(t>0)
	{
		opcount++;
		if(m%t==0 && n%t==0)
			return t;
		else
			t=t-1;
	}
}

int main(){
	int m,n;
	printf("Enter 2 nos");
	scanf("%d%d",&m,&n);
	printf("GCD : %d \n",gcd(m,n));
	printf("opcount = %d \n",opcount);
	printf("M+N= %d \n",m+n);
	return 0;
}