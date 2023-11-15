#include "tar.h"

int main(int argc, char *argv[]) {

    // TODO : extract file and tasks from options
    char* filename = "/home/tanguy/Seafile/Cours/CNAM/A2/Systèmes_avancées/Projet/test.tar";
    FILE* file;

    if(!(file = fopen(filename, "rb"))) {
        printf("File not existent\n");
        return EXIT_FAILURE;
    }

    struct tar_header header;

    tar_read_header(file, &header);

    print_full_header_info(&header);

    fclose(file);

    return EXIT_SUCCESS;
}