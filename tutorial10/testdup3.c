#define _GNU_SOURCE           // needed for dup3 on Linux
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    dup3(fd, STDOUT_FILENO, O_CLOEXEC);
    close(fd);

    write(STDOUT_FILENO, "dup3\n", 5);

    return 0;
}