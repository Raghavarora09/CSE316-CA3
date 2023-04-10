#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

void roundRobin(int burst_time[], int no_of_processes, int quantum);
void drawGanttChart(int burst_time[], int no_of_processes, int quantum);

int main(void)
{
    int no_of_processes, bt[MAX], quantum;
    int waiting_time[MAX];
    srand(time(0)); //random number generator with computer clock

    no_of_processes = (rand() % MAX) + 1;

    printf("Number of processes: %d\n\n", no_of_processes);

    for (int i = 0; i < no_of_processes; ++i)
    {
        bt[i] = (rand() % 10) + 1;     
        waiting_time[i] = rand() % 20; 
        printf("Process %d\tBurst Time: %d\tWaiting Time: %d\n", i + 1, bt[i], waiting_time[i]);
    }

    quantum = (rand() % 5) + 1;

    printf("\nTime Quantum: %d\n\n", quantum);

    roundRobin(bt, no_of_processes, quantum);  //function call

    printf("\n\n");

    return 0;
}

void drawGanttChart(int burst_time[], int no_of_processes, int quantum)
{

    int remaining_time[MAX]; //remaining burst time 
    int total = 0;  
    int remain = no_of_processes;  //processed remaining to be executed
    int flag = 0; //indicate process completion
    int i;

    printf("\nGantt Chart:\n\n");

    for (int i = 0; i < no_of_processes; ++i)
    {
        total += burst_time[i]; 
    }

    for (int i = 0; i < no_of_processes; ++i)
    {
        remaining_time[i] = burst_time[i]; //remaining time change 
    }
    // to print each process in gantt chart
    for (int process = 0; remain != 0; )
    {
        if (remaining_time[process] <= quantum && remaining_time[process])
        {
            printf("|P%d \t", process + 1);
            remaining_time[process] = 0;

            flag = 1;
        }

        else if (remaining_time[process] > 0)
        {
            printf("|P%d \t", process + 1);
            remaining_time[process] -= quantum;
        }

        if (flag == 1)
        {
            --remain;  //update remaining processes
            flag = 0; 
        }

        if (process == no_of_processes - 1)
        {
            process = 0;
        }

        else
        {
            ++process;
        }
    }

    printf("|");
    flag = 0;
    printf("\n");
    //time in gantt chart
    for (i = 0; i <= total ; i += quantum)
    {
        printf("%d\t", i);
        flag = 1;
    }

    if ((i % total) != 0)
    {
        printf("%d", total);
    }
    printf("\n\n");
}

//algo implement
void roundRobin(int burst_time[], int no_of_processes, int quantum)
{
    int remaining_time[MAX];     
    int waiting_time[MAX] = {0}; 
    int turnaround_time = 0;
    
    //copy burst time to reamining time
    for (int i = 0; i < no_of_processes; ++i)
    {
        remaining_time[i] = burst_time[i];
    }

    int current_time = 0;
    int completed = 0;

    //process execution loop
    while (completed != no_of_processes)
    {
        for (int i = 0; i < no_of_processes; ++i)
        {
            if (remaining_time[i] > 0)
            {
                if (remaining_time[i] <= quantum)
                {
                    //rem time < quantam update wait and turnaround
                    current_time += remaining_time[i];
                    turnaround_time += current_time;
                    remaining_time[i] = 0;
                    completed++; 

                    printf("Process %d completed in %d seconds.\n", i + 1, current_time);

                }
                else
                {
                    current_time += quantum; //current time update 
                    remaining_time[i] -= quantum;

                    printf("Process %d executed for %d seconds.\n", i + 1, quantum);

                    waiting_time[i] += current_time - burst_time[i] - waiting_time[i];  //wait time update
                }
            }
        }
    }

    drawGanttChart(burst_time, no_of_processes, quantum);

    float avg_waiting_time = 0;
    for (int i = 0; i < no_of_processes; i++) {
        avg_waiting_time += waiting_time[i];
    }
    avg_waiting_time /= no_of_processes;

    printf("Average Waiting Time: %f\n", avg_waiting_time);
    printf("Average Turnaround Time: %f\n", (float)turnaround_time / (float)no_of_processes);
}

