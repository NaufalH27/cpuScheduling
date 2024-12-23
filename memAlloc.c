#include <stdio.h>
#include <string.h>

#define NUM_BLOCKS 4
#define NUM_PROCESSES 4

void firstFit(int memory[], int process[], int allocated[]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_BLOCKS; j++) {
            if (memory[j] >= process[i]) {
                allocated[i] = j;
                memory[j] -= process[i];
                break;
            }
        }
    }
}

void bestFit(int memory[], int process[], int allocated[]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int bestIdx = -1;
        for (int j = 0; j < NUM_BLOCKS; j++) {
            if (memory[j] >= process[i]) {
                if (bestIdx == -1 || memory[j] < memory[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocated[i] = bestIdx;
            memory[bestIdx] -= process[i];
        }
    }
}

void worstFit(int memory[], int process[], int allocated[]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int worstIdx = -1;
        for (int j = 0; j < NUM_BLOCKS; j++) {
            if (memory[j] >= process[i]) {
                if (worstIdx == -1 || memory[j] > memory[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocated[i] = worstIdx;
            memory[worstIdx] -= process[i];
        }
    }
}

void displayMemory(int memory[]) {
    printf("Blok Memori Awal:\n");
    printf("======================================================\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        printf("|   %4dk            ", memory[i]);
    }
    printf("|\n");
    printf("======================================================\n");
}

void printResult(int memory[], int process[], int allocated[]) {
    printf("\nAlokasi Akhir:\n");
    printf("======================================================\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        int allocatedProcess = -1;
        for (int j = 0; j < NUM_PROCESSES; j++) {
            if (allocated[j] == i) {
                allocatedProcess = j;
                break;
            }
        }
        if (allocatedProcess != -1) {
            printf("|   %4dk   (P%d)   ", memory[i] + process[allocatedProcess], allocatedProcess + 1);
        } else {
            printf("|   %4dk            ", memory[i]);
        }
    }
    printf("|\n");
    printf("======================================================\n");
}

int main() {
    int memory[NUM_BLOCKS] = {400, 500, 600, 200};
    int process[NUM_PROCESSES];
    int method;

    displayMemory(memory);

    printf("\nMasukkan ukuran untuk 4 proses (dalam k):\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Proses %d: ", i + 1);
        scanf("%d", &process[i]);
    }

    printf("\nPilih Metode Alokasi:\n1. First Fit\n2. Best Fit\n3. Worst Fit\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &method);

    int allocated[NUM_PROCESSES];
    memset(allocated, -1, sizeof(allocated));

    switch (method) {
    case 1:
        firstFit(memory, process, allocated);
        break;
    case 2:
        bestFit(memory, process, allocated);
        break;
    case 3:
        worstFit(memory, process, allocated);
        break;
    default:
        printf("Pilihan tidak valid! Keluar.\n");
        return 1;
    }

    printResult(memory, process, allocated);

    return 0;
}
