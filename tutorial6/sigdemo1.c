/* sigdemo1.c - shows how a signal handler works.
 *            - run this and press Ctrl-C a few times
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int count = 0;
int max_count = 0;  

void f(int signum);

int main(int argc, char *argv[])
{
    int i;

    if (argc != 2) {
        fprintf(stderr, "Error:please prove the max ^C to exit%s \n", argv[0]);
        exit(1);
    }

    max_count = atoi(argv[1]);
    if (max_count <= 0) {
        fprintf(stderr, "Error: %s is not positive\n", argv[1]);
        exit(1);
    }

    signal(SIGINT, f);

    printf("Press Ctrl-C %d time(s) to exit.\n", max_count);

    for (i = 0; i < 30; i++) {
        printf("hello\n");
        sleep(1);
    }

    return 0;
}

void f(int signum)  
{
    int i;
    count++;

    printf("OUCH!");
    for (i = 1; i < count; i++) {
        printf("!");
    }
    printf("\n");

    if (count >= max_count) {
        printf("You pressed Ctrl-C %d time(s). Exiting!\n", count);
        exit(0);
    }
}