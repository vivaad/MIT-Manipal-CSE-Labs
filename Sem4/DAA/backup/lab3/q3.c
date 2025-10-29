#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** getPowerSet(int *set, int set_size) 
{ 
    unsigned int pow_set_size = pow(2, set_size); 
    int counter, j; 
    int** pow_set=(int**)malloc(sizeof(int*)*pow_set_size);
    for(counter = 0; counter < pow_set_size; counter++) 
    { 
    	int count=0;
    	int* sub=(int*)malloc(sizeof(int)*set_size);
      for(j = 0; j < set_size; j++) 
       { 
          if(counter & (1<<j))
          	sub[count++]=set[j];
       }
       sub[count]=-1;
       pow_set[counter]=sub;  
    }

    return pow_set; 
} 
int find_sum(int* a,int n){
	int sum=0;
	for(int i=0;i<n;i++)
	{
		sum+=a[i];
	}
	return sum;
}

int isDisjoint(int* a,int* b)
{
	int i=0;int j=0;
	while(a[i]!=-1){
		while(b[j]!=-1){
			if(a[i]==b[j])
				return 0;
			j++;
		}
		i++;
		j=0;
	}
	return 1;
}

void partition(int* set, int n){
	int** pow_set=getPowerSet(set,n);
	int* sums=(int*)malloc(sizeof(int)*pow(2,n));
	for(int i=0;i<pow(2,n);i++){
		int count=0;
		int j=0;
		while(pow_set[i][j]!=-1)
		{
			count++;
			j++;
		}
		int x=find_sum(pow_set[i],count);
		sums[i]=x;
	}

	for(int i=0;i<pow(2,n);i++)
	{
		int *part1=pow_set[i];
		for(int j=0;j<pow(2,n);j++)
		{
			if(i==j)
				continue;
			int *part2=pow_set[j];
			if(sums[i]==sums[j] & isDisjoint(part1,part2)==1)
			{
				int j=0,k=0;
				printf("Part 1: ");
				while(part1[j]!=-1)
				{
					printf("%d ",part1[j]);
					j++;
				}
				printf("Part 2: ");
				while(part2[k]!=-1)
				{
					printf("%d ",part2[k]);
					k++;
				}
				printf("Sum: %d",sums[i]);
			}
		}
		printf("\n");
	}
}

int main()
{
	int set[]={1,2,3,4};
	partition(set,4);
}