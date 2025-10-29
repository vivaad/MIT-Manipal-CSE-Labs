#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	struct Node* lchild;
	struct Node* rchild;
	int data;
}Node;

// void insertNode(Node* root,int item){
	// while(root)
	// {
	// 	int num = (rand() % (10)) ;	
	// 	printf("%d",num);
	// 	if(num%2==0) 
	// 		insertNode(root->rchild,item);
	// 	else
	// 		insertNode(root->lchild,item);

	// }
	// root=(Node*)malloc(sizeof(Node));
	// root->lchild=(Node*)malloc(sizeof(Node));
	// root->rchild=(Node*)malloc(sizeof(Node));
	// root->data=item;
	// 	return;
	// if(!root)
	// {
	// 	root=(Node*)malloc(sizeof(Node));
	// 	// root->lchild=(Node*)malloc(sizeof(Node));
	// 	// root->rchild=(Node*)malloc(sizeof(Node));
	// 	root->data=item;
	// 	return;
	// }
	// else{

	// 	int num = (rand() % (10)) ;
	// 	printf("%d",num);
	// 	if(num%2==0) 
	// 		insertNode(root->rchild,item);
	// 	else
	// 		insertNode(root->lchild,item);
	// }
// }

int countNodes(Node* root){
	if(root)
	{
		return countNodes(root->lchild) + 1 + countNodes(root->rchild);
	}
	return 0;
}

int main(){

	// struct Node* root;
	// root=NULL;
	// root=insertNode(root,5);
	// root=insertNode(root,3);
	// root=insertNode(root,6);
	// root=insertNode(root,1);
	// root=insertNode(root,8);
	// root=insertNode(root,9);
	// root=insertNode(root,4);


	Node* root=(Node*)malloc(sizeof(Node));
	root->lchild=(Node*)malloc(sizeof(Node));
	root->rchild=(Node*)malloc(sizeof(Node));
	// insertNode(root,0);
	// insertNode(root,1);
	// insertNode(root,2);
	// insertNode(root,3);
	// insertNode(root,4);
	// insertNode(root,5);
	// insertNode(root,6);
	root->lchild=(Node*)malloc(sizeof(Node));
	root->rchild=(Node*)malloc(sizeof(Node));
	root->lchild->rchild=(Node*)malloc(sizeof(Node));
	root->rchild->lchild=(Node*)malloc(sizeof(Node));
	root->lchild->lchild=(Node*)malloc(sizeof(Node));
	root->rchild->rchild=(Node*)malloc(sizeof(Node));
	root->data=0;
	root->lchild->data=1;
	root->rchild->data=2;
	root->lchild->rchild->data=3;
	root->rchild->lchild->data=4;
	root->rchild->rchild->data=5;
	root->lchild->lchild->data=6;
	printf("No. of Nodes: %d \n",countNodes(root));
}