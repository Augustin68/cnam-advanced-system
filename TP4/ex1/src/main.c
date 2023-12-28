#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Declaration of a global counter
int counter = 0;

// SIGINT signal handler function
void sigint_handler(int signum) {
    counter++;
    printf("\nNumber of SIGINT signals received: %d\n", counter);
}

// SIGTERM signal handler function
void sigterm_handler(int signum) {
    printf("\nProgram terminated. Total number of SIGINT signals received: %d\n", counter);
    exit(EXIT_SUCCESS);
}

int main() {
    // Install signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    // Infinite loop
    while (1) {
        // Perform your processing here
        // (The program remains waiting for signals)
    }

    return 0;
}
