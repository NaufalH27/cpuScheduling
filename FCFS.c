#include <stdio.h>
#include <string.h>

int main() {
    int n, AT[100], b[100], i, j, tmp, WT[100], TAT[100], time[101];
    int TotWT = 0, TotTA = 0;
    float AvWT, AvTA;
    char name[100][20], tmpName[20];

    printf("\t Algoritma CPU Scheduling FCFS \n");
    printf("Jumlah Proses\t= ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        fprintf(stderr, "Invalid input for number of processes. Ensure 0 < n <= 100.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Nama Proses\t= ");
        scanf("%s", name[i]);
        printf("Arrival time\t= ");
        if (scanf("%d", &AT[i]) != 1) {
            fprintf(stderr, "Invalid input for Arrival Time\n");
            return 1;
        }
        printf("Burst time\t= ");
        if (scanf("%d", &b[i]) != 1) {
            fprintf(stderr, "Invalid input for Burst Time\n");
            return 1;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (AT[i] > AT[j]) {
                strcpy(tmpName, name[i]);
                strcpy(name[i], name[j]);
                strcpy(name[j], tmpName);

                tmp = AT[i];
                AT[i] = AT[j];
                AT[j] = tmp;

                tmp = b[i];
                b[i] = b[j];
                b[j] = tmp;
            }
        }
    }

    time[0] = AT[0];
    for (i = 0; i < n; i++) {
        time[i + 1] = time[i] + b[i];
        WT[i] = time[i] - AT[i];
        if (WT[i] < 0) WT[i] = 0; // Handle negative waiting time
        TAT[i] = time[i + 1] - AT[i];
        TotWT += WT[i];
        TotTA += TAT[i];
    }

    printf("\n\tAverage Waiting Time : %.2f\n", (float)TotWT / n);
    printf("\tAverage Turn Around Time : %.2f\n", (float)TotTA / n);

    return 0;
}
