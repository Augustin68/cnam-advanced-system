#include <stdio.h> 
#include <unistd.h>

#include "tar.h"

int main(int argc, char *argv[]) 
{
    int opt;
    char* filename = "./archive.tar";
    int list = 0, extract = 0;

    while((opt = getopt(argc, argv, ":elf:")) != -1)
    {
        switch(opt)
        {
            case 'f':
                filename = optarg;
                break;
            case 'l':
                list = 1;
                break;
            case 'e':
                extract = 1;
                break;
            case '?': 
                printf("unknown option: %c\n", opt);
                break; 
        }
    }

    FILE* file;

    if(!(file = fopen(filename, "w+b"))) {
        printf("File not existent\n");
        return EXIT_FAILURE;
    }

    
    if(list) 
    {
        tar_list(file);
    }

    if(extract) 
    {
        tar_extract_archive(file);
    }

    FILE* f = fopen("./heeeeeeey.txt", "r");

    tar_generate_archive(file, f, "./heeeeeeey.txt");

    fclose(file);

    return EXIT_SUCCESS;
}
