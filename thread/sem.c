#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct job_s {
    int status;
    struct job_s *next;

};

struct job_s *job;
/* critical section protection */
pthread_mutex_t job_mutex = PTHREAD_MUTEX_INITIALIZER;

/* semaphore varialbe */
sem_t job_semaphore;

void *add_job()
{

    struct job_s *new_job;
    char inp[32];
    int count;
//    printf ("add job\n");
    while (1) {
        printf ("\n-----------input a job \n");
        printf ("job status: ");
        scanf ("%s", inp);

        new_job = (struct job_s *) malloc (sizeof(struct job_s));
        //new_job->status = 1;
        new_job->status = atoi(inp);
	printf ("new_job status %d \n", new_job->status);
        if (new_job->status == 0) {
            printf ("return null \n");
            return NULL;
        }

        //critical section
        sem_wait(&job_semaphore);
        pthread_mutex_lock(&job_mutex);


        new_job->next = job;
        job = new_job;
        //printf ("critical section add job\n");

        pthread_mutex_unlock (&job_mutex);
        sem_post(&job_semaphore);
    }
}



void *remove_job()
{

    struct job_s *this_job;
    int count;
    printf ("remove job\n");
    while (1) {

        count = 0;
        sleep(5);

        /*critical section */
        sem_wait(&job_semaphore);
        pthread_mutex_lock (&job_mutex);
        //this_job = job;

        for (this_job = job; this_job != NULL; this_job = this_job->next)
            if (this_job->status == 0)
                count++;

        pthread_mutex_unlock(&job_mutex);
        sem_post(&job_semaphore);
        printf (" count  is %d \n",count);
    }

}


void *process_job()
{
    struct job_s *this_job;
    printf ("process job\n");
    while (1) {

        sleep(5);
        /* critical section */
        sem_wait(&job_semaphore);
        pthread_mutex_lock (&job_mutex);

        for (this_job = job; this_job != NULL; this_job = this_job->next) {
            if (this_job->status > 0)
                this_job->status--;
            //else
              //  continue;
        }
        pthread_mutex_unlock (&job_mutex);
        sem_post (&job_semaphore);
    }
}


int main ()
{
    pthread_t thread_1, thread_2, thread_3;

    job = NULL;
    sem_init(&job_semaphore, 0, 0);

    pthread_create (&thread_1, NULL, &add_job, NULL);
    /*wait for add a job */
//        pthread_join (thread_1, NULL);

    pthread_create (&thread_2, NULL, &remove_job, NULL);
    pthread_create (&thread_3, NULL, &process_job, NULL);

    printf ("sem post \n");
    /*post operation */
    sem_post(&job_semaphore);

    printf ("wait add a job\n");
    /*wait for add a job */
    pthread_join (thread_1, NULL);
//	pthread_join (thread_2, NULL);
//	pthread_join (thread_3, NULL);
    return 0;

}








