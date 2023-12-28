#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE (int)1e8
int tab[SIZE];

void fillArrayWithRandomValues() {
    int i;
    srand(time(NULL)); // Initialize the random number generator with a different seed on each execution

    for (i = 0; i < SIZE; i++) {
        tab[i] = rand();
    }
}

void findMinAndMax() {
    int i;
    int min = tab[0];
    int max = tab[0];

    struct timeval start, end;
    gettimeofday(&start, NULL); // Record the start time

    for (i = 1; i < SIZE; i++) {
        if (tab[i] < min) {
            min = tab[i];
        } else if (tab[i] > max) {
            max = tab[i];
        }
    }

    gettimeofday(&end, NULL); // Record the end time

    printf("The minimum of the array is: %d\n", min);
    printf("The maximum of the array is: %d\n", max);

    // Calculate and print the time taken in microseconds
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    long elapsed = seconds * 1000000 + microseconds;
    printf("Time taken to find min and max: %ld ms\n", elapsed / 1000);
}

int main() {
    fillArrayWithRandomValues();
    findMinAndMax();

    return 0;
}
