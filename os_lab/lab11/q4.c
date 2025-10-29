#include <stdio.h>

#define TOTAL_BLOCKS 20
#define SPARE_BLOCKS 3

struct BadBlockEntry {
    int bad_block;
    int spare_block;
};

int main() {
    int disk[TOTAL_BLOCKS] = {0};
    int spare_start = TOTAL_BLOCKS - SPARE_BLOCKS; // last few blocks are spare
    struct BadBlockEntry bad_table[SPARE_BLOCKS];
    int bad_count = 0;

    // Suppose blocks 5 and 12 are bad
    int bad_blocks[] = {5, 12};
    int n_bad = 2;

    // Map bad blocks to spare blocks
    for (int i = 0; i < n_bad; i++) {
        bad_table[bad_count].bad_block = bad_blocks[i];
        bad_table[bad_count].spare_block = spare_start + i;
        bad_count++;
    }

    // Print bad block table
    printf("Bad Block Table:\n");
    for (int i = 0; i < bad_count; i++)
        printf("Bad Block %d -> Spare Block %d\n", 
               bad_table[i].bad_block, bad_table[i].spare_block);

    // Simulate accessing a few blocks
    int access[] = {3, 5, 7, 12, 15};
    int n_access = 5;

    printf("\nAccess Simulation:\n");
    for (int i = 0; i < n_access; i++) {
        int blk = access[i];
        int mapped = blk;
        for (int j = 0; j < bad_count; j++) {
            if (blk == bad_table[j].bad_block) {
                mapped = bad_table[j].spare_block;
                break;
            }
        }
        printf("Access Block %d -> Actual Block %d\n", blk, mapped);
    }

    return 0;
}

