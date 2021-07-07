#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NO_PRODUCERS 6
#define NO_CONSUMERS 3


sem_t sem_empty; //define the number of empty slots in the buffer
sem_t sem_full; // define the number of full slots in the buffer

pthread_mutex_t mutex;

int buffer[10]; //the number of available slots
int ind = 0; //index holds the slots where producer will put the items and where consumer will take the item
int sleep_time = 1;




void* producer(void* args)
{
    while(1)
    {
        int produced = rand() % 100; //produce item
        sleep(sleep_time);

        sem_wait(&sem_empty);
        pthread_mutex_lock(&mutex); //we lock here to not allow other threads execute this piece of code

        buffer[ind] = produced;
        ind++;
        printf("\nProducer %d inserts %d\n", *((int *)args), produced);


        pthread_mutex_unlock(&mutex);
        sem_post(&sem_full);

    }
}

void* consumer(void* args)
{
    while (1)
    {
        //remove from the buffer
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex);

        int consumed = buffer[ind - 1];
        ind--;
        printf("\nConsumer %d takes %d\n", *((int *)args), consumed);

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_empty);

        sleep(sleep_time);

    }
}

int main()
{
    srand(time(NULL));
    pthread_t threads[NO_PRODUCERS + NO_CONSUMERS]; //initializing threads
    pthread_mutex_init(&mutex, NULL);

    int number[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


    //initializing semaphores
    sem_init(&sem_empty, 0, 10);
    sem_init(&sem_full, 0, 0);



    for (int i = 0; i < NO_PRODUCERS; i++)
    {
        if (pthread_create(&threads[i], NULL, &producer, (void *)&number[i]) != 0)
            perror("Failed to create producer");
    }

    for (int i = 0; i < NO_CONSUMERS; i++)
    {
        if (pthread_create(&threads[i + NO_PRODUCERS], NULL, &consumer, (void *)&number[i]) != 0)
            perror("Failed to create consumer");
    }



    for (int i = 0; i < NO_PRODUCERS + NO_CONSUMERS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
