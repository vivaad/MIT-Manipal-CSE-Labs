#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define MAX 10

int opcount=0;
void copy(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}
void output(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d to %d\n", i + 1, a[i] + 1);
    }
}
int totVa(int a[], int m[MAX][MAX], int n) {
    int tot = 0;
    for (int i = 0; i < n; i++) {
        tot += m[i][a[i]];
    }
    return tot;
}
void perm(int a[], int str, int n, int m[MAX][MAX], int *min, int cur[]) {
    if (str == n - 1) {
        int tot = totVa(a, m, n);

        if (tot < *min) {
            *min = tot;
            copy(cur, a, n);
        }
        return;
    }
    for (int i = str; i < n; i++) {
    	opcount++;
        int temp = a[str];
        a[str] = a[i];
        a[i] = temp;
        perm(a, str + 1, n, m, min, cur);
        temp = a[str];
        a[str] = a[i];
        a[i] = temp;
    }
}
void brute(int m[MAX][MAX], int n) {
    int a[MAX];
    int cur[MAX];
    int min = INT_MAX; 
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    perm(a, 0, n, m, &min, cur);
    output(cur, n);
    printf("Minimum Total Value: %d\n", min);
}
int main() {
	srand(time(NULL));
    int n;
    printf("Enter the number of people/jobs (n): ");
    scanf("%d", &n);
    int m[MAX][MAX];
    /* printf("Enter the matrix V[%d][%d] with values for each person-job pair:\n", n, n); */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            /* scanf("%d", &m[i][j]); */
			m[i][j]=rand()%100;
        }
    }
    brute(m, n);
    printf("opcount :%d ",opcount);
    return 0;
}
