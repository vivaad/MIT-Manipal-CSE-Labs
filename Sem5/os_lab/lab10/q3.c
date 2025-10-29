#include <stdio.h>

#define N 5  // number of segments

struct Segment {
    int base;
    int limit;
};

int main() {
    struct Segment segTable[N] = {
        {219, 600},
        {2300, 14},
        {90, 100},
        {1327, 580},
        {1952, 96}
    };

    int segNum, offset, physicalAddr;

    printf("Segment Table:\n");
    printf("Segment\tBase\tLimit\n");
    for (int i = 0; i < N; i++)
        printf("%d\t%d\t%d\n", i, segTable[i].base, segTable[i].limit);

    // Function to convert logical → physical
    while (1) {
        printf("\nEnter Segment Number (-1 to exit): ");
        scanf("%d", &segNum);
        if (segNum == -1) break;

        printf("Enter Offset: ");
        scanf("%d", &offset);

        if (segNum < 0 || segNum >= N) {
            printf("Invalid Segment Number!\n");
            continue;
        }

        if (offset >= segTable[segNum].limit) {
            printf("Error: Offset %d exceeds segment limit (%d).\n",
                   offset, segTable[segNum].limit);
        } else {
            physicalAddr = segTable[segNum].base + offset;
            printf("Physical Address = %d + %d = %d\n",
                   segTable[segNum].base, offset, physicalAddr);
        }
    }

    return 0;
}

