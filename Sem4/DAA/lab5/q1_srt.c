#include <stdio.h>
#include <stdlib.h>

int vis[10];
struct Graph{
	int V;
	int Adj[10][10];
};
int indeg[10];
int cnt=0;
int top[10];
void add_edge(struct Graph* g, int v, int c){
	g->Adj[v][c]=1;
}

void calc_indegree(struct Graph* g)
{
	for(int v=0;v<g->V;v++)
	{
		indeg[v]=0;
		for(int j=0;j<g->V;j++)
		{
			if(g->Adj[j][v]==1)
				indeg[v]++;
		}
	}
}
void update_indeg(struct Graph* g, int v)
{
	for(int i=0;i<g->V;i++)
	{
		if(g->Adj[v][i]==1)
		{
			g->Adj[v][i]=0;
			indeg[i]--;
		}
	}
}

int next_in_top(struct Graph* g)
{
	for(int i=0;i<g->V;i++)
	{
		if(indeg[i]==0)
		{
			indeg[i]=-1;
			return i;
		}
	}
	return -1;
}
void top_sort(struct Graph* g)
{
	for(int i=0;i<g->V;i++)
	{
		top[i]=next_in_top(g);
		update_indeg(g,top[i]);
	}
	for(int i=0;i<g->V;i++)
		printf("%d ",top[i]);
}


int main(){
	struct Graph* g=(struct Graph*)malloc(sizeof(struct Graph));
	g->V=5;
	for(int i=0;i<g->V;i++)
	{
		for(int j=0;j<g->V;j++)
		{
			g->Adj[i][j]=0;
		}
	}
	for (int i = 0; i < 10; i++) {
        vis[i] = 0;
    }
    // add_edge(g,0,1);
	// add_edge(g,0,4);
	// add_edge(g,1,3);
	// add_edge(g,2,1);
	// add_edge(g,4,3);
	// add_edge(g,4,1);

	add_edge(g,0,2);
	add_edge(g,0,3);
	add_edge(g,1,0);
	add_edge(g,1,3);
	add_edge(g,3,2);
	add_edge(g,3,4);
	add_edge(g,2,4);
    
    calc_indegree(g);
    top_sort(g);
}