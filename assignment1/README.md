22170804 - Steven Wang

COMP2019 - System Programming



INSTRUCTIONS:

1. in terminal run
2. gcc -std=gnu89 -o mycopydir mycopydir.c
3. can make sure mycopydir have been created by doing ls
4. run code
./mycopydir \[directory1]\[directory2]
5. directory1 and directory2 must be DIFFERENT



LOGIC:

Most are explained inside the code (comments)



PSEUDOCODE:

main and copy\_dir:

Check if the ac is equal to 3 or not, if not then error

Check if the av\[1] is == av\[2] by comparing the string, if yes then error

Goes inside copy\_dir func:

&#x09;opens the source directory av\[1] and stores it inside the (the address)

&#x09;create a new directory which name comes from av\[2]



&#x09;while loop direntp = readdir(dir\_ptr) will keep reading one by one until there is no more items to be read inside that dir:

&#x09;if:

&#x09;	if it is "." or ".." it will continue and not copy

&#x09;allocates memory for both source and destination to save the full path of the directory or file

&#x09;after the memory is successfully created. print the dirsrc/direntp->d\_name into the fullpath\_src. Same with the dst

&#x09;

&#x09;check whether the src is a dir or a file:

&#x09;	if it's a directory, run the copydir again but with fullpath\_src and fullpath\_dst as the av\[1] and av\[2]

&#x09;	if it's not a dir, run the copy\_file



&#x09;then the system frees the memory that was allocated for that directory



after the loop is done, it close the dir (the directory which address was saved in dir\_ptr)



copy\_file:

open the file source, and the mode is read only, if it's not successful then it will be -1

create a new file, and the mode is copymode or 0644, copy mode here have rw-r--r--. If it's not successful then it will be -1



&#x09;while:

&#x09;	read input file and save it to buf as much as buffersize and then save it to n\_chars, if n\_chars > 0, then it will continue inside the loop

&#x09;	if:

&#x09;		writes the buf into the output file and check whether the outfile is as big as n\_chars or no.



&#x09;	once the output is == n\_chars it will exit the  n\_chars



&#x09;outside the loop it checks again if the finish of the loop is because of an error or normaly

&#x09;



&#x09;after that we close the file for input and output both files



oops:

prints the error s1 is the error message and s2 is the argument that most likely has the error

then exits



isadir:

creates a var called info that have a data type of stat



stat the path, if it can't stat it, then exit the program



if successful stat, check uusing S\_ISDIR(info.st\_mode) uusiing the mode we can  find out if  it is a directory



TEST:

* created a directory test with 3 txt files, 2 files have bytes inside and 1 file is empty. Works, copied to test2 (directory dst not created manually)
* same thing but now test2 have already been created the directory. Works, just added the files inside the directory (directory dst created manually)
* created a directory test that have another directory inside and a file inside that sub-directory. Works, copied everything (directory dst  not created manually)
* Same thing as number 3 but now the directory test2 is created manually, still works (directory dest created manually)
* Copied a directory that is in the parent directory, outside the directory of assignment1. Works.



LIMITATIONS:

No limitations that I know of other than the ones mentioned in the Instructions, but for copying path that is not inside the same directory as the file, then we need to provide the full path to reach that directory.

