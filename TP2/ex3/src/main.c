#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        handle_error("pipe");
    }

    pid_t pid = fork();

    if (pid == -1) {
        handle_error("fork");
    }

    if (pid == 0) {
        // Code du processus fils

        close(pipefd[0]);

        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            handle_error("dup2");
        }

        close(pipefd[1]);

        execlp("ps", "ps", "eaux", NULL);

        handle_error("execlp");
    } else {
        // Code du processus parent

        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            handle_error("dup2");
        }

        close(pipefd[0]);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            execlp("grep", "grep", "^root", NULL);
            handle_error("execlp");
        } else {
            fprintf(stderr, "Error: Child process terminated abnormally\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}