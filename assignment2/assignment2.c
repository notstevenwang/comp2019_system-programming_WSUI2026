#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int thisChild1Code();
int thisChild2Code(char *argv[]);
int thisChild3Code(char *argv[]);
int thisParentCode();

int main(int argc, char *argv[]){
    
    int childPid1, childPid2, childPid3;

    if(argc != 4){
        printf("Argument doesn't match: %s sort-input sort-output update-file\n", argv[0]);
        exit(0);
    }

    pid_t pid1 = fork();
    childPid1 = pid1;
    if(pid1 == 0){
        thisChild1Code();
        exit(1);
    } else if(pid1 == -1){
        perror("fork");
    }


    thisParentCode(childPid1);

    pid_t pid2 = fork();
    childPid2 = pid2;
    if(pid2 == 0){
        thisChild2Code(argv);
        exit(2);
    } else if(pid2 == -1){
        perror("fork");
    }

    thisParentCode(childPid2);

    pid_t pid3 = fork();
    childPid3 = pid3;
    if(pid3 == 0){
        thisChild3Code(argv);
        exit(3);
    } else if(pid3 == -1){
        perror("fork");
    }

    thisParentCode(childPid3);

    return 0;
}

int thisChild1Code(){
    int nMarks  = 6;
    double marks[nMarks];
    double sum = 0;
    double min = 100000;
    double max = -10000;

    for(int i = 0; i <nMarks; i++){
        //scanf is asking for input  %lf is double
        printf("Enter the marks (0-100): \n");
        scanf("%lf", &marks[i]);

        ///sum up all of the input
        sum += marks[i];
        //finnd the min
        if(marks[i] < min){
            min = marks[i];
        }
        //find the max
        if(marks[i] > max){
            max = marks[i];
        }
    }
    //from the sum gte avg
    double avg = sum/nMarks;
    
    //print the results
    printf("Calculation is done\n");
    printf("The avg of this class is: %lf\n", avg);
    printf("The min is %lf and the max is %lf\n", min, max);
}

int thisChild2Code(char *argv[]){
    /*
    The -r means reverse oreder for sort
    */
    char* args[] = {"sort", "-r", argv[1], NULL};
    int fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd < 0){
        perror("open failure");
        exit(67);
    }
    /*
    Instead of printing to the screen now it will print to the file
    dup2(fd,1) => change from stdout(screen) to fd
    */
    dup2(fd, 1);
    close(fd);
    /*
    execvp(the program name we want to run (in thiss case it is sort),
    and the second part is the part that we actually want)

    ANALOGGY:
    sort is phone number, args is the message we want to tell to sort
    such as Hello is this sort? I want to sort in -r...
    */
    execvp("sort",args);
    perror("exec fail");
    exit(1);
}

int thisChild3Code(char *argv[]){
    FILE *fp = fopen(argv[3], "r");
    if(fp < 0){
        perror("fail to open");
        exit(67);
    }

    /*
    0 means the offset
    */
    fseek(fp, 0, SEEK_END);
    /*
    ftell says "i am in character nuumber... 555 example"
    */
    long size = ftell(fp);
    /*
    SEEK_SEET means the start location
    */
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(size + 1);

    /*
    saves the fp file as big as size and 1 character is 1 byte and saves  it into buuffer
    */
    fread(buffer, 1, size, fp);

    /*
    The \0 helps like it is a period, it tells the string ends here
    */
    buffer[size] = '\0';
    fclose(fp);

    /*
    After closing the file that twe can only read, we open again and now we can writee
    */
    fp = fopen(argv[3], "w");
    if(fp < 0){
        perror("fail to open");
        exit(67);
    }
    fprintf(fp, "This is the updated ver.\n");

    int i = 0;
    while(i<size){
        /*
        strncmp compares n characcters (in this case 5)
        so for instance:

        This is test table

        It will check T first and then checks 5 from T which means "This "
        checks if it is table or not, if not then move to next h which is "his i" 
        checks again if it is table. and then moving on to next char i so "is is"
        and so on until EOF
        */
        if(strncmp(buffer+ i, "table", 5) == 0) {
            fprintf(fp, "desk");
            i += 5;
        } 
        else {
            fputc(buffer[i], fp);
            i++;
        }
    }
    fclose(fp);
    free(buffer);
}

int thisParentCode(int child){
    int status;
    wait(&status);
    /*
    WEXITSTATIS = from Claude
    it extracts the actual exit code from status 
    */
    printf("Child %d exited with status: %d\n", child, WEXITSTATUS(status));
}