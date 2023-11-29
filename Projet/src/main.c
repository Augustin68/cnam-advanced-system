#include <stdio.h> 
#include <unistd.h>

#include "tar.h"

int main(int argc, char *argv[]) 
{
    int opt;
    char* filename = NULL;
    int list = 0;

    while((opt = getopt(argc, argv, ":lf:")) != -1)
    {
        switch(opt)
        {
            case 'f':
                filename = optarg;
                break;
            case 'l':
                list = 1;
                break;
            case '?': 
                printf("unknown option: %c\n", opt);
                break; 
        }
    }

    FILE* file;

    if(!(file = fopen(filename, "rb"))) {
        printf("File not existent\n");
        return EXIT_FAILURE;
    }

    
    if(list) 
    {
        tar_list(file);
    }

    fclose(file);

    return EXIT_SUCCESS;
}