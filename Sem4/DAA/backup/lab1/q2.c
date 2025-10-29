#include <stdio.h>
#include <stdlib.h>

struct node{
	int vertex;
	struct node* link;
};
struct Graph{
	int v;
	int adj_matrix[10][10];
	struct node* adj_list[10];
};

void add_edge(struct Graph* g, int v, int c){
	//updating adjacency matrix
	g->adj_matrix[v][c]=1;
	// updating adjacency list
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp=g->adj_list[v];
	while(temp->link)
		temp=temp->link;

	struct node* connection=(struct node*)malloc(sizeof(struct node));
	connection->vertex=c;
	connection->link=NULL;
	temp->link=connection;
}

int main(){
	struct Graph* g=(struct Graph*)malloc(sizeof(struct Graph));
	g->v=5;
	for(int i=0;i<g->v;i++)
	{
		for(int j=0;j<g->v;j++)
		{
			g->adj_matrix[i][j]=0;
		}
	}
	for(int i=0;i<g->v;i++)
	{
		g->adj_list[i]=(struct node*)malloc(sizeof(struct node));
		g->adj_list[i]->vertex=i;
		g->adj_list[i]->link=NULL;
	}
	add_edge(g,0,1);
	add_edge(g,0,4);
	add_edge(g,1,3);
	add_edge(g,2,1);
	add_edge(g,4,3);
	add_edge(g,4,1);
	
	for(int i=0;i<g->v;i++)
	{
		for(int j=0;j<g->v;j++)
		{
			printf("%d ",g->adj_matrix[i][j]);
		}
		printf("\n");
	}

	for(int i=0;i<g->v;i++)
	{
		printf("%d :",i);
		for(struct node* j=g->adj_list[i];j->link;j=j->link)
		{
			printf("%d ",j->vertex);
		}
		printf("\n");
	}
}