#include<stdio.h>

int main() 
{ 
    int processIndex, timeIndex, totalProcesses, currentTime, remainingProcesses, isProcessCompleted = 0, timeQuantum; 
    int totalWaitingTime = 0, totalTurnaroundTime = 0, arrivalTime[100], burstTime[100], remainingTime[100]; 

    // Input the total number of processes
    printf("Enter the number of processes: "); 
    scanf("%d", &totalProcesses); 
    remainingProcesses = totalProcesses; 

    // Input the arrival time and burst time for each process
    for (processIndex = 0; processIndex < totalProcesses; processIndex++) 
    { 
        printf("Enter arrival time for Process P%d: ", processIndex + 1);  
        scanf("%d", &arrivalTime[processIndex]); 
        printf("Enter burst time for Process P%d: ", processIndex + 1);  
        scanf("%d", &burstTime[processIndex]); 
        remainingTime[processIndex] = burstTime[processIndex]; 
    } 

    //arrivalTime = [0, 20, 25]
    //burstTime = [5, 4, 5]
    //remainingTime = [5, 4, 5]

    // Input the time quantum
    printf("Enter the time quantum: "); 
    scanf("%d", &timeQuantum); 

    // Display table headers
    printf("\n\nProcess\t| Turnaround time | Waiting time\n\n");  

    // Round-robin scheduling loop
    for (currentTime = 0, processIndex = 0; remainingProcesses != 0;) 
    { 
        // If process can finish within time quantum
        if (remainingTime[processIndex] <= timeQuantum && remainingTime[processIndex] > 0) 
        { 
            currentTime += remainingTime[processIndex]; 
            remainingTime[processIndex] = 0; 
            isProcessCompleted = 1; 
        } 
        // If process cannot finish within time quantum
        else if (remainingTime[processIndex] > 0) 
        { 
            remainingTime[processIndex] -= timeQuantum; 
            currentTime += timeQuantum; 
        } 

        // Process has completed its execution
        if (remainingTime[processIndex] == 0 && isProcessCompleted == 1) 
        { 
            remainingProcesses--; 
            printf("P[%d]\t|\t%d\t|\t%d\n", processIndex + 1, currentTime - arrivalTime[processIndex], currentTime - arrivalTime[processIndex] - burstTime[processIndex]); 
            totalWaitingTime += currentTime - arrivalTime[processIndex] - burstTime[processIndex]; 
            totalTurnaroundTime += currentTime - arrivalTime[processIndex]; 
            isProcessCompleted = 0; 
        }  

        // Move to the next process or restart from the first process
        if (processIndex == totalProcesses - 1) 
            processIndex = 0; 
        else if (arrivalTime[processIndex + 1] <= currentTime) 
            processIndex++; 
        else 
            processIndex = 0; 
    } 

    // Output the average waiting time and average turnaround time
    printf("\nAverage Waiting Time = %.2f\n", totalWaitingTime * 1.0 / totalProcesses);  
    printf("Average Turnaround Time = %.2f\n", totalTurnaroundTime * 1.0 / totalProcesses);  

    return 0; 
}
