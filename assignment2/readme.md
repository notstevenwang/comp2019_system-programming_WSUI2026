Steven Wang - 22170804



\* How to compile and run

1\. First run gcc -o assignment2 assignment2.c 

2\. tthen run ./assginment2 sort-test.txt sorted.txt update-test.txt



\* Pseudo

check if the 3 files are given when running (arguments)

create a var to hold pid 1 2 3 of the child

if not then error, print the error



create child 1

save child 1 pid to new pid

if child 1 pid == 0 then:

    child 1 asks for input (6)

    child 1 sums the inputs

    child 1 compare to find min and max

    child 1 prints

else error for child 1

parent prints child pid and exist status



creaete child 2

save child 2 pid to new pid

if child 2 pid == 0 then:

    child 2 opens the file

    child 2 duplicate and tells the sys to print into the fd or file (redirecting)

    child 2 calls execvp and calls sort with -r (reverse order)

else error for child 2

parent prints child pid and exist status



create child 3

save child 3 pid to new pid

if child 3 pid == 0 then

    child 3 reads the 3 argument

    child 3 finds the file size  using fseek and ftelll **(Claude help)**

    child 3 reads entire file into buffer

    child 3 close file

    child 3 opens file again this time for writing or edit

    child 3 scans buffer character by character

    &#x09;if table is found  write desk then skip 5 chars

    &#x09;else write the file as it  is

    child 3 close file free buff

else error for child 3

parent prints child pid and exist status



parent  waits for child to finish

inside parent func it will prints the child pid and the child exit status



\* Test run output
./assignment2 sort-test.txt sorted.txt update-test.txt 
Enter the marks (0-100): 
70
Enter the marks (0-100): 
67
Enter the marks (0-100): 
80
Enter the marks (0-100): 
70
Enter the marks (0-100): 
80
Enter the marks (0-100): 
90
Calculation is done
The avg of this class is: 76.166667
The min is 67.000000 and the max is 90.000000
Child 2304 exited with status: 1
Child 2305 exited with status: 0
Child 2306 exited with status: 3

\* Limitation

1\. if user input a letter it will break

2\. if execvp fails, no details why error

3\. case sensitive (only  replaces table, if there's TABLE Table etc wont be replaced)

