//Tutorial 2 - Steven Wang (22170804)

#include <stdio.h>
#include <stdlib.h>

typedef char DATA;
struct node
{
	DATA d;
	struct node *next;
};

void printList(struct node *head){
    struct node *temp = head;
    while(temp != NULL){
        printf(" %c", temp->d);
        temp = temp->next;
    }
    printf("\n");
}

void reverseList(struct node *head){
    struct node *prev = NULL;
    struct node *curr = head;
    struct node *next = NULL;

    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
}

int main(){
	//create head (no need malloc because empty)
	struct node *head= NULL;
    struct node *tail= NULL;

	for (int i =0; i<10; i++){
		struct node *body= NULL;
		body = (struct node *)malloc(sizeof(struct node));

		printf("Enter the data to put inside the list (10 character)\n");
		char c;
		scanf(" %c", &c);

        body->d = c;
        
        if(tail == NULL){
            head = body;
            tail = body;
        } else  {
            tail->next = body;
            tail = body;
        }
	}

    printList(head);

    reverseList(head);

    printList(tail);

	return 0;
};
