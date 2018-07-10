// Jacob Rogers
// December 20th, 2017
// linked lists, many possible function implemented through a working example.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Linked List typedef.
typedef struct node{
	struct node *next;
	int data;
}node;

// Create a new node. Will return the address of the new node.
node *createNode(int data){
	// malloc memory size of node, store address in newNode ptr.
	node *newNode = malloc(sizeof(node));

	// Check if memory allocation fails.
	if(newNode == NULL){
		printf("Memory allocation failed. Node not created.\n");
		exit(1);
	}

	// fill data fields.
	newNode->next = NULL;
	newNode->data = data;

	// Return pointer.
	return newNode;
}

// Prints the linked list. Note using head pointer to iterate, this is ok because it's a local variable to the function.
void printListRecursive(node *head){
	// Base case, return if the current address is null.
	if(head == NULL)
		return;
	
	// Print the current node's data.
	printf("|%d|-> ", head->data);
	// Recursive call to move up through the list until the end, NULL.
	printListRecursive(head->next);
}

// Insert node at head. Will return the address of the head of the updated linked list.
node *headInsert(node *head, int data){

	node *newHead = NULL;
	// Check if the head is NULL, in which case the list is empty and the head can simply be populated as the new node.
	if(head == NULL)
		return createNode(data);

	// Malloc newHead in memory.
	newHead = createNode(data);

	// Set newHead's next field to the current head.
	newHead-> next = head;

	// Return newHead's address, set head to this address in main.
	return newHead;
}

// Insert node at the end of the list. Will return the head of the list. 
node *insertEnd(node *head, int data){
	node *originalHead = head;
	// Check if the list is empty, in which case simply create a node and return it as the head.
	if(head == NULL)
		return createNode(data);
	
	// Iterate to the end of the list, once there add a new node and return the original head.
	// Iterating using the local head pointer, so original head is needed to n ot lose the list.
	while(head->next != NULL)
		head = head->next;

	head->next = createNode(data);

	return originalHead;
}

// Insert node at the end of the list. Will return the head of the list.
// TO-DO understand why this works and how recursion works fundamentally. Ask Jim Gordon and/or do internet research.
node *insertEndRecursive(node *head, int data){
	
	if(head == NULL)
		return createNode(data);

	head->next = insertEndRecursive(head->next, data);
	return head;
}

// Counts the number of nodes in the list, prints the answer, returns the number of nodes as an integer.
int countNodes(node *head){
	int count = 1;
	// Check if head is null, if so return 0 (avoids a seg fault).
	if(head == NULL){
		printf("The list contains 0 nodes.\n");
		return;
	}
	// Iterate to the end of the list, incrementing the counter after each loop iteration.
	while(head->next != NULL){
		head = head->next;
		count++;
	}

	printf("List contains %d nodes.\n", count);
	return count;
}

// Inserts a node in the middle of the list. Will return the head of the list.
node *insertMiddle(node *head, int data){
	int middle = 0, i;
	node *current = head, *newNode = createNode(data);

	// If the list is empty, create a new node and return it's address.
	if(head == NULL)
		return createNode(data);

	// Find the number of iterations required to reach the middle of the list.
	middle = (countNodes(head) / 2);

	// Iterate to the node before the middle.
	for(i = 0; i < middle - 1; i++){
		current = current->next;
	}

	// Set the newNode->next to current->next.	
	newNode->next = current->next;

	// Set current->next to newNode.
	current->next = newNode;

	return head;
}

// Will delete the first node from the list. Will return the new head of the list.
node *deleteHead(node *head){
	node *newHead;
	// If list is empty, say so and return.
	if(head == NULL){
		printf("\nList is empty.\n");
		return;
	}

	// Store the address of the 2nd node in the list in newHead.
	newHead = head->next;

	// Free the head.
	free(head);
	printf("\nHead deleted.\n");

	// return the newHead of the list to be set as the head in the calling function.
	return newHead;
}

// Will delete the last node from the list. Will return the head of the list.
node *deleteEnd(node *head){
	node *prev, *current;
	// Check if the list is empty, if so say so and return.
	if(head == NULL){
		printf("\nList is empty.\n");
		return;
	}

	// If there's only one node simply free it and return NULL (reseting head in main to be empty).
	if(head->next == NULL){
		free(head);
		printf("\nEnd deleted.\n");
		return NULL;
	}

	// Set current to the 2nd node and prev to the head.
	prev = head;
	current = head->next;

	// Iterate the two pointers up to the two last nodes of the list.
	while(current->next != NULL){
		prev = current;
		current = current->next;
	}

	// Free the last node, and set the 2nd to last node->next to NULL.
	free(current);
	printf("\nEnd deleted.\n");
	prev->next = NULL;

	return head;
}

// Deletes the entire list. Will return NULL to head in the calling function.
node* deleteList(node *head){
	node *prev, *current;
	// Check if list is empty.
	if(head == NULL){
		printf("\nList is empty.\n");
		return;
	}

	// If there's only one node just free it.
	if(head->next == NULL){
		free(head);
		printf("\nList deleted.\n");
		return;
	}

	// Set up a pair of tandem pointers at the begining of the list.
	prev = head;
	current = head->next;

	// Iterate until current == NULL, free the prev node at each iteration, move the tandem pair forward after each iteraiton.
	while(current != NULL){
		free(prev);
		prev = current;
		current = current->next;
	}

	printf("\nList deleted.\n");

	return NULL;
}

