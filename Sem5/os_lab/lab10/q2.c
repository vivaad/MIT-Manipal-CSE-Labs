#include <stdio.h>
#include <stdlib.h>

#define TIME_QUANTUM 4  // for RR (Q1)

typedef struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int queue_level; // 1, 2, or 3
    struct Process *next;
} Process;

// Queue structure
typedef struct {
    Process *front;
    Process *rear;
} Queue;

// Function prototypes
void enqueue(Queue *q, Process *p);
Process* dequeue(Queue *q);
int isEmpty(Queue *q);
Process* createProcess(int pid, int burst, int arrival);
void simulateMLFQ(Process *plist, int n);
void sortByBurst(Process **head);  // used for SJF (Q2)

// Queue operations
void enqueue(Queue *q, Process *p) {
    p->next = NULL;
    if (!q->rear)
        q->front = q->rear = p;
    else {
        q->rear->next = p;
        q->rear = p;
    }
}
Process* dequeue(Queue *q) {
    if (!q->front) return NULL;
    Process *temp = q->front;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    return temp;
}
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// Create process dynamically using malloc
Process* createProcess(int pid, int burst, int arrival) {
    Process *p = (Process*)malloc(sizeof(Process));
    p->pid = pid;
    p->burst_time = burst;
    p->remaining_time = burst;
    p->arrival_time = arrival;
    p->queue_level = 1;
    p->next = NULL;
    return p;
}

// Sort queue for SJF
void sortByBurst(Process **head) {
    for (Process *i = *head; i && i->next; i = i->next)
        for (Process *j = i->next; j; j = j->next)
            if (i->burst_time > j->burst_time) {
                int t;
                t = i->pid; i->pid = j->pid; j->pid = t;
                t = i->burst_time; i->burst_time = j->burst_time; j->burst_time = t;
                t = i->remaining_time; i->remaining_time = j->remaining_time; j->remaining_time = t;
            }
}

// MLFQ simulation
void simulateMLFQ(Process *plist, int n) {
    Queue q1 = {NULL, NULL}, q2 = {NULL, NULL}, q3 = {NULL, NULL};
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) enqueue(&q1, &plist[i]);

    printf("\n--- Multilevel Feedback Queue Scheduling ---\n");
    while (completed < n) {
        Process *p = NULL;

        // Q1 → Round Robin
        if (!isEmpty(&q1)) {
            p = dequeue(&q1);
            printf("Time %d: P%d (Q1-RR)\n", time, p->pid);
            if (p->remaining_time > TIME_QUANTUM) {
                p->remaining_time -= TIME_QUANTUM;
                time += TIME_QUANTUM;
                p->queue_level = 2;
                enqueue(&q2, p); // demote
            } else {
                time += p->remaining_time;
                p->remaining_time = 0;
                printf("P%d finished at time %d\n", p->pid, time);
                completed++;
            }
        }

        // Q2 → SJF (non-preemptive)
        else if (!isEmpty(&q2)) {
            sortByBurst(&q2.front);
            p = dequeue(&q2);
            printf("Time %d: P%d (Q2-SJF)\n", time, p->pid);
            time += p->remaining_time;
            p->remaining_time = 0;
            printf("P%d finished at time %d\n", p->pid, time);
            completed++;
        }

        // Q3 → FCFS
        else if (!isEmpty(&q3)) {
            p = dequeue(&q3);
            printf("Time %d: P%d (Q3-FCFS)\n", time, p->pid);
            time += p->remaining_time;
            p->remaining_time = 0;
            printf("P%d finished at time %d\n", p->pid, time);
            completed++;
        }

        else break; // all queues empty
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process *plist = (Process*) malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        int bt, at;
        printf("Enter burst time and arrival time for P%d: ", i + 1);
        scanf("%d %d", &bt, &at);
        plist[i] = *createProcess(i + 1, bt, at);
    }

    simulateMLFQ(plist, n);

    free(plist);
    return 0;
}

