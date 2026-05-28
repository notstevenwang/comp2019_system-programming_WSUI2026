#include <stdiolib.h>


int main(){
    int fd, fd1, fd2, fd3;
    char buf[50];
    size_t n;
    
    fd = open("Tutorial4_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    //open ("file name", flags, mode (mode is optional can use, can not));
    // O_TRUNC - to delete the content of the file without deleting the file
    // O_CREAT - to create the file if it haven't been created

    write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890\n", 63);
    close(fd);

    fd1 = open("Tutorial4_output.txt", O_RDONLY);
    fd2 = open("Tutroail4_output.txt", O_WRONLY);
    fd3 = open("Tutorial4_output.txt", O_RDONLY);

    n = read(fd1, buf, 50);
    buf[n]='\0';
    printf("%s")
}
