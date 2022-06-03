#include "processor.h"
#include <string.h>

MESSAGE messageCache[CACHE_SIZE];

// TODO add globals to track required statistics
// and to track the index in the messageCache

void addMessageToCache(char *inputLine, int *numMess, int *numBatches, int numTypes[])
{
    // TODO See the description of the Task 10

    char temp[BUFFER_SIZE];
    sscanf(inputLine, "%d %[^\n]", &messageCache[*numMess].type, temp);

    switch (messageCache[*numMess].type)
    {
        case MSG_TYPE_1:
            messageCache[*numMess].content.string = malloc((strlen(temp)+1) * sizeof(char));
            strcpy(messageCache[*numMess].content.string, temp);
            break;
        case MSG_TYPE_2:
            for(int x=0; x<NUM_OF_INTEGERS; x++)
            {
                messageCache[*numMess].content.integers[x] = strtol(inputLine, temp, 10);
            }
            break;
        case MSG_TYPE_3:
            for(int x=0; x<NUM_OF_DOUBLES; x++)
            {
                messageCache[*numMess].content.doubles[x] = strtod(inputLine, temp);
            }
            break;
        case MSG_TYPE_4:
            sscanf(temp, " %s %s %s",
                   messageCache[*numMess].content.words[0],
                   messageCache[*numMess].content.words[1],
                   messageCache[*numMess].content.words[2]);
            break;
    }

    *numMess++;
    if(*numMess == CACHE_SIZE)
    {
        messageDispatcher(numBatches, numMess, numTypes);
    }
}

void messageDispatcher(int *numBatches, int *numMess, int *numTypes)
{
    // TODO See the description of the Task 10
    for(int x=0; x<*numMess; x++)
    {
        processMessage(&messageCache[x], numTypes);
    }
    *numBatches++;
    *numMess=0;
}

void processMessage(MESSAGE *message, int *numTypes)
{
    // TODO See the description of the Task 10
    switch (message->type)
    {
        case MSG_TYPE_1:
            printf("TYPE 1 : &s\n", message->content.string);
            numTypes[MSG_TYPE_1-1]++;
            free(message->content.string);
            break;
        case MSG_TYPE_2:
            printf("TYPE 2 :");
            for (int x=0; x<NUM_OF_INTEGERS; x++)
            {
                printf(" %d", message->content.integers[x]);
            }
            printf("\n");
            numTypes[MSG_TYPE_2-1]++;
            break;
        case MSG_TYPE_3:
            printf("TYPE 3 :");
            for (int x=0; x<NUM_OF_DOUBLES; x++)
            {
                printf(" %.1lf", message->content.doubles[x]);
            }
            printf("\n");
            numTypes[MSG_TYPE_3-1]++;
            break;
        case MSG_TYPE_4:
            printf("TYPE 4 :");
            for(int x=0; x<NUM_OF_STRINGS; x++)
            {
                printf(" %s", message->content.words[x]);
            }
            printf("\n");
            numTypes[MSG_TYPE_4-1]++;
            break;
    }
}

void printStatistics(int numMess, int numBatches, int numTypes[])
{
    // TODO See the description of the Task 10


    printf("Number of batches processed : %d\n", numBatches);


}
