#ifndef _TAR
#define _TAR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define BLOCKSIZE 512


struct tar_header 
{
    char name[100]; 		// filename
    char mode[8];			// access mode
    char owner[8];			// proprietary id
    char group[8];			// group id
    char size[12];			// filesize
    char mtime[12];			// Last modification date
    char checksum[8];		
    char type;			    // File type		
    char linkname[100];		// link name
    char magic[6];
    char version[2];
    char uname[32];
    char gname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char pad[12];
};

void tar_list(FILE* file);

int tar_read_header(FILE* file, struct tar_header* header);
bool tar_header_is_empty(struct tar_header* header);
void print_full_header_info(struct tar_header* header);

#endif // _TAR