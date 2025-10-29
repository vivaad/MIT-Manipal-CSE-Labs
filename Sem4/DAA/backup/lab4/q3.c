#include <stdio.h>
#include <stdlib.h>

struct Graph{
	int V;
	int Adj[10][10];
};

int visited[10];

void add_edge(struct Graph* g, int v, int c){
	g->Adj[v][c]=1;
}

void BFS(struct Graph* g, int s)
{

    int queue[10];
    int front = 0;
    int rear = 0;
 
    visited[s] = 1;
    queue[rear++] = s;
 
    while (front != rear) {

        s = queue[front++];
        printf("%d ", s);

        for (int adjacent = 0; adjacent < g->V;adjacent++)
        {
            if (g->Adj[s][adjacent] && visited[adjacent]==0)
            {
                visited[adjacent] = 1;
                queue[rear++] = adjacent;
            }
        }
    }
}
void BFS_traversal(struct Graph* g,int s)
{
	BFS(g,s);
	for(int i=0;i<g->V;i++)
	{
		if(visited[i]==0)
			BFS(g,i);
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
	for (int i = 0; i < g->V; i++) {
        visited[i] = 0;
    }
    add_edge(g,0,1);
	add_edge(g,0,4);
	add_edge(g,1,3);
	// add_edge(g,0,2);
	add_edge(g,2,1);
	add_edge(g,4,3);
	add_edge(g,4,1);
	BFS_traversal(g,0);

}
