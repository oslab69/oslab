#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
};

void srtf(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    bool is_running = false;
    int current_process_index = -1;
    int turnaround_times[n];
    int gantt_chart[100];
    int gc_index = 0;
    
    while (completed_processes < n) {
        int shortest_remaining_time = -1;
        
        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (shortest_remaining_time == -1 || processes[i].remaining_time < shortest_remaining_time) {
                    shortest_remaining_time = processes[i].remaining_time;
                    current_process_index = i;
                }
            }
        }
        
        if (current_process_index != -1) {
            if (!is_running) {
                gantt_chart[gc_index++] = processes[current_process_index].pid;
                is_running = true;
            }
            
            processes[current_process_index].remaining_time--;
            if (processes[current_process_index].remaining_time == 0) {
                gantt_chart[gc_index++] = -1; // indicates process completion
                completed_processes++;
                is_running = false;
                turnaround_times[current_process_index] = current_time + 1 - processes[current_process_index].arrival_time;
            }
        } else {
            gantt_chart[gc_index++] = 0; // indicates idle time
        }
        
        current_time++;
    }
    
    printf("Gantt Chart:\n");
    for (int i = 0; i < gc_index; i++) {
        if (gantt_chart[i] == -1) {
            printf("P%d ", current_process_index + 1);
        } else if (gantt_chart[i] == 0) {
            printf("Idle ");
        } else {
            printf("P%d ", gantt_chart[i]);
        }
    }
    
    printf("\n\nProcess\tArrival Time\tCompletion Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, current_time, turnaround_times[i]);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    srtf(processes, n);
    
    return 0;
}

