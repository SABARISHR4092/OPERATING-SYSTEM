#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 5
#define MAX_WRITERS 2

sem_t mutex;
sem_t writeBlock;
int readCount = 0;

void* reader(void* arg) {
    int readerID = *((int*)arg);
    while (1) {
        sem_wait(&mutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);

        printf("Reader %d is reading\n", readerID);
        sleep(1); // Simulate reading time

        sem_wait(&mutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&writeBlock);
        }
        sem_post(&mutex);
        sleep(1); // Simulate time between reads
    }
}

void* writer(void* arg) {
    int writerID = *((int*)arg);
    while (1) {
        sem_wait(&writeBlock);
        printf("Writer %d is writing\n", writerID);
        sleep(2); // Simulate writing time
        sem_post(&writeBlock);
        sleep(1); // Simulate time between writes
    }
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int readerIDs[MAX_READERS], writerIDs[MAX_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    for (int i = 0; i < MAX_READERS; i++) {
        readerIDs[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIDs[i]);
    }

    for (int i = 0; i < MAX_WRITERS; i++) {
        writerIDs[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIDs[i]);
    }

    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);
    return 0;
}
