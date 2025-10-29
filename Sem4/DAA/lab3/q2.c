#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int opcount=0;
int match(char* str, char* substr,int m,int n){
	for(int i=0;i<=m-n;i++)
	{
		opcount++;
		if(substr[0]==str[i])
		{
			for(int j=1;j<n;j++)
			{
				opcount++;
				if(substr[j]==str[i+j]){
					if(j==n-1)
						return 1;
					else
						continue;
				}
				else
					break;
			}
		}
	}
	return 0;
}

int main(){
	char* str=(char*)malloc(100*sizeof(char));
	char* substr=(char*)malloc(100*sizeof(char));
	printf("Enter main string\n");
	scanf("%s",str);
	printf("Enter sub string\n");
	scanf("%s",substr);
	int res=match(str,substr,strlen(str),strlen(substr));
	if(res==1)
		printf("Match \n");
	else
		printf("No match \n");

	printf("M:%d\n",(int) strlen(str));
	printf("N:%d\n",(int) strlen(substr));
	printf("M+N:%d\n",(int) (strlen(substr)+strlen(str)));
	printf("Opcount : %d\n",opcount);
}
