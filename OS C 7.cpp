#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void findWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;

    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void findTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void findavgTime(struct Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

void sortProcesses(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].burst_time > proc[j + 1].burst_time) {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct Process proc[] = { {1,4}, {3, 2}, {5, 4}, {5, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);

    sortProcesses(proc, n);
    findavgTime(proc, n);

    return 0;
}
