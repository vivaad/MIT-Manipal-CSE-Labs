#include <stdio.h>

#define MAX_REF 50
#define MAX_FRAMES 10

typedef struct {
    int page;
    int ref_bit;
} Frame;

int main() {
    int refStr[MAX_REF], n, framesCount, pageFaults = 0, hits = 0;
    Frame frames[MAX_FRAMES];
    int pointer = 0; // clock hand

    // Input
    printf("Enter length of reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &refStr[i]);

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    // Initialize frames
    for (int i = 0; i < framesCount; i++) {
        frames[i].page = -1;
        frames[i].ref_bit = 0;
    }

    // Simulation
    for (int i = 0; i < n; i++) {
        int page = refStr[i];
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < framesCount; j++) {
            if (frames[j].page == page) {
                frames[j].ref_bit = 1; // give second chance
                found = 1;
                hits++;
                break;
            }
        }

        // Page fault (not found)
        if (!found) {
            while (1) {
                if (frames[pointer].page == -1) {
                    // empty frame — place it
                    frames[pointer].page = page;
                    frames[pointer].ref_bit = 1;
                    pointer = (pointer + 1) % framesCount;
                    break;
                }
                else if (frames[pointer].ref_bit == 0) {
                    // replace this page
                    frames[pointer].page = page;
                    frames[pointer].ref_bit = 1;
                    pointer = (pointer + 1) % framesCount;
                    break;
                } else {
                    // give second chance
                    frames[pointer].ref_bit = 0;
                    pointer = (pointer + 1) % framesCount;
                }
            }
            pageFaults++;
        }

        // Display current frame status
        printf("\nAfter referencing page %d: ", page);
        for (int j = 0; j < framesCount; j++) {
            if (frames[j].page != -1)
                printf("%d(%d) ", frames[j].page, frames[j].ref_bit);
            else
                printf("- ");
        }
    }

    float hitRatio = (float)hits / n;
    printf("\n\nTotal Page Faults: %d", pageFaults);
    printf("\nTotal Hits: %d", hits);
    printf("\nHit Ratio: %.2f\n", hitRatio);

    return 0;
}

