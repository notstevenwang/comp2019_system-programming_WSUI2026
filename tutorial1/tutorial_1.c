#include <stdio.h>

int main(){
	char name[50];
	int age = 0;

	printf("Enter your name:\n");
	scanf("%49s", name);
	while(age <= 0){
		printf("Enter your age:\n");
		scanf("%d", &age);
		if(age <=0)
			printf("Age shouldn't be lower than 1\n");
	}
	printf("Hello %s, right now you are %d years old\n", name, age);

	return 0;
}
