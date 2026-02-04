#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
struct process {
 int bt, at, rt, ct, wt, tat, completed;
 char p_name[10];
};
void display(struct process *p, int n) {
 printf("\nProcess Name Arrival Time Burst Time Completion Time Turnaround Time Waiting Time\n");
 for (int i = 0; i < n; i++) {
 printf(" %s %d %d %d %d %d\n",
 p[i].p_name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
 }}
void calculations(struct process *p, int n) {
 float sum_wt = 0.0, sum_tat = 0.0, avg_wt = 0.0, avg_tat = 0.0;
 for (int i = 0; i < n; i++) {
 sum_wt += p[i].wt;
 sum_tat += p[i].tat; }
 avg_wt = sum_wt / n;
 avg_tat = sum_tat / n;
 printf("\nAverage Waiting Time = %f\n", avg_wt);
 printf("Average Turnaround Time = %f\n", avg_tat); }
void preemptive_sjf(struct process *p, int n) {
 int completed = 0, current_time = 0, min_bt, min_index;
 float total_wt = 0, total_tat = 0;
 // Initialize remaining time and completion flags
 for (int i = 0; i < n; i++) {
 p[i].rt = p[i].bt;
 p[i].completed = 0; }
 int total_time = 0;
 for (int i = 0; i < n; i++) {
 total_time += p[i].bt; // Calculate the total execution time (sum of burst times) }
 // Dynamically allocate memory for the Gantt chart
 int *gantt = (int *)malloc(total_time * sizeof(int)); // Allocate memory for the Gantt chart
 if (gantt == NULL) {
 printf("Memory allocation failed!\n");
 return; }
 int gantt_index = 0;
 printf("\nGantt Chart: \n");
 printf("|");
 while (completed < n) {
 min_bt = INT_MAX;
 min_index = -1;
 for (int i = 0; i < n; i++) { // Find the process with the shortest remaining time that has arrived
 if (p[i].at <= current_time && !p[i].completed && p[i].rt < min_bt) {
 min_bt = p[i].rt;
 min_index = i;
 }}
 if (min_index == -1) { // No process is ready to execute at current_time
 current_time++;
 continue; }
 // Execute the process for one time unit
gantt[gantt_index++] = min_index; // Store the process index in the gantt chart
 p[min_index].rt--;
 current_time++;
 if (p[min_index].rt == 0) { // If the process is completed
 p[min_index].completed = 1;
 completed++;
 p[min_index].ct = current_time;
 p[min_index].tat = p[min_index].ct - p[min_index].at;
 p[min_index].wt = p[min_index].tat - p[min_index].bt;
 }}
 for (int i = 0; i < gantt_index; i++) { // Print the Gantt chart
 printf(" %s |", p[gantt[i]].p_name); }
 printf("\n");
 for (int i = 0; i < gantt_index; i++) {
 printf(" %d ", current_time - gantt_index + i); }
 printf("\n");
 free(gantt); // Free dynamically allocated memory 
 }
int main() {
 int n;
 printf("---------Shortest Job First (Preemptive)---------\n");
 printf("\nEnter the number of processes: ");
 scanf("%d", &n);
 printf("\n");
 struct process *p = (struct process *)malloc(n * sizeof(struct process));
 if (p == NULL) {
 printf("Memory allocation failed!\n");
 return -1; 
}
 for (int i = 0; i < n; i++) {
 printf("Enter 'Name' | 'Arrival Time' | 'Burst Time' for process %d: ", i + 1);
 scanf("%s", p[i].p_name);
 scanf("%d", &p[i].at);
 scanf("%d", &p[i].bt);
 printf("\n"); }
 preemptive_sjf(p, n);
 display(p, n);
 calculations(p, n);
 free(p); // Free dynamically allocated memory
 return 0;
}