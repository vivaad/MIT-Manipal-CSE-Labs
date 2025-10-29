#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(const char *path, struct stat *file_stat, const char *file_name) {
    // Print file permissions
    printf( (S_ISDIR(file_stat->st_mode)) ? "d" : "-");
    printf( (file_stat->st_mode & S_IRUSR) ? "r" : "-");
    printf( (file_stat->st_mode & S_IWUSR) ? "w" : "-");
    printf( (file_stat->st_mode & S_IXUSR) ? "x" : "-");
    printf( (file_stat->st_mode & S_IRGRP) ? "r" : "-");
    printf( (file_stat->st_mode & S_IWGRP) ? "w" : "-");
    printf( (file_stat->st_mode & S_IXGRP) ? "x" : "-");
    printf( (file_stat->st_mode & S_IROTH) ? "r" : "-");
    printf( (file_stat->st_mode & S_IWOTH) ? "w" : "-");
    printf( (file_stat->st_mode & S_IXOTH) ? "x" : "-");
    printf("  ");

    // Print number of links
    printf("%ld  ", file_stat->st_nlink);

    // Print file owner and group
    struct passwd *owner = getpwuid(file_stat->st_uid);
    struct group *grp = getgrgid(file_stat->st_gid);
    printf("%s  %s  ", owner ? owner->pw_name : "Unknown", grp ? grp->gr_name : "Unknown");

    // Print file size
    printf("%ld  ", file_stat->st_size);

    // Print last modification time
    char time_str[256];
    struct tm *time_info = localtime(&file_stat->st_mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", time_info);
    printf("%s  ", time_str);

    // Print file name
    printf("%s\n", file_name);
}

void list_files_in_directory(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;
    char file_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        // Skip the '.' and '..' directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
        if (stat(file_path, &file_stat) == 0) {
            print_file_info(file_path, &file_stat, entry->d_name);
        } else {
            perror("stat error");
        }
    }

    closedir(dir);
}

int main() {
    // Get current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Listing files in directory: %s\n", cwd);
        list_files_in_directory(cwd);
    } else {
        perror("getcwd error");
    }
    return 0;
}

