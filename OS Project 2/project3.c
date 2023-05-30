#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5

int count = 0;
pthread_mutex_t mutex;
pthread_cond_t fullBox, emptyBox;
int terminate=0;

void getToyFromBox() {
    pthread_mutex_lock(&mutex);
    while (count == 0) {
        pthread_cond_wait(&fullBox, &mutex);
    }
    count--;
    printf("Child: Took a toy from the box\n");
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&emptyBox);
}

void refillToyBox() {
    pthread_mutex_lock(&mutex);
    while (count == N) {
        pthread_cond_wait(&emptyBox, &mutex);
    }
    count++;
    printf("Mother: Refilled the toy box\n");
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&fullBox);
}

void *childThread(void *arg) {
    while (1) {
        if(terminate)
            break;
        getToyFromBox();
        
        sleep(1);
    }
    return NULL;
}

void *motherThread(void *arg) {
    while (1) {
        if(terminate)
            break;
        refillToyBox();
        
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t child, mother;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&fullBox, NULL);
    pthread_cond_init(&emptyBox, NULL);

    pthread_create(&child, NULL, childThread, NULL);
    pthread_create(&mother, NULL, motherThread, NULL);

    printf("Press enter to stop the loop\n");
    getchar();
    terminate=1;

    pthread_join(child, NULL);
    pthread_join(mother, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&fullBox);
    pthread_cond_destroy(&emptyBox);

    return 0;
}
