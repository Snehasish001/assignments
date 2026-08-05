#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0, readCount = 0;

sem_t mutex, wrt;

void *reader(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&mutex);

    readCount++;
    if(readCount == 1)
        sem_wait(&wrt);

    sem_post(&mutex);

    printf("Reader %d reads %d\n", id, data);
    sleep(1);

    sem_wait(&mutex);

    readCount--;
    if(readCount == 0)
        sem_post(&wrt);

    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&wrt);

    data++;
    printf("Writer %d writes %d\n", id, data);
    sleep(1);

    sem_post(&wrt);

    return NULL;
}

int main()
{
    pthread_t r[3], w[2];

    int rid[3]={1,2,3};
    int wid[2]={1,2};

    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);

    pthread_create(&r[0],NULL,reader,&rid[0]);
    pthread_create(&r[1],NULL,reader,&rid[1]);

    pthread_create(&w[0],NULL,writer,&wid[0]);

    pthread_create(&r[2],NULL,reader,&rid[2]);

    pthread_create(&w[1],NULL,writer,&wid[1]);

    for(int i=0;i<3;i++)
        pthread_join(r[i],NULL);

    for(int i=0;i<2;i++)
        pthread_join(w[i],NULL);

    return 0;
}