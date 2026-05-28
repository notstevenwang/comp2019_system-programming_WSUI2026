#include <stdio.h>

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

int main(){
	printf("Please input the number of times this function is called:\n");
	scanf("%d", &n);

	while(i<n){
		printf("%d ", count(i));
		i++;
	}
}