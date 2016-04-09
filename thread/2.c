#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *print_hello(void *argu)
{
    while(1) {
        printf ("%s\n", (char *)argu);
        sleep(1);
    }
    return NULL;

}


void *print_world(void *argu)
{
    while(1) {
        printf ("%s\n", (char *)argu);
        sleep(1);
    }
    return NULL;

}

int main (void)
{

    pthread_t thread_1, thread_2;
    char argu1[] = "hello";
    char argu2[] = "world";
    pthread_create(&thread_1, NULL, &print_hello, argu1);
    pthread_create(&thread_2, NULL, &print_world, argu2);

    while (1) {
        printf ("-----------------------\n");
        sleep(1);
    }

    return 0;
}


