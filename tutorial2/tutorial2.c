//Tutorial 2 - Steven Wang (22170804)

#include <stdio.h>
#include <stdlib.h>

//Number 3
enum weekDays{
	Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

//Number 4
typedef char DATA;
struct node
{
	DATA d;
	struct node *next;
};

int main(){
	//create head (no need malloc because empty)
	struct node *head= NULL;

	int i = 0;
	while(i<5){
		struct node *body= NULL;
		body = (struct node *)malloc(sizeof(struct node));

		printf("Enter the data to put inside the list (5 character), type 0 to exit\n");
		char c;
		scanf(" %c", &c);

		if (c=='0'){
			return 0;
		}

		body->d = c;
		body->next = head;
		head = body;

		i++;
	}
	return 0;
};
