/** ls1.c
 **   purpose  list contents of directory or directories
 **   action   if no args, use .  else list files in args
 **/
#include	<stdio.h>
#include	<sys/types.h>
#include	<dirent.h>
#include 	<sys/stat.h>
#include 	<limits.h>

void do_ls(char []);

main(int ac, char *av[])
{
	if ( ac == 1 )
		do_ls( "." );
	else
		while ( --ac ){
			printf("%s:\n", *++av );
			do_ls( *av );
		}
}

void do_ls( char dirname[] )
/*
 *	list files in directory called dirname
 */
{
	DIR		*dir_ptr;				/* the directory */
	struct dirent	*direntp;		/* each entry	 */
	struct stat info;
	char filepath[PATH_MAX];		/*the maximum of path size in linux*/

	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
		fprintf(stderr,"ls1: cannot open %s\n", dirname);
	else
	{
		while ( ( direntp = readdir( dir_ptr ) ) != NULL ){
			snprintf(filepath, sizeof(filepath), "%s/%s", dirname, direntp->d_name);
		
			if (stat(filepath, &info) == -1){
				perror(filepath);
			}
			else {
				printf("%s\t", direntp->d_name );
				printf("inode: %lu\t", (unsigned long)info.st_ino);
				printf("   mode: %o\n", info.st_mode);         /* type + mode */
				printf("  links: %d\n", info.st_nlink);        /* # links     */
				printf("   user: %d\n", info.st_uid);          /* user id     */
				printf("  group: %d\n", info.st_gid);          /* group id    */
				printf("   size: %d\n", info.st_size);         /* file size   */
				printf("modtime: %d\n", info.st_mtime);        /* modified    */
				printf("\n");
			}
		}
		closedir(dir_ptr);
	}
}
