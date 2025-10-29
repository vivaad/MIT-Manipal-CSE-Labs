#include<stdio.h>
#include<stdlib.h>

int opcount=0;
int swapped=0;
void bubSort(int* a, int n){
	for(int i=0;i<n-1;i++){
		swapped=0;
		for(int j=0;j<n-1-i;j++){
			opcount++;
			if(a[j]>a[j+1]){
				swapped=1;
				opcount++;
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
		if(swapped==0)
			break;
	}
}
int main() {
	int *a;
	int i,n = 5;
	for (int j=0; j < 6; j++) // repeat experiment for 4 trials
	{
		opcount=0;
		a = (int *)malloc(sizeof(int)*n);
		for (int k=0; k< n; k++)
			a[k] = k+1; 
		
		printf("Elements are ");
		
		for(i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");

		bubSort(a,n);
		printf("Elements after bubble sort ");
		for(i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
		printf("OPCOUNT :%d \n",opcount);
		printf("N:%d\n",n);
		free(a);
		n = n + 5; 
	}
	return 0;
}