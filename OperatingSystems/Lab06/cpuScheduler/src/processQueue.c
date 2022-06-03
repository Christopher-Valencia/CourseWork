/**
 * Name: Christopher Valencia
 * Lab: Lab06
 * Date: 03/10/21
 **/
#include "processQueue.h"

PROCESS *processTable;
int processTableSize = 0;
int processTableAdded = 0;
int processTableCapacity;

PROCESS **readyQueue;
int readyQueueSize = 0;
int readyQueueCapacity;


/***
 * constructor of the process table
 */
void createProcessTable(int capacity)
{
    processTable = (PROCESS *) malloc(capacity * sizeof(PROCESS));
    processTableCapacity = capacity;
}


/***
 * constructor of the ready queue
 */
void createReadyQueue(int capacity)
{
    readyQueue = (PROCESS **) malloc(capacity * sizeof(PROCESS *));
    readyQueueCapacity = capacity;
}


/***
 * display the processes table
 */
void displayProcessTable()
{
    printf("PROCESSES:\n\nName    \tEntry\tBurst\n");
    for (int i = 0; i < processTableSize; i++)
    {
        printf("%-8s\t%3d   \t%3d   \n", processTable[i].name, processTable[i].entryTime, processTable[i].burstTime);
    }
    printf("\n");
}


/***
 * displays the contents of the ready queue
 */
void displayQueue()
{
    int i;
    printf("QUEUE: ");

    if (readyQueueSize <= 0)
        printf("<empty>");
    else
    {
        for (i = 0; i < readyQueueSize; i++)
        {
            printf("%s(%d) ", readyQueue[i]->name, readyQueue[i]->burstTime);
        }
    }
}


/***
 * calculates and prints the average wait time using information in the process table
 */
void printAverageWaitTime()
{
    int i = 0;
    double sum = 0;
    for (i = 0; i < processTableSize; i++)
    {
        sum = sum + processTable[i].waitTime;
        printf("Process %s Wait Time: %.2lf\n", processTable[i].name, (double) processTable[i].waitTime);
    }
    printf("Average Wait Time: %.2lf\n", (sum / (double) processTableSize));
}


/***
 * adds a process and expands the table if necessary
 */
void addProcessToTable(PROCESS process)
{
    if (processTableSize >= processTableCapacity) //if array too small
    {
        processTableCapacity *= 2; //double capacity
        processTable = (PROCESS *) realloc(processTable, processTableCapacity * sizeof(PROCESS));
    }

    processTable[processTableSize++] = process;
}


/***
 * adds any processes that arrive at the current time to ready queue
 */
void addArrivingProcessesToReadyQueue(int time)
{
    if (processTable[processTableAdded].entryTime == time)
        addProcessToReadyQueue(&processTable[processTableAdded++]);
}


/***
 * determines if any processes in the process table still need to execute
 */
//will determine if any processes in the process queue have more to execute
bool processesLeftToExecute()
{
// TODO: implement
    for(int x=0; x<processTableSize; x++)
    {
        if(processTable[x].burstTime != 0)
            return true;
    }

    return false; //return 0 if all processes are complete
}


/***
 * adds a process to the ready queue and expands it if necessary
 */
void addProcessToReadyQueue(PROCESS *pointer)
{
    if (readyQueueSize >= readyQueueCapacity) //if array too small
    {
        readyQueueCapacity *= 2; //double capacity
        readyQueue = (PROCESS **) realloc(readyQueue, readyQueueCapacity * sizeof(PROCESS *));
    }

// TODO: complete
    readyQueue[readyQueueSize] = pointer;
    readyQueueSize++;
}


/***
 * removes a process from the ready queue and fills the "hole"
 */
void removeProcessFromReadyQueue(PROCESS *p)
{
// TODO: implement
    for(int x=0; x<readyQueueSize; x++)
    {
        if(strcmp(readyQueue[x]->name, p->name)==0)
        {
            for(int y=x; y<readyQueueSize-1; y++)
            {
                readyQueue[y]=readyQueue[y+1];
            }
            break;
        }
    }
    readyQueueSize--;
}


/***
 * fetches the first process from the ready queue
 */
PROCESS *fetchFirstProcessFromReadyQueue()
{
// TODO: implement
    return readyQueue[0];
}


/***
 * finds the shortest job in the ready queue
 */
PROCESS *findShortestProcessInReadyQueue()
{
// TODO: implement
    if(readyQueueSize == 1)
        return readyQueue[0];

    int shortest=0;
    for(int x=1; x<readyQueueSize; x++)
    {
        if(readyQueue[x]->burstTime < readyQueue[shortest]->burstTime)
            shortest=x;
    }
    return readyQueue[shortest];
}


/***
 * clean up the process table
 */
void cleanUp()
{
// TODO: implement
    free(readyQueue);
    free(processTable);
}





