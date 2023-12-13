#include "tar.h"

int tar_read_header(FILE* file, struct tar_header* header) 
{
    if(file == NULL) 
    {
        printf("Bad file\n"); // TODO : better error management
        return -1;
    }

    if(fread(header, sizeof(struct tar_header), 1, file)) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void print_full_header_info(struct tar_header* header) 
{
    printf("Nom du fichier : %s\n", header->name);
    printf("Mode d'accès : %s\n", header->mode);
    printf("ID du propriétaire : %s\n", header->owner);
    printf("ID du groupe : %s\n", header->group);
    printf("Taille du fichier : %lu octets\n", strtol(header->size, NULL, 8));
    
    time_t mtime = strtol(header->mtime, NULL, 8);
    struct tm *tm_info = localtime(&mtime);
    char mtime_str[20];
    // strftime(mtime_str, sizeof(mtime_str), "%Y-%m-%d %H:%M:%S", tm_info);
    strftime(mtime_str, sizeof(mtime_str), "%d-%m-%Y %H:%M:%S", tm_info);

    printf("Date de modification : %s\n", mtime_str);
    printf("Somme de contrôle : %s\n", header->checksum);
    printf("Type de fichier : %c\n", header->type);
    printf("Nom du lien : %s\n", header->linkname);

    printf("\n");
}

bool tar_header_is_empty(struct tar_header* header)
{
    if(header->name[0] == '\0' && header->size[0] == '\0' && header->type == '\0') 
    {
        return true;       
    }
    else
    {
        return false;
    }
}

void tar_list(FILE* file) 
{
    long int bytes_read = 0;
    fseek(file, 0, SEEK_END);
    long int tar_file_size = ftell(file);
    fseek(file, 0, SEEK_SET); 

    struct tar_header header;

    while(bytes_read < tar_file_size) 
    {
        tar_read_header(file, &header);

        if(tar_header_is_empty(&header)) 
            break;

        bytes_read += (sizeof header);

        printf("%s - %lu octets\n", header.name, strtol(header.size, NULL, 8));

        long int file_size = strtol(header.size, NULL, 8);
        long int size_to_seek = (file_size  + 511) / 512 * 512; // We round up to the next multiple of 512
        
        fseek(file, size_to_seek, SEEK_CUR); // Seek to skip the content of the file

        bytes_read += size_to_seek;
    }

    // just in case
    fseek(file, 0, SEEK_SET); 
}

void tar_extract_archive(FILE* file) 
{
    struct tar_header header;

    while(true)
    {
        tar_read_header(file, &header);
        
        if(tar_header_is_empty(&header))
        {
            break;
        }

        if(strtol(header.size, NULL, 8) == 0)
        {
            tar_create_folder(&header);
        }
        else
        {
            tar_extract_file(file, &header);
        }
    }

    // just in case
    fseek(file, 0, SEEK_SET); 
}

bool tar_extract_file(FILE* archive, struct tar_header* header)
{
    FILE* file = fopen(header->name, "w");

    long int file_size = strtol(header->size, NULL, 8);

    if(!file) 
        return false;

    int* temp = malloc(512);

    for (long int i = 0; i < file_size; i += 512)
    {
        if((file_size) - i > 511) // 
        {
            fread(temp, 512, 1, archive);
            fwrite(temp, 512, 1, file);            
        }
        else 
        {
            // If there are less than 512 bytes left to extract : we extract what remains and put the cursor at the end of the block
            fread(temp, file_size - i, 1, archive);
            fwrite(temp, file_size - i, 1, file); 
            fseek(archive, i + 512 - file_size, SEEK_CUR);
            break;
        }
    }
    
    free(temp);
    fclose(file);

    return true;
}

bool tar_create_folder(struct tar_header* header)
{
    if(strtol(header->size, NULL, 8) > 0) // if size > 0 : not a folder
    {
        return false;
    }

    return mkdir(header->name, strtol(header->mode, NULL, 8));
}