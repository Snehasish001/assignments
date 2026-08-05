#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readCount = 0;
int data = 0;

sem_t mutex;      // Protects readCount
sem_t wrt;        // Controls database access
sem_t readTry;    // Blocks readers when writer is waiting

void *reader(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&readTry);
    sem_wait(&mutex);

    readCount++;
    if (readCount == 1)
        sem_wait(&wrt);

    sem_post(&mutex);
    sem_post(&readTry);

    printf("Reader %d is reading: %d\n", id, data);
    sleep(1);

    sem_wait(&mutex);

    readCount--;
    if (readCount == 0)
        sem_post(&wrt);

    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&readTry);   // Stop new readers
    sem_wait(&wrt);

    data++;
    printf("Writer %d is writing: %d\n", id, data);
    sleep(2);

    sem_post(&wrt);
    sem_post(&readTry);

    return NULL;
}

int main()
{
    pthread_t r[3], w;
    int rid[3] = {1, 2, 3};
    int wid = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    sem_init(&readTry, 0, 1);

    pthread_create(&r[0], NULL, reader, &rid[0]);
    pthread_create(&r[1], NULL, reader, &rid[1]);

    sleep(1);

    pthread_create(&w, NULL, writer, &wid);

    sleep(1);

    pthread_create(&r[2], NULL, reader, &rid[2]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    pthread_join(w, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    sem_destroy(&readTry);

    return 0;
}