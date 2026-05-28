/** mycopydir.c - copies everything (files and sub-directories) from dir1 to dir2
 ** dir1 and dir2 are from the command line arguments
 ** ------------------------------------------------------------
 *
 *
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include    <unistd.h>
#include	<string.h>
#include	<errno.h>
#include	<fcntl.h>

#define BUFFERSIZE      4096
#define COPYMODE        0644
#define	FILE_MODE	    S_IRWXU

void oops(char *, char *);
int isadir(char *);
void copy_file( char *, char * );
void copy_dir(char *, char *);

int main(int ac, char *av[])
{

    /*insert you code here*/
	
	/*
	check if there is 2 arguments when calling this file
	./mycopydir -> 0
	dir1 		-> 1
	dir2		-> 2
	and also checks if dir1 and dir2 name is same or not
	*/
	if (ac != 3){
		oops("Not enough arguments", av[0]);
	} 

	if(strcmp(av[1], av[2]) == 0){
		oops("File name is the same", av[2]);
	}

	/*
	starts the copy_dir function
	*/
	copy_dir( av[1], av[2] );
	return 0;

}


void copy_dir( char dir_src[] , char dir_dst[] )
/*
 *	copy files and sub_directories from dir_src to dis_dst
 */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */
	char   *fullpath_src, *fullpath_dst;

	/*insert you code here*/

	/*
	opens the directory and then store it inside dir_ptr
	*/
	dir_ptr = opendir(dir_src);

	if(dir_ptr == NULL){
	/*
	if the openning of the directory is successful, it will change dir_ptr  to the memory address of the openned dir
	if not, then it will keep the dir_ptr as NULL
	*/
		oops("Directory can't be openned", dir_src);
	}

	if(mkdir(dir_dst, FILE_MODE)  == -1 && errno != EEXIST){		
	/*
	check if the mkdir is successful (if successful == 0 if not -1)
	also check if the error -1 is caused by the directory existing or other
	if already exist then continue, but if the error is other than because the direcotory already exist then  exit
	*/

		oops("Directory can't be created", dir_dst);

	}

	while((direntp = readdir(dir_ptr)) != NULL){
		/*
		will keep checking the direntry until there's no more aka it reaches the end or NULL
		*/
		if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0){
			/*
			Checker so if it is "." current or ".." parent directory, it will just continue and not do anythhing.
			*/
			continue;
		}
		/*
		allocate memory for the path of the cource and the destination
		*/
		fullpath_src = malloc(strlen(dir_src) + 1 +strlen(direntp->d_name) + 1);
		sprintf(fullpath_src, "%s/%s", dir_src, direntp->d_name);

		fullpath_dst = malloc(strlen(dir_dst) + 1 + strlen(direntp->d_name) + 1);
		sprintf(fullpath_dst, "%s/%s", dir_dst, direntp->d_name);
		
		/*
		if it is a directory, it will run copy_dir again, but now with the full path
		if it is not, then it will run copy_file with the fuull path of ssrc and dst
		*/
		if(isadir(fullpath_src)){
			copy_dir(fullpath_src, fullpath_dst);
		} else {
			copy_file(fullpath_src, fullpath_dst);
		}
		/*
		Since malloc is used, need to free the memory to prvent memory leak
		*/
		free(fullpath_dst);
		free(fullpath_src);
	}
	closedir(dir_ptr);
}

void copy_file( char *file_src, char *file_dst )
/*
 *copy file from file_src to file_dst
 */
{
	int     in_fd, out_fd, n_chars;
    char    buf[BUFFERSIZE];

	/* insert your code here */

	/*
	if opening or creating a file failed, it will return -1
	*/
	if((in_fd  = open(file_src, O_RDONLY)) == -1){
		oops("Can't open file", file_src);
	}
	if((out_fd = creat(file_dst, COPYMODE)) == -1){
		oops("Can't create file", file_dst);
	}

	/*
	this while condition will read the input file and then store it inside buf as big as buffersize
	then it will store the total of buf inside of n_chars and use n_chars as the loopp condition
	if the condition is >0 that means it has succefully read bytes of the file inside the file
	if the condition is =0 that means it has reach the end
	and if the condition is =-1 that means there was aan error
	*/
	while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0){
		/*
		this if will check if the out file that is being wrritten to the out_fd is as big as n_chars
		what will be innside the out_fd is the buf aka the characterss that have been read fro in_fd
		
		the size of the write can be <n_chars depending on the problem, could be because the memory is full or etc.
		*/
		if(write(out_fd, buf, n_chars) !=  n_chars){
			oops("Write error to ", file_dst);
		}
	}
	/*
	at the end of the loop, when the loop is done, it checks whether the loop stops with an error or normallyy
	normally it would be n_chars == some int indicating how many char or bytes are inside then after the loop
	if it was normal, it will be 0 (end of file)
	if it wasn't normal, it will be -1
	*/
	if(n_chars == -1){
		oops("Read error from ", file_dst);
	}

	if ( close(in_fd) == -1 || close(out_fd) == -1 )
        oops("Error closing files","");
}

void oops(char *s1, char *s2)
/*
 *Output the error message and exit
 */

{
        /* insert your code here*/
		fprintf(stderr,"Error: %s %s\n", s1, s2);	
        // perror(s2);
        exit(1);
}



int isadir(char *str)
/*
 * boolean: tells if arg names a directory
 */

{
	struct stat info; //creates a variable name info that has plenty of data type (all of the data type that we get from stat)

	/*insert you code here*/
	
	//stat(source, destination) str is the source
	if(stat(str, &info) == -1){
		oops("Can't stat", str);
	}

	return S_ISDIR(info.st_mode); //checks st_mode if it is a directory or not S_ISDIR is a directory
}