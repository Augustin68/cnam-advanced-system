#include <stdio.h> 
#include <unistd.h>

#include "tar.h"

int main(int argc, char *argv[]) 
{
    int opt;
    char* archivename;
    char* filenames[argc];
    int list = 0, extract = 0, compress = 0;
    int nb_files = 0;


    while((opt = getopt(argc, argv, ":elc:f:")) != -1)
    {
        switch(opt)
        {
            case 'f':
                archivename = optarg;               
                break;
            case 'l':
                list = 1;
                break;
            case 'e':
                extract = 1;
                break;
            case 'c':
                compress = 1;
                filenames[nb_files] = optarg;
                nb_files++;
                break;
            case '?': 
                fprintf(stderr, "Unknown option: %c\n", opt);
                break; 
        }
    }

    FILE* archive;

    char* mode = "r+b";

    if(compress) 
    {
        mode = "w+b";
    }

    if(!(archive = fopen(archivename, mode))) {
        fprintf(stderr, "Error : main() : cannot fopen archive\n");
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
