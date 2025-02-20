#include <stdio.h>
#include <stdlib.h>

void firstFit(int size[], int m, int process[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (size[j] >= process[i]) {
                allocation[i] = j;
                size[j] -= process[i];
                break;
            }
        }
    }

    printf("First Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void bestFit(int size[], int m, int process[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (size[j] >= process[i]) {
                if (bestIdx == -1 || size[bestIdx] > size[j]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            size[bestIdx] -= process[i];
        }
    }

    printf("Best Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void worstFit(int size[], int m, int process[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (size[j] >= process[i]) {
                if (worstIdx == -1 || size[worstIdx] < size[j]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            size[worstIdx] -= process[i];
        }
    }

    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

int main() {
    int m = 5; // Number of memory blocks
    int size[] = {100, 500, 200, 300, 600}; // Memory block sizes
    int n = 4; // Number of processes
    int process[] = {212, 417, 112, 426}; // Process sizes

    firstFit(size, m, process, n);
    bestFit(size, m, process, n);
    worstFit(size, m, process, n);

    return 0;
}
