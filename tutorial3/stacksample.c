#include <stdio.h>
#include <stdlib.h>

/* Stack structure definition */
typedef char stackitem;

struct stack {
stackitem  d;
struct stack *next;
};

typedef  struct stack ELEMENT;
typedef  ELEMENT   *POINTER;


void push(POINTER *Top, stackitem a)
/* Put item a into the top of the stack */
     {
		POINTER temp;
		temp = malloc(sizeof(ELEMENT));
		temp->d = a;
		temp->next = *Top;
		*Top = temp;
		printf("Insert element %c\n", temp->d);
     }

void pop(POINTER *Top)
/* Remove the top item */
     {
		POINTER Top1 = *Top;
		if (Top != NULL)
		{
		  *Top = Top1->next;
		  printf("Remove element %c\n", Top1->d);
		  free(Top1);

		/*
		The way pop works is first Top1 = *Top is like currernt = Head;
		Then it moves the *Top to the next value, then it free the old Top;
		*/

		}
		else
		  printf("Empty stack.\n");
     }

void print_stack(POINTER Top)
/*Print the contents of the stack. Do not modify the stack in any way. */
	{
		printf("Start printing the stack ...\n");

		/*insert you code here */

		POINTER current  = Top;
		while(current != NULL){
			printf("%c\n", current->d);		//-> is like . but for pointers | can also use (*current).d
			current=current->next;
		}

	}

void delete_stack(POINTER *Top)
/* Delete the stack, i.e. remove all items from the stack */
	{
		printf("Start deleting the stack...\n");

		/*insert you code here */
		POINTER current = Top;
		while(*Top != NULL){		//check if there is anymore data inside (not just the data but also is there any more memory address inside this stack)
			pop(Top);
		}
	}

void push_string(POINTER *Top,char *string)
/* Push a string of characters into a stack. */
	{
		printf("Start inserting the string ...\n");

		/*insert you code here */
		int i = 0;
		while(string[i] != '\0'){		// for pointers it is NULL for string it is \0
			push(Top, string[i]);
			i++;
		}
	}

main()
	{

		POINTER top;
		top= (POINTER) NULL;
		stackitem A='A';
		stackitem B='B';
		char *C="12345";
		//printf("C is %s\n", C);
		push(&top,A);
		push(&top,B);
		print_stack(top);
		pop(&top);
		pop(&top);
		print_stack(top);
		push_string(&top,C);
		print_stack(top);
		delete_stack(&top);
		print_stack(top);

	}

