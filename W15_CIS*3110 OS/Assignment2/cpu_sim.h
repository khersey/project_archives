/* filename:   cpu_sim.h
 * author:     Kyle Hersey
 * student#:   0851973
 * course:     CIS*3110
 * assignment: 2
 *
 * This file contains function declarations for all function in main.c and
 * also contains structure and type definitions for process, thread, burst and state_type types.
 */

#include "priorityQueue.h"
#include "fifoQueue.h"

typedef enum state_type {
    NEW,
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED,
} state_type; 


typedef struct thread thread;
typedef struct burst burst;
typedef struct process process;

struct burst {
    int burst_ID;
    int cpu_time;
    int cpu_remain;
    int io_time;
    thread * parent_thread;
};

struct thread {
    int thread_ID;
    int arrival_time;
    int finish_time;
    int i; 
    int burst_count;
    state_type state;
    burst * child_burst;
    process * parent_process;
    
};

struct process {
    int process_ID;
    int thread_count;
    thread * child_thread;
};

typedef struct settings settings;
struct settings {
    int process_count;
    int thread_switch;
    int process_switch;
    int v;
    int d;
    int r;
};


void parseProcesses(FILE *fp, process **p_adt, settings s);

void parseThread(FILE *fp, thread **t);

void fillPriorityQueue(pQueue pq, process *p_adt, settings s);

void fillFIFOQueue(queue fq, process *p_adt, settings s);

void printProcesses(process *p_adt, settings s);

void freeProcesses(process *p_adt, settings s);

void fcfs(process *p_adt, pQueue readyQ, settings s);

void rr(process *p_adt, queue readyQ, settings s);

int validTopItem(pQueue pq, int cTime);

int allThreadsTerminated(process * p_adt, settings s);

void turnAroundTime(process * p_adt, settings s, int cTime, int average);

