// Jacob Rogers
// December-27-2017

// Queues linked list implementation.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Three typedefs.
typedef struct node{
	int data;
	struct node *next;
}node;

typedef struct LinkedList{
	node *head;
	node *tail;
}LinkedList;

typedef struct queue{
	LinkedList *list;
	int count;
}queue;

node *CreateNode(int data);
queue *createQueue(void);
int isEmpty(queue *q);
void enqueue(queue *q, int data);
int dequeue(queue *q);
int peek(queue *q);


// Will create and return a new linked list node.
node *CreateNode(int data){
	node *newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// Will create and return a queue.
queue *createQueue(void){
	queue *q = malloc(sizeof(queue));
	q->list = malloc(sizeof(LinkedList));
	q->list->head = NULL;
	q->list->tail = NULL;

	q->count = 0;

	return q;
}

// Check if is empty. Will return 1 if so, else 0.
// NOTE: cannot check if a queue linked list implementation is full because nodes can be dynamically created.
int isEmpty(queue *q){
	if(q->list->head == NULL)
		return 1;
	else
		return 0;
}

// Will insert to the tail of the queue.
void enqueue(queue *q, int data){
	// Create a new node.
	node *newNode = CreateNode(data);

	// If the queue is empty, set the head AND the tail to the new node, meaning there's now only one node in the queue.
	// This will always assign the head to the first node.
	if(isEmpty(q)){
		q->list->tail = q->list->head = newNode;
	printf("Enqueued %d in node # %d\n",data, ++(q->count));
		return;
	}
	// Otherwise, assign the new node to tail->next, and move up tail afterwards.
	else{
		q->list->tail->next = newNode;
		q->list->tail = q->list- >tail->next;
	}

	// Increase the count.
	q->count++;
	printf("Enqueued %d in node # %d\n",data, q->count);
}

// Will dequeue an element from the head of the queue. Will return its value.
int dequeue(queue *q){
	node *arrow;
	int retval;

	// If the queue is empty, say so and return int min.
	if(isEmpty(q)){
		printf("EMPTY QUEUE\n");
		return INT_MIN;
	}
	// Save the address of the next head, or the second element in the queue.
	arrow = q->list->head->next;
	// Get the retval from the current head.
	retval = q->list->head->data;
	// Free the current head.
	free(q->list->head);
	// Update the head of the queue to be the saved address.
	q->list->head = arrow;

	// Update the count.
	q->count--;

	printf("Dequeued %d in the head of the list. New Count = %d.\n",retval, q->count);

	return retval;
}

// Will return the value of the front of the queue.
int peek(queue *q){
	if(isEmpty(q)){
		printf("Queue is empty.\n");
		return INT_MIN;
	}
	printf("Peeked %d at node # %d\n", q->list->head->data, 1);
	return q->list->head->data;	
}


int main(void){
int op = -2, terminate = 0, data = -1, output;
	queue *q;

	q = createQueue();
	system("cls");

	while(!terminate){

		op = -2;
		printf("Choose an operation:\n -1 - quits the program\n 0 - enqueues a data value\n 1 - dequques an element\n 2 - peeks\n 3 - is empty?\n");
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
			default:
				system("cls");
				printf("\nWrong number input.\n");
				break;
		}
	}

	
	return 0;
}