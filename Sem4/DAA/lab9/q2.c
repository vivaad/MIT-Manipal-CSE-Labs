#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int m;
int n;

typedef struct Node{
	struct Node* link;
	int data;
}Node;

Node* table[10];

Node* createNode(int key){
	Node* new =(Node*)malloc(sizeof(Node));
	new->data=key;
	new->link=NULL;
	return new;
}

void hash(int hindex, int key)
{

	Node* new_node=createNode(key);
	Node* current=table[hindex];
	if(!current)
	{
		table[hindex]=new_node;
		return;
	}
	while(current->link!=NULL)
	{
		current=current->link;
	}
	current->link=new_node;
	return;
}

int hx(int key)
{
	return key%m;
}
void printHash()
{
	for(int i=0;i<m;i++)
	{
		printf("Hash value: %d Keys : ",i);
		Node* temp=table[i];
		while(temp!=NULL) 
		{
			printf("%d ",temp->data);
			temp=temp->link;
		}
		printf("\n");		
	}
}

void work(int m_, int n_){
	m=m_;
	n=n_;
	int a[n];
	printf("n= %d, m= %d\n", n, m);
	for(int i=0; i<n; i++){
		a[i]=rand()%100;
	}
	for(int i=0;i<m;i++)
	{
		table[i]=NULL;
	}
	for(int i=0;i<n;i++)
	{
		int value=hx(a[i]);
		hash(value,a[i]);
	}
	printHash();
	printf("\n");
}

int main()
{	
	srand(time(NULL));
	/* int a[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14}; */
	int na[] ={50, 100, 200};
	int ma[] ={10, 20, 50};
	
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			work(ma[j], na[i]);
		}
	}


	return 1;
}
