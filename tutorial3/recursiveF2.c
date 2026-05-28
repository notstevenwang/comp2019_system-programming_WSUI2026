#include <stdio.h>
#include <stdlib.h>

int n, i;

int count(int n){
    if(n == 0){
		return 0;
	}
	if(n == 1){
		return 1;
	}
	return count(n-1) + count(n-2);
}

int main(int argc, char *argv[]){
	n = atoi(argv[1]);              //atoi means ASCII to int
                                    //in C can't  int *agrv because command line are always received as strings by OS    

	while(i<n){
		printf("%d ", count(i));
		i++;
	}
}