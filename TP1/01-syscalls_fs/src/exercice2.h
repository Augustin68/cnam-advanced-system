#ifndef EXERCICE_2
#define EXERCICE_2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<getopt.h>
#include <unistd.h>  /* Many POSIX functions (but not all, by a large margin) */
#include <fcntl.h>   /* open(), creat() - and fcntl() */

#define BUFFER_SIZE 1024

void printReverse(const char* src);

#endif // EXERCICE_2