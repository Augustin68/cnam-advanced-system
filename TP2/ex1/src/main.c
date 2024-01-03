#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // Utilisation de fork pour créer un processus fils
    pid_t pid = fork();

    if (pid == -1) {
        // Erreur lors de la création du processus fils
        perror("Erreur fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Code du processus fils
        printf("Processus fils - PID : %d, PID du père : %d\n", getpid(), getppid());

        // Sortie avec le dernier chiffre du PID comme code de retour
        int lastDigit = getpid() % 10;
        exit(lastDigit);
    } else {
        // Code du processus père
        printf("Processus père - PID du fils : %d\n", pid);

        // Attend la terminaison du processus fils
        int status;
        pid_t terminated_pid = wait(&status);

        if (terminated_pid == -1) {
            perror("Erreur wait");
            exit(EXIT_FAILURE);
        }

        // Vérifie si le processus fils s'est terminé normalement
        if (WIFEXITED(status)) {
            printf("Le processus fils avec PID %d s'est terminé avec le code de retour : %d\n", terminated_pid, WEXITSTATUS(status));
        } else {
            printf("Le processus fils avec PID %d s'est terminé de manière anormale.\n", terminated_pid);
        }
    }

    return 0;
}