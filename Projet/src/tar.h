#ifndef _TAR
#define _TAR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "typedef.h"

#define BLOCKSIZE 512

bool tar_extract_file(FILE* archive, struct tar_header* header);
int tar_read_header(FILE* file, struct tar_header* header);
void print_full_header_info(struct tar_header* header);
bool tar_header_is_empty(struct tar_header* header);
bool tar_create_folder(struct tar_header* header);
void tar_extract_archive(FILE* file);
void tar_list(FILE* file);

#endif // _TAR