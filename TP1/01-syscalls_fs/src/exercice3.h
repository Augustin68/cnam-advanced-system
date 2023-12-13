#ifndef EXERCICE_3
#define EXERCICE_3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

// private void printFileInfo(const char *filename);

int isDirectory(const char *path);

void ls(char* src);

void printFileInfo(const char *filename);

#endif // EXERCICE_3