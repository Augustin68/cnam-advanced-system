#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define SIZE (int)1e8
#define NUM_THREADS 8

int tab[SIZE];

// Structure to hold result data
typedef struct {
    int min;
    int max;
    long elapsed;
    pthread_mutex_t mutex; // Mutex to protect access to result variables
} ThreadResult;

// Global result variable
ThreadResult result;

// Function to fill the array with random values
void fillArrayWithRandomValues() {
    int i;
    srand(time(NULL));

    for (i = 0; i < SIZE; i++) {
        tab[i] = rand();
    }
}

// Function to find min and max values in a given range
void* findMinAndMaxRange(void* arg) {
    int thread_id = *((int*)arg);
    int chunk_size = SIZE / NUM_THREADS;
    int start = thread_id * chunk_size;
    int end = (thread_id == NUM_THREADS - 1) ? SIZE : (thread_id + 1) * chunk_size;

    int local_min = tab[start];
    int local_max = tab[start];

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = start + 1; i < end; i++) {
        if (tab[i] < local_min) {
            local_min = tab[i];
        } else if (tab[i] > local_max) {
            local_max = tab[i];
        }
    }

    gettimeofday(&end_time, NULL);

    // Lock the mutex before updating global result variables
    pthread_mutex_lock(&result.mutex);

    // Update the global result structure
    result.min = (local_min < result.min) ? local_min : result.min;
    result.max = (local_max > result.max) ? local_max : result.max;
    result.elapsed += (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

    // Unlock the mutex after updating global result variables
    pthread_mutex_unlock(&result.mutex);

    pthread_exit(NULL);
}

int main() {
    fillArrayWithRandomValues();

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    result.min = tab[0];
    result.max = tab[0];
    result.elapsed = 0;

    // Initialize the mutex
    if (pthread_mutex_init(&result.mutex, NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, findMinAndMaxRange, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&result.mutex);

    printf("The minimum of the array is: %d\n", result.min);
    printf("The maximum of the array is: %d\n", result.max);
    printf("Time taken to find min and max with %d threads: %ld ms\n", NUM_THREADS, result.elapsed / 1000);

    return 0;
}
