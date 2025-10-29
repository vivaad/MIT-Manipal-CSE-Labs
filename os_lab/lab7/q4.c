#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define K 1234
#define N 3

struct S {
    char b[N][N];
    int t,m,w;
} *s;

void p(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            printf(" %c ", s->b[i][j]?s->b[i][j]:' ');
        printf("\n");
    }
    printf("\n");
}

int ca(){
    for(int i=0;i<N;i++)
        if(s->b[i][0] && s->b[i][0]==s->b[i][1] && s->b[i][1]==s->b[i][2]) 
			return s->b[i][0]=='X'?1:2;
    for(int i=0;i<N;i++)
        if(s->b[0][i] && s->b[0][i]==s->b[1][i] && s->b[1][i]==s->b[2][i]) 
			return s->b[0][i]=='X'?1:2;
    if(s->b[0][0] && s->b[0][0]==s->b[1][1] && s->b[1][1]==s->b[2][2]) 
		return s->b[0][0]=='X'?1:2;
    if(s->b[0][2] && s->b[0][2]==s->b[1][1] && s->b[1][1]==s->b[2][0]) 
		return s->b[0][2]=='X'?1:2;
    return 0;
}

int main(){
    int shmid=shmget(K,sizeof(struct S),0666|IPC_CREAT);
    s=shmat(shmid,0,0);
    if(!s->t){
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)s->b[i][j]=0;
		s->t=1;
		s->m=0;
		s->w=0;
	}
    int pnum, r,c;
    printf("Player (1 or 2): "); scanf("%d",&pnum);
    char mk=pnum==1?'X':'O';
    while(1){
        if(s->w){
			p();
			printf(s->w==3?"Draw!\n":"Player %d wins!\n",s->w); 
			break;
		}
        if(s->t!=pnum){
			/* printf("Waiting for Player %d...\n", s->t); */
			sleep(1);
			continue;
		}
        p();
        printf("Player %d (%c) move (row col): ", pnum,mk);
        scanf("%d%d",&r,&c);
        if(r<1||r>3||c<1||c>3||s->b[r-1][c-1]){
			printf("Invalid\n");
			continue;
		}
        s->b[r-1][c-1]=mk; 
		s->m++;
        int w=ca();
        if(w) s->w=w; 
		else if(s->m==9) s->w=3; 
		else s->t=3-pnum;
    }
    shmdt(s);
    if(pnum==1) shmctl(shmid,IPC_RMID,0);
    return 0;
}

