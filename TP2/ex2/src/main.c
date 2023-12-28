#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int printWord(char* message) {
    printf("Le premier mot passé en ligne de commande est : %s\n", message);
    return 0;
}

int main(int argc, char *argv[]) {
    // Vérifier le nombre de paramètres
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mot>\n", argv[0]);
        return 1; // Retourner une erreur
    }

    // Création du processus fils
    pid_t pid = fork();

    if (pid == -1) {
        perror("Erreur lors de la création du processus fils");
        return 1;
    }

    if (pid == 0) {
        // Code du processus fils

        // Afficher le PID du fils
        printf("[fils] - PID du fils : %d\n", getpid());

        // Fermer le descripteur de fichier STDOUT (1)
        close(1);

         // Créer un modèle de nom de fichier modifiable
        char template[] = "/tmp/proc-exerciseXXXXXX";
        
        // Utiliser mkstemp pour créer et ouvrir le fichier temporaire
        int fd = mkstemp(template);

        if (fd == -1) {
            perror("[fils] - Erreur lors de l'ouverture du fichier temporaire");
            exit(EXIT_FAILURE);
        }

        // Afficher le numéro du descripteur du fichier ouvert
        printf("[fils] - Numéro du descripteur du fichier ouvert : %d\n", fd);

        // Utiliser dup2 pour rediriger le descripteur de fichier
        if (dup2(fd, 1) == -1) {
            perror("[fils] - Erreur lors de la redirection du descripteur de fichier");
            exit(EXIT_FAILURE);
        }

        // Exécuter le programme de base
        printWord(argv[1]);
    } else {
        // Code du processus père

        // Afficher le PID du père
        printf("[père] - PID du père : %d\n", getpid());

        // Attendre la fin du fils
        int status;
        waitpid(pid, &status, 0);

        // Afficher un message avant de terminer
        printf("[père] - That's All Folks !\n");
    }

    return 0;
}
