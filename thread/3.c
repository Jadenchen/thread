#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>






void *print_hello(void *argu)
{
    while(1) {
        printf ("hello\n");
        sleep(1);
    }
    return NULL;

}


void *print_world(void *argu)
{
    while(1) {
        printf ("world\n");
        sleep(1);
    }
    return NULL;

}

int main (void)
{
    //detached thread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t thread_1, thread_2;
    pthread_create(&thread_1, &attr, &print_hello, NULL);
    pthread_create(&thread_2, &attr, &print_world, NULL);

    while (1) {
        printf ("-----------------------\n");
        sleep(1);
    }

    return 0;
}


