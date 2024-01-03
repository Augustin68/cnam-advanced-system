#ifndef _TAR
#define _TAR

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "typedef.h"

#define BLOCKSIZE 512
#define OCTAL_BASE 8
#define NUMBER_TRAILING_EMPTY_BLOCK 2

bool tar_extract_file(FILE* archive, struct tar_header* header);
int tar_read_header(FILE* file, struct tar_header* header);
bool tar_header_is_empty(struct tar_header* header);
void print_full_header_info(struct tar_header* header);
bool tar_header_is_empty(struct tar_header* header);
bool tar_create_folder(struct tar_header* header);
void tar_extract_archive(FILE* file);
void tar_list(FILE* file);
struct tar_header tar_fill_header(FILE* file, char* filename);
void tar_generate_archive(FILE* archive, char** filenames, int nb_files);
bool tar_add_file_to_archive(FILE* archive, FILE* file, char* filename);
void tar_add_end_of_file(FILE* archive);
unsigned int tar_calculate_checksum_header(char* header_string);
char* tar_header_to_string(struct tar_header* header);

#endif // _TAR