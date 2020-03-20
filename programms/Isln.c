//PLAKOLB Marcel
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

#define BUFFERSIZE 256

int main(int argc, char *argv[]) {
    if(argc>2){
        printf("You can only call lsln with one or less arguments!");
        return 0;
    }

    struct dirent *de;

    char path[BUFFERSIZE];

    strcpy(path, argc == 2 ? argv[1] : ".");
    strcat(path, "/");

    DIR *dr = opendir(path);

    if (dr == NULL)
    {
        printf("Directory does not exist");
        return 0;
    }

    struct stat sb;

    while ((de = readdir(dr)) != NULL){
        strcat(path, de->d_name);
        lstat(path, &sb);

        switch (sb.st_mode & S_IFMT) {
            case S_IFBLK:  printf("b");             break;
            case S_IFCHR:  printf("c");             break;
            case S_IFDIR:  printf("d ");            break;
            case S_IFIFO:  printf("f ");            break;
            case S_IFLNK:  printf("l ");            break;
            case S_IFREG:  printf("- ");            break;
            case S_IFSOCK: printf("s ");            break;
        }

        printf((sb.st_mode & S_IRUSR) ? "r" : "-");
        printf((sb.st_mode & S_IWUSR) ? "w" : "-");
        printf((sb.st_mode & S_IXUSR) ? "x" : "-");
        printf((sb.st_mode & S_IRGRP) ? "r" : "-");
        printf((sb.st_mode & S_IWGRP) ? "w" : "-");
        printf((sb.st_mode & S_IXGRP) ? "x" : "-");
        printf((sb.st_mode & S_IROTH) ? "r" : "-");
        printf((sb.st_mode & S_IWOTH) ? "w" : "-");
        printf((sb.st_mode & S_IXOTH) ? "x" : "-");

        printf("%5d ", sb.st_uid);
        printf("%5d ", sb.st_gid);
        printf("%9lld ", sb.st_size);
        char formatted_date[40];
        strftime( formatted_date, 40, "%Y-%m-%d-%H-%M", localtime(&sb.st_mtime));
        printf("%s ", formatted_date);
        printf("%s \n", de->d_name);
    }

    closedir(dr);
    return 0;
}
