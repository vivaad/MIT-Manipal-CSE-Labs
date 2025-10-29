#include <unistd.h>

// Convert integer to decimal string (positive only)
void itoa(int n, char *buf) {
    int i = 0;
    if (n == 0) {
        buf[i++] = '0';
    } else {
        int tmp = n;
        while (tmp > 0) {
            tmp /= 10;
            i++;
        }
        buf[i] = '\0';
        while (n > 0) {
            buf[--i] = '0' + (n % 10);
            n /= 10;
        }
    }
}

// Write a string
void print_str(const char *s) {
    int len = 0;
    while (s[len]) len++;
    write(1, s, len);
}

// Write a single character
void print_char(char c) {
    write(1, &c, 1);
}

int main() {
    int num = 12345;
    char c = 'A';
    char buf[20];

    itoa(num, buf);
    print_str(buf);
    print_char('\n');

    print_char(c);
    print_char('\n');
    return 0;
}

