#include <stdio.h>
#include <stdlib.h>

int vis[10];

struct Graph{
	int V;
	int Adj[10][10];
};
int top[10];
int cnt=0;

void add_edge(struct Graph* g, int v, int c){
	g->Adj[v][c]=1;
}

void DFS(struct Graph* G, int u)
{
    vis[u] = 1;
    // printf("%d ", u);
    for (int v = 0; v < G->V; v++) {
        if (!vis[v] && G->Adj[u][v]) {
            DFS(G, v);
        }
    }
    top[cnt++]=u;
}

void DFStraversal(struct Graph* G)
{
    for (int i = 0; i < G->V; i++) {
        if (!vis[i]) {
            DFS(G, i);
        }
        
    }
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
	for (int i = 0; i < 100; i++) {
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

    DFStraversal(g);
    for(int i=g->V - 1;i>=0;i--)
    {
    	printf("%d ",top[i]);
    }
}




