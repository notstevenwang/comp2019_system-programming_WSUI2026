#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("original fd = %d\n", fd);

    int newfd = dup(fd);
    printf("duplicated fd = %d\n", newfd);

    write(newfd, "Hello from dup!\n", 16);

    close(fd);
    close(newfd);
    return 0;
}