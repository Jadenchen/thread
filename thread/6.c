#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;


void *print_hello(void *argu)
{
    sem_wait (&mutex);
    while(1) {
        printf ("hello\n");
        sleep(1);
    }
    sem_post (&mutex);
    return NULL;

}


void *print_world(void *argu)
{
    sem_wait(&mutex);
    while(1) {
        printf ("world\n");
        sleep(1);
    }
    sem_post(&mutex);
    return NULL;

}

int main (void)
{

    pthread_t thread_1, thread_2;
    //init semapore

    sem_init(&mutex,0 ,1);
    pthread_create(&thread_1, NULL, &print_hello, NULL);
    pthread_create(&thread_2, NULL, &print_world, NULL);

    while (1) {
        printf ("-----------------------\n");
        sleep(1);
    }
    sem_destroy(&mutex);

    return 0;
}


