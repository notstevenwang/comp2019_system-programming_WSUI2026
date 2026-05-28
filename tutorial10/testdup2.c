#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int newfd = dup2(fd, STDOUT_FILENO);
     printf("fd = %d\n", STDOUT_FILENO);
    printf("duplicated fd = %d\n", newfd);

    close(fd);                
    printf("dup2\n");

    return 0;
}