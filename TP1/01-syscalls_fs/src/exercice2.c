#include "exercice2.h"

void printReverse(const char* filename) {
  printf("printReverse\n");
  int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    off_t fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize == -1) {
        perror("Error seeking to end of file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    off_t position = fileSize - 1;

    while (position >= 0) {
        ssize_t bytesRead = pread(fd, buffer, sizeof(buffer), position);
        if (bytesRead == -1) {
            perror("Error reading file");
            close(fd);
            exit(EXIT_FAILURE);
        }

        for (ssize_t i = bytesRead - 1; i >= 0; --i) {
            putchar(buffer[i]);
        }

        position -= bytesRead;  // Corrected position calculation

        if (position < 0) {
            break;
        }
    }

    close(fd);
    putchar('\n'); // Ajout d'un saut de ligne à la fin
    printf("Fin exercice 2\n");
}