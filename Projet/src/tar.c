#include "tar.h"

// read header from tar archive
int tar_read_header(FILE* file, struct tar_header* header) 
{
    if(file == NULL) 
    {
        printf("Bad file\n"); 
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

// display all informations from a tar header (for debug)
void print_full_header_info(struct tar_header* header) 
{
    printf("Nom du fichier : %s\n", header->name);
    printf("Mode d'accès : %s\n", header->mode);
    printf("ID du propriétaire : %s\n", header->owner);
    printf("ID du groupe : %s\n", header->group);
    printf("Taille du fichier : %lu octets\n", strtol(header->size, NULL, OCTAL_BASE));
    
    time_t mtime = strtol(header->mtime, NULL, OCTAL_BASE);
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

// check if tar header is empty
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

// list all files in tar archive
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

        printf("%s - %lu octets\n", header.name, strtol(header.size, NULL, OCTAL_BASE));

        long int file_size = strtol(header.size, NULL, OCTAL_BASE);
        long int size_to_seek = (file_size  + BLOCKSIZE - 1) / BLOCKSIZE * BLOCKSIZE; // We round up to the next multiple of BLOCKSIZE
        
        fseek(file, size_to_seek, SEEK_CUR); // Seek to skip the content of the file

        bytes_read += size_to_seek;
    }

    // just in case
    fseek(file, 0, SEEK_SET); 
}

// extract all files from tar archive
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

        if(strtol(header.size, NULL, OCTAL_BASE) == 0)
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

// extract a single file from tar archive
bool tar_extract_file(FILE* archive, struct tar_header* header)
{
    FILE* file = fopen(header->name, "w");

    if(file == NULL) 
    {
        fprintf(stderr, "Error : tar_extract_file() : cannot fopen archive\n");
        fprintf(stderr, strerror(errno));
    }

    long int file_size = strtol(header->size, NULL, OCTAL_BASE);

    if(!file) 
        return false;

    int* temp = malloc(BLOCKSIZE);

    for (long int i = 0; i < file_size; i += BLOCKSIZE)
    {
        if((file_size) - i > 511) // 
        {
            fread(temp, BLOCKSIZE, 1, archive);
            fwrite(temp, BLOCKSIZE, 1, file);            
        }
        else 
        {
            // If there are less than BLOCKSIZE bytes left to extract : we extract what remains and put the cursor at the end of the block
            fread(temp, file_size - i, 1, archive);
            fwrite(temp, file_size - i, 1, file); 
            fseek(archive, i + BLOCKSIZE - file_size, SEEK_CUR);
            break;
        }
    }
    
    free(temp);
    fclose(file);

    return true;
}

// create a folder from tar archive
bool tar_create_folder(struct tar_header* header)
{
    if(strtol(header->size, NULL, OCTAL_BASE) > 0) // if size > 0 : not a folder
    {
        return false;
    }

    return mkdir(header->name, strtol(header->mode, NULL, OCTAL_BASE));
}

// generate a tar archive with given files 
void tar_generate_archive(FILE* archive, char* filenames[], int nb_files)
{
    for(int i = 0; i < nb_files; i++) 
    {
        FILE* file;
        
        if(!(file = fopen(filenames[i], "r")) )
        {
            fprintf(stderr, "Error : tar_generate_archive() : cannot open file %s\n", filenames[i]);
            fprintf(stderr, strerror(errno));

            return;
        }

        tar_add_file_to_archive(archive, file, filenames[i]);

        fclose(file);
    }

    tar_add_end_of_file(archive);
}

// add a single file into tar archive
bool tar_add_file_to_archive(FILE* archive, FILE* file, char* filename) 
{
    struct tar_header header = tar_fill_header(file, filename);

    if(tar_header_is_empty(&header)) 
    {
        return false;
    }

    int* temp = malloc(BLOCKSIZE);

    long int file_size = strtol(header.size, NULL, OCTAL_BASE);

    fwrite(&header, BLOCKSIZE, 1, archive);

    for (long int i = 0; i < file_size; i += BLOCKSIZE)
    {
        fread(temp, BLOCKSIZE, 1, file);
        fwrite(temp, BLOCKSIZE, 1, archive);            
    }
    
    free(temp);

    return true;
}

// create a tar header from file
struct tar_header tar_fill_header(FILE* file, char* filename)
{
    struct tar_header header;

    // mode
    int fd = fileno(file);
    struct stat file_stat;

    if(fstat(fd, &file_stat) != 0) 
    {
        printf("Error : \tar_fill_header() : error when reading file metadatas\n");
        return header;
    }

    // name
    strncpy(header.name, filename, 100);
    header.name[sizeof(header.name) - 1] = '\0';

    sprintf(header.mode, "%o", file_stat.st_mode);
    sprintf(header.owner, "%o", file_stat.st_uid);
    sprintf(header.group, "%o", file_stat.st_gid);
    sprintf(header.size, "%lo", file_stat.st_size);
    sprintf(header.mtime, "%lo", file_stat.st_mtime);

    memset(header.checksum, ' ', sizeof(header.checksum));

    header.type = '0';

    if(file_stat.st_size == 0) 
    {
        header.type = '5';
    } 

    unsigned int checksum = tar_calculate_checksum_header((char *) &header);

    sprintf(header.checksum, "%06o\0 ", checksum);

    return header;
}

// add 2 blocks of empty bytes at the end of the archive
void tar_add_end_of_file(FILE* archive) 
{
    char data[BLOCKSIZE];

    memset(data, 0, BLOCKSIZE);

    for(int i = 0; i < NUMBER_TRAILING_EMPTY_BLOCK; i++)
    {
        fwrite(data, BLOCKSIZE, 1, archive);
    }
}
