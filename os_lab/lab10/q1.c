#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mab {
    int offset;
    int size;
    int allocated;
    struct mab *next;
    struct mab *prev;
};
typedef struct mab Mab;
typedef Mab* MabPtr;

// Global pointer for Next Fit
MabPtr last_alloc = NULL;

// Function prototypes
MabPtr createBlock(int offset, int size, int allocated);
MabPtr memChk(MabPtr head, int size, char *policy);
MabPtr memSplit(MabPtr m, int size);
MabPtr memMerge(MabPtr m);
MabPtr memAlloc(MabPtr head, int size, char *policy);
MabPtr memFree(MabPtr m);
void printMem(MabPtr head);

// Create new block
MabPtr createBlock(int offset, int size, int allocated) {
    MabPtr b = (MabPtr) malloc(sizeof(Mab));
    b->offset = offset;
    b->size = size;
    b->allocated = allocated;
    b->next = b->prev = NULL;
    return b;
}

// Split block into allocated and remainder
MabPtr memSplit(MabPtr m, int size) {
    if (m->size <= size) return m;

    MabPtr newBlock = createBlock(m->offset + size, m->size - size, 0);
    newBlock->next = m->next;
    if (newBlock->next) newBlock->next->prev = newBlock;
    newBlock->prev = m;
    m->next = newBlock;
    m->size = size;

    return m;
}

// Merge adjacent free blocks
MabPtr memMerge(MabPtr m) {
    while (m->next && !m->allocated && !m->next->allocated) {
        m->size += m->next->size;
        MabPtr tmp = m->next;
        m->next = tmp->next;
        if (m->next) m->next->prev = m;
        free(tmp);
    }
    return m;
}

// Find a free block depending on allocation policy
MabPtr memChk(MabPtr head, int size, char *policy) {
    MabPtr temp = head, chosen = NULL;

    if (strcmp(policy, "First") == 0) {
        while (temp) {
            if (!temp->allocated && temp->size >= size)
                return temp;
            temp = temp->next;
        }
    }
    else if (strcmp(policy, "Best") == 0) {
        int bestSize = 1e9;
        while (temp) {
            if (!temp->allocated && temp->size >= size && temp->size < bestSize) {
                bestSize = temp->size;
                chosen = temp;
            }
            temp = temp->next;
        }
        return chosen;
    }
    else if (strcmp(policy, "Worst") == 0) {
        int worstSize = -1;
        while (temp) {
            if (!temp->allocated && temp->size >= size && temp->size > worstSize) {
                worstSize = temp->size;
                chosen = temp;
            }
            temp = temp->next;
        }
        return chosen;
    }
    else if (strcmp(policy, "Next") == 0) {
        MabPtr start = last_alloc ? last_alloc : head;
        temp = start;
        do {
            if (!temp->allocated && temp->size >= size) {
                last_alloc = temp;
                return temp;
            }
            temp = temp->next ? temp->next : head;
        } while (temp != start);
    }

    return NULL;
}

// Allocate a block
MabPtr memAlloc(MabPtr head, int size, char *policy) {
    MabPtr block = memChk(head, size, policy);
    if (!block) {
        printf("No suitable block found for size %d under %s Fit.\n", size, policy);
        return NULL;
    }

    memSplit(block, size);
    block->allocated = 1;
    last_alloc = block;
    return block;
}

// Free and merge
MabPtr memFree(MabPtr m) {
    m->allocated = 0;
    if (m->prev && !m->prev->allocated)
        m = memMerge(m->prev);
    if (m->next && !m->next->allocated)
        m = memMerge(m);
    return m;
}

// Print memory map
void printMem(MabPtr head) {
    MabPtr temp = head;
    printf("\nMemory Layout:\n");
    while (temp) {
        printf("[Offset=%d Size=%d %s]\n",
               temp->offset, temp->size,
               temp->allocated ? "Allocated" : "Free");
        temp = temp->next;
    }
}

int main() {
    // initialize one free block of 1000 units
    MabPtr memList = createBlock(0, 1000, 0);

    int choice, size;
    char policy[10];
    MabPtr blocks[10] = {NULL};
    int blockCount = 0;

    while (1) {
        printf("\n--- Memory Allocation Simulation ---\n");
        printf("1. Allocate Block\n");
        printf("2. Free Block\n");
        printf("3. Print Memory\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter allocation policy (First/Best/Worst/Next): ");
            scanf("%s", policy);
            printf("Enter block size: ");
            scanf("%d", &size);
            MabPtr b = memAlloc(memList, size, policy);
            if (b) {
                printf("Allocated block at offset %d, size %d.\n", b->offset, b->size);
                blocks[blockCount++] = b;
            }
        }
        else if (choice == 2) {
            printf("Enter index of block to free (0-%d): ", blockCount - 1);
            int idx; scanf("%d", &idx);
            if (idx >= 0 && idx < blockCount && blocks[idx]) {
                memFree(blocks[idx]);
                printf("Block freed.\n");
                blocks[idx] = NULL;
            }
        }
        else if (choice == 3) {
            printMem(memList);
        }
        else if (choice == 4) break;
        else printf("Invalid choice.\n");
    }

    return 0;
}

