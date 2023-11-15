#ifndef _TAR
#define _TAR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
};


int tar_read_header(FILE* file, struct tar_header* header);
void print_full_header_info(struct tar_header* header);

#endif // _TAR