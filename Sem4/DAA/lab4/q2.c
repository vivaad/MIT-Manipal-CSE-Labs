#include <stdio.h>
#include <stdlib.h>

int vis[100];
int push=0;
int pop=0;
struct Graph{
	int V;
	int Adj[10][10];
};

void add_edge(struct Graph* g, int v, int c){
	g->Adj[v][c]=1;
}

void DFS(struct Graph* G, int u)
{
	push++;
	printf("Pushed %d \n",u);
    vis[u] = 1;
    // printf("%d ", u);
    for (int v = 0; v < G->V; v++) {
        if (!vis[v] && G->Adj[u][v]) {
            DFS(G, v);
        }
    }
    printf("popped %d \n",u);

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
    add_edge(g,0,1);
	add_edge(g,0,4);
	add_edge(g,1,3);
	add_edge(g,2,1);
	add_edge(g,4,3);
	add_edge(g,4,1);
    DFStraversal(g);
}




