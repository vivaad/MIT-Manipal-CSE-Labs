#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int op=0;

typedef struct node* np;
typedef struct node {
    int data;
    np next;
} node;

typedef struct gph {
    int nver;
    np* adlist;
    int mat[MAX][MAX];
} gph;

void ini(gph* g, int nver) {
    g->nver = nver;
    g->adlist = (np*)malloc(nver * sizeof(np));
    for (int i = 0; i < nver; i++) {
        g->adlist[i] = NULL;
        for (int j = 0; j < nver; j++) {
            g->mat[i][j] = 0;
        }
    }
}

void add(gph* g, int u, int v) {
    np new = (np)malloc(sizeof(node));
    new->data = v;
    new->next = g->adlist[u];
    g->adlist[u] = new;
    g->mat[u][v] = 1;
}

void closure(gph* g) {

    for (int k = 0; k < g->nver; k++) {
        for (int i = 0; i < g->nver; i++) {
            for (int j = 0; j < g->nver; j++) {
            	op++;
                g->mat[i][j] = g->mat[i][j] || (g->mat[i][k] && g->mat[k][j]);
            }
        }
    }

    printf("Transitive Closure :\n");
    for (int i = 0; i < g->nver; i++) {
        for (int j = 0; j < g->nver; j++) {
            printf("%d ", g->mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int nver, e, i, u, v;

    printf("Enter the number of nver: ");
    scanf("%d", &nver);

    gph g;
    ini(&g, nver);

    printf("Enter the number of e: ");
    scanf("%d", &e);

    printf("Enter the e (u v):\n");
    for (i = 0; i < e; ++i) {
        scanf("%d %d", &u, &v);
        add(&g, u, v);
    }
    closure(&g);
    printf("Opcount = %d",op);
    return 0;
}
