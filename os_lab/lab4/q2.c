#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>

#define LINES_PER_PAGE 20
#define BUF_SIZE 1024

// Wait for a single key press (disable canonical mode)
void wait_key() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int main(int argc, char **argv) {
    char buf[BUF_SIZE];
    int fd, i, n, lines = 0;

    if (argc < 2) return 1;

    for (i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0) continue; // skip on error
        while ((n = read(fd, buf, BUF_SIZE)) > 0) {
            for (int j = 0; j < n; j++) {
                if (write(STDOUT_FILENO, &buf[j], 1) != 1) {
                    close(fd);
                    return 1;
                }
                if (buf[j] == '\n') {
                    lines++;
                    if (lines == LINES_PER_PAGE) {
                        wait_key();
                        lines = 0;
                    }
                }
            }
        }
        close(fd);
    }
    return 0;
}

