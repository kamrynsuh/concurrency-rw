#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct _rwlock_t {
    sem_t lock; // mx (or out)
    sem_t writelock;  // wrt
    sem_t fair; // in 
    int readers;
} _rwlock_t;

_rwlock_t mutex;

// define our semaphores
void rwlock_init(_rwlock_t *lock) {
    lock->readers = 0;
    sem_init(&lock->lock, 0, 1); 
    sem_init(&lock->writelock, 0, 1); 
    sem_init(&lock->fair, 0, 1);
}

// a waste time function
void reading_writing(){
    int i, j;
    int x = 0, T; T = rand() % 10000;
    for(i = 0; i < T; i++) {
        for(j = 0; j < T; j++) {
            x = i * j;
        }
    } 
}

// release and acquire for read
void rwlock_acquire_readlock(_rwlock_t *lock) {
    sem_wait(&lock->fair);
    sem_wait(&lock->lock);
    lock->readers++;
    if (lock->readers == 1)  {
	    sem_wait(&lock->writelock);
    }
    sem_post(&lock->lock);
    sem_post(&lock->fair);
}

void rwlock_release_readlock(_rwlock_t *lock) {
    sem_wait(&lock->lock);
    lock->readers--;
    if (lock->readers == 0) {
	    sem_post(&lock->writelock);
    }
    sem_post(&lock->lock);
}

// release and acquire for write
void rwlock_acquire_writelock(_rwlock_t *lock) {
    sem_wait(&lock->fair); /// in
    sem_wait(&lock->writelock);  // wrt
}

void rwlock_release_writelock(_rwlock_t *lock) {
    sem_post(&lock->writelock); // wrt
    sem_post(&lock->fair); // in*/
}

// threads for read + write
void *readThread(void* args) {
    rwlock_acquire_readlock(&mutex);
    printf("Reader's is in... reading\n");
    reading_writing();
    printf("Finished reading\n");
    rwlock_release_readlock(&mutex); 
    return NULL;
}

void *writeThread(void* args) {
    rwlock_acquire_writelock(&mutex);
    printf("Writer's is in... writing\n");
    reading_writing();
    printf("Finished writing\n");
    rwlock_release_writelock(&mutex);
    return NULL;
}


int main() {
    // struct
    
    // variables
    struct _rwlock_t *lock = malloc(sizeof(struct _rwlock_t));
    char rw;
    FILE *file;
    int error;

    //open inputfile
    file = fopen("scenarios.txt", "r");

    //initialize lock
    rwlock_init(lock);

    //for threads
    pthread_t thread;

    if (file)
    {
        //scan input file
        printf("Scenario Starts:\n");
        while (fscanf(file, "%c", &rw) != EOF)
        {
            if (rw == 'r')
            {
                //if read create a thread to run the readThread
                printf("Create reader\n");
                error = pthread_create(&thread, NULL, (void *)readThread, (void *)&lock);
                
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }

            else if (rw == 'w')
            {
                //if write create a thread to run the writeThread
                printf("Create writer\n");
                error = pthread_create(&thread, NULL, (void *)writeThread, (void *)&lock);
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }
        }
    }

    //close file
    fclose(file);

    //exit threads
    pthread_exit(NULL);

    return 0;
}