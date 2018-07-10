// Jacob Rogers
// December-27-2017
// Queues array implementation.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct queue{
	int *array;
	int front, rear, capacity, size;
}queue;


// A function to create a queue, will take in the desired size of the full capacity of the queue. Will return the address of the queue.
queue *createQueue(int capacity){
	queue *q = malloc(sizeof(queue));
	// Also malloc the array within the queue.
	q->array = malloc(sizeof(int) * capacity);

	// Intialize front to index 0 and rear to capacity - 1. Will circularly loop around due to modulo insertion in equeue. (default positions).
	q->front = 0;
	q->rear = capacity - 1;

	// Initialize the capcity to the user defined capacity, and the size to 0.
	q->capacity = capacity;
	q->size = 0;

	return q;
}

// A function to check if the queue is empty. Will return 1 if the queue is empty, 0 otherwise.
int isEmpty(queue *q){
	// If size == 0.
	if(q->size == 0)
		return 1;
	else
		return 0;
}

// A function to check if the queue is full. Will return 1 if so, else 0.
int isFull(queue *q){
	// If the size == the capcity it's full.
	if(q->size >= q->capacity)
		return 1;
	else
		return 0;
}

// A function to add a number to the queue. All items are added to the REAR of the queue.
void enqueue(queue *q, int data){
	// Check if the queue is full.
	if(isFull(q)){
		printf("The queue is already full.\n");
		return;
	}

	// Update the rear int. Using a mod by the capacity of the array to allow for circular enqueueing into the array. D':
	// Simply moding by capacity makes it circualar. Know properties of modulo divion.
	// https://www.youtube.com/watch?v=okr-XE8yTO8
	q->rear = (q->rear + 1) % q->capacity;
	// Set the rear index to the data being enqueued.
	q->array[q->rear] = data;
	printf("Enqueued %d at q->array[%d]\n", data, q->rear);
	// Increase size.
	q->size++;
	
	return;
}

// A function to dequeue an element from the queue. All items are dequeued from the front of the queue.
int dequeue(queue *q){
	int retval;
	// Check if the queue if empty.
	if(isEmpty(q)){
		printf("The queue is empty.\n");
		return INT_MIN;
	}

	// Get the retval.
	retval = q->array[q->front];
	printf("Dequeued %d at q->array[%d]\n", retval, q->front);

	// Move front up (+1), circualarly (% capacity).
	q->front = (q->front + 1) % q->capacity;

	// Decrease size.
	q->size--;

	return retval;
}

// A function to return the value of the front of the queue, but not remove it from the queue.
int peek(queue *q){
	int retval;

	// Check if is empty.
	if(isEmpty(q)){
		printf("The queue is empty.\n");
		return INT_MIN;
	}

	// Get the retval.
	retval = q->array[q->front];
	printf("Peeked %d at q->array[%d]\n", retval, q->front);

	return retval;
}


int main(void){

	int op = -2, terminate = 0, data = -1, output;
	queue *q;

	printf("Enter the capcity of the queue:\n");
	scanf("%d", &data);

	q = createQueue(data);
	system("cls");

	while(!terminate){

		op = -2;
		printf("Choose an operation:\n -1 - quits the program\n 0 - enqueues a data value\n 1 - dequques an element\n 2 - peeks\n 3 - is empty?\n 4 - is full?\n");
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
				enqueue(q, data);
				break;
			case 1:
				system("cls");
				output = dequeue(q);
				//printf("output = %d\n", output);
				break;
			case 2:
				system("cls");
				output = peek(q);
				//printf("output = %d\n", output);
				break;
			case 3:
				system("cls");
				output = isEmpty(q);
				if(output == 1)
					printf("EMPTY\n");
				if(output == 0)
					printf("NOT EMPTY\n");
				break;
			case 4:
				system("cls");
				output = isFull(q);
				if(output == 1)
					printf("FULL\n");
				if(output == 0)
					printf("NOT FULL\n");
				break;
			default:
				system("cls");
				printf("\nWrong number input.\n");
				break;
		}
	}

	return 0;
}

