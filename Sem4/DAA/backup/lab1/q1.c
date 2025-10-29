#include <stdio.h>
#include <stdlib.h>

struct Node{
	struct Node* lchild;
	struct Node* rchild;
	int data;
};

struct Node* insertNode(struct Node* root, int data){
	if(root==NULL)
	{
		struct Node* root=(struct Node*)malloc(sizeof(struct Node));
		root->data=data;
		root->lchild=NULL;
		root->rchild=NULL;
		return root;
	}
	else
	{
		if(data<root->data)
			root->lchild=insertNode(root->lchild,data);
		else
			root->rchild=insertNode(root->rchild,data);
		return root;
	}
}

void inorder(struct Node* root)
{
	if(root){
		inorder(root->lchild);
		printf("%d ",root->data);
		inorder(root->rchild);
	}
}
void preorder(struct Node* root)
{
	if(root){
		printf("%d ",root->data);
		preorder(root->lchild);
		preorder(root->rchild);
	}
}
void postorder(struct Node* root)
{
	if(root){
		postorder(root->lchild);
		postorder(root->rchild);
		printf("%d ",root->data);
	}
}


int main(){
	struct Node* root;
	root=NULL;
	root=insertNode(root,5);
	root=insertNode(root,3);
	root=insertNode(root,6);
	root=insertNode(root,1);
	root=insertNode(root,8);
	root=insertNode(root,9);
	root=insertNode(root,4);

	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
}