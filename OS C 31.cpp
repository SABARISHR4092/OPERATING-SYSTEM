#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3
#define PAGE_SIZE 10

void fifo_paging(int pages[], int n) {
    int frame[FRAME_SIZE], page_faults = 0, k = 0;
    int is_present;

    for (int i = 0; i < FRAME_SIZE; i++) {
        frame[i] = -1; // Initialize frames
    }

    for (int i = 0; i < n; i++) {
        is_present = 0;

        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frame[j] == pages[i]) {
                is_present = 1; // Page is already in frame
                break;
            }
        }

        if (!is_present) {
            frame[k] = pages[i]; // Replace the oldest page
            k = (k + 1) % FRAME_SIZE; // Move to the next frame
            page_faults++;
        }

        printf("Page: %d | Frames: ", pages[i]);
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[PAGE_SIZE] = {0, 1, 2, 0, 3, 0, 4, 2, 3, 0};
    int n = sizeof(pages) / sizeof(pages[0]);

    fifo_paging(pages, n);
    return 0;
}
