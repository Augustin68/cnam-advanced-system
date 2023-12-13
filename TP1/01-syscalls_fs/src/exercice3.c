#include "exercice3.h"

void ls(char* src) {
    if(src == NULL) {
        printf("ls: missing operand\n");
        return;
    }

    if(!isDirectory(src)) {
        printf("'%s': Is a file. It should be a directory\n", src);
        exit(EISDIR);
        return;
    }

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (src)) != NULL) {
        // printf("ls src : %s\n", src);
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf ("d_name : %s\n", ent->d_name);
            const char* path = strcat(*src, ent->d_name);
            if(isDirectory(path)) {
                ls(path);
            } else {
                printFileInfo(path);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("opendir");
        exit(ENOENT);
    }
   
}

void printFileInfo(const char *filename) {
    struct stat file_stat;
    // printf("filename : %s", filename);
    if (stat(filename, &file_stat) == -1) {
        perror("stattt");
        return;
    }

    // Permissions
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    // Owner and Group
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);
    if (pwd != NULL && grp != NULL) {
        printf(" %s : %s", pwd->pw_name, grp->gr_name);
    }

    // Size
    printf(" – %ld – ", (long)file_stat.st_size);

    // Last Modification Date
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%d%m%y @ %Hh%M", tm_info);
    printf("%s\n", time_str);
}

int isDirectory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}