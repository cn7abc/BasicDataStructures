// Jacob Rogers
// Array implementation of stacks.
//A program to test knowledge of stacks 3-14-17 | 8:20 PM | Cayman Islands :)

#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
	int *array;
	int size;
	int capacity;
}stack;

// Will create and return a stack.
stack *createStack(int capacity){
	stack *s = malloc(sizeof(stack));
	if (s==NULL)
		return NULL;
	// Malloc the array.
	s->array = malloc(sizeof(int) * capacity);
	if (s->array == NULL)
		return NULL;
	// Italize size to zero and capacity to the user defined capacity.
	s->size = 0;
	s->capacity = capacity;
	printf("Created stack with capacity of %d.\n", capacity);

	return s;
}

// Will push an element onto the top of the stack, or the next element (size) of the array.
void push(stack *s, int data){
	if(isFull(s)){
		printf("FULL STACK\n");
		return;
	}
	printf("Pushed: %d at s->array[%d]\n",data, s->size);
	// Size is always 1 above the index of the array, so put data into array[s->size] then do a POST-increment with ++.
	s->array[s->size++] = data;
}

// Will return the value of the element in the index (size - 1) of the array.
int pop(stack *s){
	if(isEmpty(s)){
		printf("EMPTY STACK\n");
		return;
	}
	// Do a pre-decrement of size, then return that index from the array.
	printf("Popped: %d at s->array[%d]\n", s->array[s->size - 1], s->size - 1);
	return s->array[--s->size];
}

// Will return 1 is the stack is empty, 0 otherwise.
int isEmpty(stack *s){
	if(s->size == 0 || s == NULL)
		return 1;
	else
		return 0;
}

// Will return 1 if the stack is fill, 0 otherwise.
int isFull(stack *s){
	if(s->size == s->capacity || s == NULL)
		return 1;
	else 
		return 0;
}

// Will return the value of the last element pushed into the stack.
int peek(stack *s){
	if(isEmpty(s)){// So if this returns a non-zero number, meaning it's true, then activate this if statment and return null.
		printf("EMPTY STACK\n");
		return 0;
	}

	printf("Peeked %d at s->array[%d]\n", s->array[s->size - 1], (s->size - 1));
	// Return the value of (size - 1) of the array, do not change size.
	return s->array[s->size - 1];
}

int main(void){
	int op = -2, terminate = 0, data = -1, output;
	stack *s;

	printf("Enter the capcity of the stack:\n");
	scanf("%d", &data);

	s = createStack(data);
	system("cls");

	while(!terminate){

		op = -2;
		printf("Choose an operation:\n -1 - quits the program\n 0 - pushes a data value\n 1 - pops an element\n 2 - peeks\n 3 - is empty?\n 4 - is full?\n 5 - return size\n");
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
				output = isFull(s);
				if(output == 1)
					printf("FULL\n");
				if(output == 0)
					printf("NOT FULL\n");
				break;
			case 5:
				system("cls");
				printf("size = %d\n",s->size);
				break;
			default:
				system("cls");
				printf("\nWrong number input.\n");
				break;
		}
	}

	
	return 0;
}