// Sean Szumlanski's function.
// Deletes the list recursively. ASK JIM GORDON HOW THIS WORKS.
node *deleteListRecursive(node *head){
	// If the list is empty return NULL, job already done. Base case?
	if (head == NULL){
		return NULL;
	}

	// We destroy the *rest* of the linked list, then come back to this node
	// and destroy it. So, we destroy the tail of the list first, then work
	// our way back toward the head.
	deleteListRecursive(head->next);

	// Try uncommenting this printf() line and tracing through what the code is
	// doing.
	//printf("Destroying the node with %d...\n", head->data);
	free(head);

	return NULL;
}

// Deletes the first node from the list that contains the given data. Returns the head of the list.
node *deleteSpecificNode(node *head, int num){
	node *prev, *current;
	// If the list is empty, return NULL and say so.
	if(head == NULL){
		printf("\nThe list is empty\n");
		return NULL;
	}

	// If the list only contains one node, check to see if it is the one, if so delete it.
	if(head->next == NULL){
		if(head->data == num){
			free(head);
			printf("\nNode containing %d deleted.\n", num);
			return NULL;
		}
	}

	// Create a pair of tandem pointers at the begining of the list.
	prev = head;
	current = head->next;

	// Iterate until the current pointer is at the node that is to be deleted.
	// If the node is not found, then return NULL and say so.
	while(current != NULL){
		// If the node is found, set prev->next to current->next, and free current, then break and return.
		if(current->data == num){
			prev->next = current->next;
			free(current);
			printf("\nNode containing %d deleted.\n", num);
			return head;
		}

		// Move the tandem pointers forward.
		prev = current;
		current = current->next;
	}
	
	printf("No node contains the given data. No nodes were deleted.\n");
	return head;
}	

// Will return the number of nodes that contain the given data.
int countSpecific(node * head, int key){
	if(head == NULL)
		return 0;

	return (head->data == key) + countSpecific(head->next, key);
}


int main(void){

	int selection = -2;
	int data = 0, terminate = 0;
	node *head = NULL;

	while(!terminate){

		selection = -2;
		printf("\nChoose an Operation:\n -1 - Ends program\n 0 - print list\n 1 - insert at head\n 2 - insert at end (iterative)\n 3 - insert at end (recursive)\n 4 - count nodes\n 5- insert in middle\n 6 - Delete Head\n 7 - Delete end\n 8 - Delete List (iterative)\n 9 - Delete List (Recursive)\n 10 - Delete a specific node\n 11 - Count A specific Key's Occurence\n");
		if(scanf("%d", &selection) != 1){
			system("cls");
			printf("\nA non-numeric value was entered. Ending program to avoid crash.\n");
			exit(1);
		}

		switch(selection){
			case -1: // TERMINATE.
				system("cls");
				head = deleteListRecursive(head);
				printf("\nProgram terminated.\n");
				terminate = 1;
				break;
			case 0: // PRINT LIST.
				system("cls");
				printf("\n");
				printListRecursive(head);
				printf("\n");
				break;
			case 1: // INSERT AT HEAD.
				system("cls");
				printf("\nWhat is the data to be inserted: \n");
				scanf("%d", &data);
				
				head = headInsert(head, data);
				system("cls");
				printf("\n%d insered at head.\n", data);
				break;
			case 2: // INSERT AT END ITERATIVE.
				system("cls");
				printf("\nWhat is the data to be inserted: \n");
				scanf("%d", &data);
				head = insertEnd(head, data);
				system("cls");
				printf("\n%d inserted at end.\n", data);
				break;
			case 3: // INSERT AT END RECURSIVE.
				system("cls");
				printf("\nWhat is the data to be inserted: \n");
				scanf("%d", &data);
				
				head = insertEndRecursive(head, data);
				system("cls");
				printf("\n%d inserted at end.\n", data);
				break;
			case 4: // COUNT NODES.
				system("cls");
				printf("\n");
				countNodes(head);
				break;
			case 5: // INSERT IN MIDDLE.
				system("cls");
				printf("\nWhat is the data to be inserted: \n");
				scanf("%d", &data);
				
				head = insertMiddle(head, data);
				system("cls");
				printf("\n%d inserted in middle.\n", data);
				break;
			case 6: // DELETE HEAD.
				system("cls");
				head = deleteHead(head);
				break;
			case 7: // DELETE END.
				system("cls");
				head = deleteEnd(head);
				break;
			case 8: // DELETE LIST (ITERATIVE).
				system("cls");
				head = deleteList(head);
				break;
			case 9: // DELETE LIST (RECURSIVE).
				system("cls");
				head = deleteListRecursive(head);
				printf("\nList deleted.\n");
				break;
			case 10: // DELETE A SPECIFIC NODE.
				system("cls");
				printf("\nEnter the data contained in the node that you wish to delete.\n");
				scanf("%d", &data);
				head = deleteSpecificNode(head, data);
				break;
			case 11: // COUNT SPECIFIC KEYS.
				system("cls");
				printf("Enter the data you want to count.\n");
				scanf("%d", &data);
				system("cls");
				printf("The number of times %d is in the list is %d\n", data, countSpecific(head, data));
				break;
			default:
				system("cls");
				printf("\nWrong number input.\n");
				break;
		}
	}

	return 0;
}
