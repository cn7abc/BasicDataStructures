// Jacob Rogers
// December-27-2017

// Linked list implementation of stacks.

#include <stdio.h>
#include <stdlib.h>

// Three typedefs.
typedef struct node{
	int data;
	struct node *next;
}node;

typedef struct linkedList{
	node *head;
}linkedList;

typedef struct stack{
	linkedList *list;
	int count;
}stack;

// Will create and return a linked list node.
node *CreateNode(int data){
	node *newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// Will create and return a stack.
stack *createStack(void){
	stack *s = calloc(1,sizeof(stack));
	if (s==NULL)
		return NULL;

	s->list = calloc(1,sizeof(linkedList));
	s->list->head = NULL;
	s->count = 0;
	return s;
}

// Will push a value into the head of the list.
void push(stack *s, int data){
	node *arrow;
	// Save the address of the current head.
	arrow = s->list->head;
	// Set the head of the list to be a new node with the data that is being pushed on.
	s->list->head = CreateNode(data);
	// Link this new node (new head) to the old head.
	s->list->head->next = arrow;
	// Update the count.
	s->count++;
	printf("Pushed %d onto the top of the stack.\n",data);
}

// Will pop a value off the top of the stack, eliminate the first node in the list. Will return its data value.
int pop(stack *s){
	node *arrow;
	int retval;
	if(isEmpty(s)){
		printf("EMPTY STACK\n");
		return;
	}
	// Save the address of the 2nd node in the list.
	arrow = s->list->head->next;
	// Get the data value from the head of the list (the node to be popped).
	retval = s->list->head->data;
	// Free the head of the list.
	free(s->list->head);
	// Reset the head of the list to the saved address.
	s->list->head = arrow;
	// Update the count.
	s->count--;

	printf("Popped %d from the top of the stack.\n", retval);
	return retval;
}

// Will return 1 if the stack is empty, 0 otherwise. NOTE: no isFull because nodes can be created dynamically. 
int isEmpty(stack *s){
	if(s == NULL || s->list->head == NULL)
		return 1;
	else
		return 0;
}

// Will return the data vlaue of the first node in the stack's list.
int peek(stack *s){
	if(isEmpty(s)){//so if this returns a non-zero number, meaning it's true, then activate this if statment and return null.
		printf("EMPTY STACK\n");
		return 0;
	}
	printf("Peeked %d ontop of the stack.\n", s->list->head->data);
	return s->list->head->data;
}

// Will count the stack nodes and determine if there are >= 5 nodes in the stack. Will return 1 if so, and 0 otherwise.
int fiveCheck()

int main(void){
	int op = -2, terminate = 0, data = -1, output;
	stack *s;


	s = createStack();
	system("cls");

	while(!terminate){

		op = -2;
		printf("Choose an operation:\n -1 - quits the program\n 0 - pushes a data value\n 1 - pops an element\n 2 - peeks\n 3 - is empty?\n 4 - return count\n");
		if(scanf("%d", &op) != 1){
			system("cls");
			printf("\nA non-numeric value was entered. Ending program to avoid crash.\n");
			exit(1);
		}

		switch(op){
			case -1: // TERMINATE
				system("cls");
				printf("\nProgram terminated.\n");
				terminate = 1;
				break;
			case 0:
				system("cls");
				printf("\nWhat is the data to be inserted: \n");
				scanf("%d", &data);
				push(s, data);
				break;
			case 1:
				system("cls");
				output = pop(s);
				//printf("output = %d\n", output);
				break;
			case 2:
				system("cls");
				output = peek(s);
				break;
			case 3:
				system("cls");
				output = isEmpty(s);
				if(output == 1)
					printf("EMPTY\n");
				if(output == 0)
					printf("NOT EMPTY\n");
				break;
			case 4:
				system("cls");
				printf("count = %d\n",s->count);
				break;
			default:
				system("cls");
				printf("\nWrong number input.\n");
				break;
		}
	}


	return 0;
}

