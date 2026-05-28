	/*
	 * C program to open file several times
	 */
	#include <stdio.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/stat.h>

	#define COPYMODE  0644

	main()
	{
	  int fd, fd1, fd2;
	  ssize_t nread;
	  char buffer[1024];

	  fd=open("data", O_RDONLY|O_CREAT, COPYMODE);  /* open file "data" for reading, create it if not exist */
	  printf("file descriptor is %d\n", fd);

	  fd1=open("data", O_RDONLY);  /* open file data for reading */
	  printf("file descriptor is %d\n", fd1);

	  fd2=open("data", O_RDONLY);  /* open file data for reading */
	  printf("file descriptor is %d\n", fd2);

	  /* close the file */
	  close(fd);
	  close(fd1);
	  close(fd2);
	}

