#include <stdio.h>

int main() {
    int i, j, n, time, remain, flag = 0, tq;
    int TotWT = 0, TotTA = 0, AT[100], b[100], rt[100];
    
    printf("Masukkan jumlah proses : ");
    scanf("%d", &n);
    remain = n;

    // Input arrival and burst times for each process
    for (i = 0; i < n; i++) {
        printf("Masukkan arrival time untuk Proses P%d : ", i + 1);
        scanf("%d", &AT[i]);
        printf("Masukkan burst time untuk Proses P%d : ", i + 1);
        scanf("%d", &b[i]);
        rt[i] = b[i];
    }

    // Input time quantum
    printf("Masukkan time quantum: ");
    scanf("%d", &tq);

    printf("\n\nProcess\t|Turnaround time|waiting time\n\n");

    // Round Robin Scheduling
    for (time = 0, i = 0; remain != 0;) {
        if (rt[i] <= tq && rt[i] > 0) {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        } else if (rt[i] > 0) {
            rt[i] -= tq;
            time += tq;
        }

        // Process completed, calculate waiting time and turnaround time
        if (rt[i] == 0 && flag == 1) {
            remain--;
            printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, time - AT[i], time - AT[i] - b[i]);
            TotWT += time - AT[i] - b[i];
            TotTA += time - AT[i];
            flag = 0;
        }

        // Move to next process
        if (i == n - 1) {
            i = 0;
        } else if (AT[i + 1] <= time) {
            i++;
        } else {
            i = 0;
        }
    }

    // Calculate average waiting time and average turnaround time
    printf("\nAverage Waiting Time = %f\n", TotWT * 1.0 / n);
    printf("Average Turnaround Time = %f\n", TotTA * 1.0 / n);

    return 0;
}
