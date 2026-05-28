#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINES 256
#define MAX_LINE_LEN 1024

int main(){
    char *lines[MAX_LINES];
    int count = 0;
    char buf[MAX_LINE_LEN];

    //read lines from stdin then store to array
    printf("Please type in a line (Ctrl+D when done): \n");
    while(count < MAX_LINES && fgets(buf, sizeof buf, stdin) != NULL){
        lines[count] = strdup(buf);          /* heap-copy each line */
        if (!lines[count]) { perror("strdup"); exit(EXIT_FAILURE); }
        count++;
    }

    //check if there is something inputed or not
    if (count == 0) {
        fprintf(stderr, "No input lines.\n");
        return EXIT_FAILURE;
    }

    //create 2 pipes for input and output
    int pipe_in[2], pipe_out[2];
 
    if (pipe(pipe_in)  == -1) { 
        perror("pipe (in)");  exit(EXIT_FAILURE); 
    }
    if (pipe(pipe_out) == -1) {
        perror("pipe (out)"); exit(EXIT_FAILURE);
    }

    //create child to exec sort 
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }
 
    if (pid == 0) {
        if (dup2(pipe_in[0], STDIN_FILENO)  == -1) { 
            perror("dup2 stdin");  exit(EXIT_FAILURE); 
        }
        if (dup2(pipe_out[1], STDOUT_FILENO) == -1) {
            perror("dup2 stdout"); exit(EXIT_FAILURE); 
        }
        close(pipe_in[0]);  close(pipe_in[1]);
        close(pipe_out[0]); close(pipe_out[1]);
        
        printf("This is from the child running sort, pid: %d\n", getpid());
        execlp("sort", "sort", (char *)NULL);
        
        perror("execlp sort");
        exit(EXIT_FAILURE);
    }

    close(pipe_in[0]);   /* parent doesn't read from pipe_in  */
    close(pipe_out[1]);  /* parent doesn't write to pipe_out  */

    for (int i = 0; i < count; i++) {
        printf("This comes from the parent, the parent id: %d\n", getpid());
        if (write(pipe_in[1], lines[i], strlen(lines[i])) == -1) {
            perror("write to sort");
            break;
        }
        free(lines[i]);     /* free the original copy */
        lines[i] = NULL;
    }
    close(pipe_in[1]);

    FILE *sort_out = fdopen(pipe_out[0], "r");
    if (!sort_out) {
        perror("fdopen"); exit(EXIT_FAILURE); 
    }

    count = 0;
    while (count < MAX_LINES && fgets(buf, sizeof buf, sort_out) != NULL) {
        printf("This comes from the parent getting sort, pid: %d\n", getpid());
        lines[count] = strdup(buf);
        if (!lines[count]) { perror("strdup"); exit(EXIT_FAILURE); }
        count++;
    }
    fclose(sort_out);

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        fprintf(stderr, "sort exited with status %d\n", WEXITSTATUS(status));
 
    printf("\n Sorted Output \n");
    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
 
    return EXIT_SUCCESS;
}