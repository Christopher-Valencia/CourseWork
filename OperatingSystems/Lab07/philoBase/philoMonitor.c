/**
 * Name: Christopher Valencia
 * Lab: Lab07
 * Date: 03/24/21
 **/
 #include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define SLEEP_TIME ( (rand() % 5 + 1) * 1000)

void pickup (int i);
void putdown (int i);
void test (int i);
void stateInit();
void *function();

int numOfSeats, numOfTurns;

pthread_mutex_t monitor_mutex = PTHREAD_MUTEX_INITIALIZER;
enum { THINKING, HUNGRY, EATING} *state;
pthread_cond_t *self;

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: philosophers <number of seats> <number of turns>");
        return 1;
    }

    numOfSeats = strtod(argv[1], NULL);
    numOfTurns = strtod(argv[2], NULL);

    state = calloc(numOfSeats, sizeof(int));
    self = calloc(numOfSeats, sizeof(pthread_cond_t));

    time_t t;
    srand(time(&t));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("Start a dinner for %d diners\n", 5);
    pthread_t philosopher_tid[5];

    stateInit();

    long i;
    for (i = 0; i < numOfSeats; i++)
        pthread_create(&philosopher_tid[i], NULL, function, (void *) i);

    for (i = 0; i < numOfSeats; i++)
        pthread_join(philosopher_tid[i], NULL);

    printf("Dinner is no more.\n");

    free(state);
    free(self);
    return 0;
}

void *function(void *num)
{
    int id = (long) num;

    printf("Philosopher no. %d sits at the table.\n", id);
    usleep(SLEEP_TIME);

    int i;
    for (i = 0; i < numOfTurns; i++)
    {
        printf("Philosopher no. %d gets hungry for the %d time!\n", id, i + 1);
        usleep(SLEEP_TIME);

        pthread_mutex_lock(&monitor_mutex);
        pickup(i);
        printf("Philosopher no. %d eating\n", id);

        usleep(SLEEP_TIME);
        putdown(i);
        pthread_mutex_unlock(&monitor_mutex);
        printf("Philosopher no. %d stopped eating for the %d time!\n", id, i+1);

        printf("Philosopher no. %d finished turn %d\n", id, i + 1);

        pthread_cond_signal(&self[id]);
    }

    printf(">>>>>> Philosopher no. %d finished meal. <<<<<<\n", id);

    pthread_exit(NULL);


}

void pickup (int i)
{
    state[i] = HUNGRY;
    test(i);
    if (state[i] != EATING)
        pthread_cond_wait(&self[i], &monitor_mutex);
        //usleep(SLEEP_TIME);
}

void putdown (int i)
{
    state[i] = THINKING;
    test((i+4) % 5);
    test((i+1) % 5);
}

void test (int i)
{
    if( (state[(i+4) % 5] != EATING) && (state[i] == HUNGRY) && (state[(i+1) % 5] != EATING) )
    {
        state[i] = EATING;
        pthread_cond_signal(&self[i]);
    }
}

void stateInit()
{
    for(int i = 0; i < 5; i++)
        state[i] = THINKING;
}

