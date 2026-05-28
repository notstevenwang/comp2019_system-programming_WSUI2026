/* waitdemo2.c - shows how parent gets child status
 */

#include	<stdio.h>
#include <signal.h>
#include <sys/wait.h>

#define	DELAY1	6
#define DELAY2	7

main()
{
	int  newpid1;
	void child_code(), parent_code(), sigChildHandler();

	printf("before: mypid is %d\n", getpid());

	signal(SIGCHLD, sigChildHandler);

	if ( (newpid1 = fork()) == -1 ){
		perror("fork c1");
		exit(1);
	}
	else if ( newpid1 == 0 ){
		child_code(DELAY1, 1);
	}
	// else if ((newpid2 = fork()) == -1){
	// 	perror("fork c2");
	// 	exit(1);
	// }
	// else if (newpid2 == 0){
	// 	child_code(DELAY2, 2);
	// }
	else
		parent_code();
}
/*
 * new process takes a nap and then exits
 */
void child_code(int delay, int childNum)
{
	printf("child %d is running (PID %d). Child will sleep for %d seconds\n", childNum, getpid(), delay);
	sleep(delay);
	printf("child done. about to exit\n");
	exit(childNum * 6);
}
/*
 * parent waits for child then prints a message
 */
void parent_code()
{	
	while(1){
		printf("waiting\n");
		sleep(1);
	}
}

void sigChildHandler(int signum){
	int wait_rv;		/* return value from wait() */
	int child_status;
	int high_8, low_7, bit_7;
	int i;

	wait_rv = wait(&child_status);
	printf("done waiting for %d. Wait returned: %d\n", wait_rv);

	high_8 = child_status >> 8;     /* 1111 1111 0000 0000 */
	low_7  = child_status & 0x7F;   /* 0000 0000 0111 1111 */
	bit_7  = child_status & 0x80;   /* 0000 0000 1000 0000 */

	printf("status: exit=%d, sig=%d, core=%d\n", high_8, low_7, bit_7);
	exit(0);
}