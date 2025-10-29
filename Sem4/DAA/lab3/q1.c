#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int n=rand()%100;
	printf("N= %d", n);
	int a[n]; 
	
	printf("\n Unsorted Elements are:\n");
	for(int i=0; i<n; i++){
		a[i]= rand()%300;
		printf("%d ", a[i]);
	}
	printf("\n");	

	for(int i=0; i<n-1; i++){
		for(int j=0; j<n-i-1; j++){
			if(a[j]>a[j+1]){
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}

	printf("\n Sorted Elements are:\n");
	for(int i=0; i<n; i++)
		printf("%d ", a[i]);
	
	printf("\n");	
	return 0;
}
