#include <stdio.h> 
#include <unistd.h>

#include "tar.h"

void usage(char *name) 
{
    printf("Utilisation : %s -f ARCHIVE_FILE [-l] [-e] [-c FILE] [-h]\n", name);
    printf("-f ARCHIVE_FILE : précise le nom de l'archive (obligatoire pour la création d'une archive)\n");
    printf("-l : liste le contenu de l'archive\n");
    printf("-e : extrait le contenu de l'archive\n");
    printf("-c FILE : génère une archive avec les noms de fichiers précisés\n");
    printf("-h : affiche ce message d'aide\n");
}

int main(int argc, char *argv[]) 
{
    int opt;
    char* archivename;
    char* filenames[argc];
    int list = 0, extract = 0, compress = 0;
    int nb_files = 0;


    while((opt = getopt(argc, argv, ":e:l:hc:")) != -1)
    {
        switch(opt)
        {
            case 'f':
                compress = 1;
                archivename = optarg;               
                break;
            case 'l':
                list = 1;
                archivename = optarg;               
                break;
            case 'e':
                extract = 1;
                archivename = optarg;
                break;
            case 'c':
                compress = 1;
                filenames[nb_files] = optarg;
                nb_files++;
                break;
            case '?': 
                fprintf(stderr, "Unknown option: %c\n", opt);
                break; 
            default: 
                usage(argv[0]);
                break;
        }
    }

    if(list == 0 && extract == 0 && compress == 0) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    FILE* archive;

    char* mode = "r+b";

    if(compress) 
    {
        mode = "w+b";
    }

    if(!(archive = fopen(archivename, mode))) {
        fprintf(stderr, "Error : main() : cannot fopen archive\n");
        fprintf(stderr, strerror(errno));
        return EXIT_FAILURE;
    }


    if(list) 
    {
        tar_list(archive);
    }

    if(extract)
    {
        tar_extract_archive(archive);
    }

    if(compress)
    {
        tar_generate_archive(archive, filenames, nb_files);
    }

    fclose(archive);


    return EXIT_SUCCESS;
}
