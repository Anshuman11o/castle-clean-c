#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int sharedResource = 0;

void* threadFunction(void* arg) {
    int result = pthread_mutex_lock(&mutex);
    if (result != 0) {
        return NULL;
    }

    int temp = sharedResource;
    printf("Thread %ld: Read sharedResource = %d\n", (long)arg, temp);
    if ((long)arg % 2 == 0) {
        sleep(1);
    }
    sharedResource = temp + 1;
    printf("Thread %ld: Updated sharedResource to %d\n", (long)arg, sharedResource);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[5];

    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, threadFunction, (void*)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Final value of sharedResource = %d\n", sharedResource);

    return 0;
}
