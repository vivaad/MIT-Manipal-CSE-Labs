#include <stdio.h>
#include <stdlib.h>

#define N 5  // number of requests

struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};

// FCFS Algorithm
void FCFS(struct DSA reqs[], int n, int head) {
    int total = 0;
    printf("\nFCFS Order:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d -> Cylinder %d\n", reqs[i].request_id, reqs[i].cylinder);
        total += abs(head - reqs[i].cylinder);
        head = reqs[i].cylinder;
    }
    printf("Total head movement: %d\n", total);
}

// SSTF Algorithm
void SSTF(struct DSA reqs[], int n, int head) {
    int done[N] = {0}, total = 0, count = 0;
    printf("\nSSTF Order:\n");
    while (count < n) {
        int min = 1e9, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                int dist = abs(reqs[i].cylinder - head);
                if (dist < min) {
                    min = dist;
                    idx = i;
                }
            }
        }
        done[idx] = 1;
        printf("Request %d -> Cylinder %d\n", reqs[idx].request_id, reqs[idx].cylinder);
        total += abs(head - reqs[idx].cylinder);
        head = reqs[idx].cylinder;
        count++;
    }
    printf("Total head movement: %d\n", total);
}

int main() {
    struct DSA reqs[N] = {
        {1, 0, 55, 0, 101},
        {2, 1, 58, 0, 102},
        {3, 2, 39, 0, 103},
        {4, 3, 18, 0, 104},
        {5, 4, 90, 0, 105}
    };
    int head = 50;

    FCFS(reqs, N, head);
    SSTF(reqs, N, head);

    return 0;
}

