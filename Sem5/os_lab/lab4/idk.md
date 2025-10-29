#include <fcntl.h>    // open
#include <unistd.h>   // read, write, close
#include <string.h>   // strstr
#include <stdlib.h>   // exit
#include <errno.h>

#define BUF_SIZE 1024

void print_error(const char *msg) {
    write(STDERR_FILENO, msg, strlen(msg));
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_error("Usage: ./program filename word\n");
        exit(1);
    }

    const char *filename = argv[1];
    const char *word = argv[2];

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        print_error("Error opening file\n");
        exit(1);
    }

    char buf[BUF_SIZE];
    ssize_t bytes_read;
    char line[BUF_SIZE * 4]; // buffer to hold a line (can span multiple reads)
    int line_len = 0;
    bytes_read = read(fd, buf, BUF_SIZE);
    
	while (bytes_read > 0) {
		bytes_read = read(fd, buf, BUF_SIZE); 
        for (int i = 0; i < bytes_read; i++) {
            line[line_len++] = buf[i];

            if (buf[i] == '\n') {
                line[line_len] = '\0'; // null terminate the line

                // Check if line contains the word
                if (strstr(line, word) != NULL) {
                    write(STDOUT_FILENO, line, line_len);
                }
                line_len = 0; // reset for next line
            }
        }
    }

    // Check if last line doesn't end with newline but contains word
    if (line_len > 0) {
        line[line_len] = '\0';
        if (strstr(line, word) != NULL) {
            write(STDOUT_FILENO, line, line_len);
            write(STDOUT_FILENO, "\n", 1); // add newline if missing
        }
    }

    if (bytes_read == -1) {
        print_error("Error reading file\n");
        close(fd);
        exit(1);
    }

    close(fd);
    return 0;
}
