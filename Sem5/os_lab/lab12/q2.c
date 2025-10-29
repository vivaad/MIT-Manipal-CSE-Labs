#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files_in_directory(const char *dir_path) {
    DIR *dir = opendir(dir_path);  // Open the directory
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    struct dirent *entry;  // Directory entry structure
    struct stat file_stat; // Stat structure for file properties
    char file_path[1024];  // Buffer to store the file path

    while ((entry = readdir(dir)) != NULL) {
        // Skip the '.' and '..' directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Create the full path of the file
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

        // Get file information
        if (stat(file_path, &file_stat) == 0) {
            // Print the file name
            printf("%s\n", file_path);

            // If the entry is a directory, recursively call this function
            if (S_ISDIR(file_stat.st_mode)) {
                list_files_in_directory(file_path);  // Recursive call
            }
        } else {
            perror("stat error");
        }
    }

    closedir(dir);  // Close the directory after processing
}

int main() {
    // Get the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Listing all files in directory and its subdirectories:\n");
        list_files_in_directory(cwd);  // Start from the current directory
    } else {
        perror("getcwd error");
    }

    return 0;
}

