/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node {
	int value;
	struct Node *next;
	struct Node *prev;
};

void append(int value, struct Node** a_head, struct Node** a_tail) {
	/* TODO (>=11 lines of code) */
	
	if(*a_head == NULL){
		(*a_head) = malloc(sizeof(struct Node));
		(*a_tail) = (*a_head);
		(*a_tail) -> value = value;	
		(*a_head) -> prev = NULL;
		(*a_tail) -> next = NULL;
	}
	else{
		struct Node *newNode = malloc(sizeof(struct Node));
		(*a_tail) -> next = newNode;
		newNode -> value = value;
		newNode -> prev = (*a_tail) -> prev;
		(*a_tail) = newNode;
		(*a_tail) -> next = NULL;
	}
	
	assert(*a_head != NULL);            // This helps you catch bugs in your code.
	assert(*a_tail != NULL);            // "    "     "   "     "    "  "    "
	assert((*a_head) -> prev == NULL);  // "    "     "   "     "    "  "    "
	assert((*a_tail) -> next == NULL);  // "    "     "   "     "    "  "    "
}

void delete(struct Node* victim, struct Node** a_head, struct Node** a_tail) {
	/* TODO (>=13 lines of code) */
	struct Node *prevNode = NULL;
	struct Node *delNode = (*a_head);
	
	if(victim == (*a_head)){
		(*a_head) = delNode -> next;
		(*a_head) -> prev = NULL;
		free(delNode);
	}
	else{
		while(delNode != victim){
			prevNode = delNode;
			delNode = delNode -> next;
		}
		prevNode -> next = delNode -> next;
		if(victim == (*a_tail)){
			(*a_tail) = prevNode;
		}
		else{
			delNode -> next -> prev = prevNode;
		}
		free(delNode);
	}
}

void empty_list(struct Node** a_head, struct Node** a_tail) {
	/* TODO (>=3 lines of code) */
	while((*a_head) != NULL){
		struct Node *newVictim = (*a_head) -> next;
		free((*a_head));
		(*a_head) = newVictim;
	}
	(*a_tail) = (*a_head);
	assert(*a_head == NULL);  // This helps you catch bugs in your code.
	assert(*a_tail == NULL);  // "    "     "   "     "    "  "    "
}

void print_list(struct Node* head) {  /* do not modify print_list(..) */
	if(head == NULL) {
		printf("EMPTY\n");
	}
	else {
		for(struct Node* curr = head; curr != NULL; curr = curr -> next) {
			printf("%d", curr -> value);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {    /* do not modify main(..) */
	struct Node* head = NULL;
	struct Node* tail = NULL;
	append(7, &head, &tail);
	assert(head == tail);
	print_list(head);  // Output:  "7"
	append(6, &head, &tail);
	append(8, &head, &tail);
	print_list(head);  // Output:  "768"
	append(3, &head, &tail);
	append(3, &head, &tail);
	append(6, &head, &tail);
	print_list(head);  // Output:  "768336"
	delete(tail, &head, &tail);
	print_list(head);  // Output:  "76833"
	delete(head, &head, &tail);
	print_list(head);  // Output:  "6833"
	delete(head -> next, &head, &tail);
	print_list(head);  // Output:  "633"
	append(9, &head, &tail);
	print_list(head);  // Output:  "6339"
	empty_list(&head, &tail);
	print_list(head);  // Output:  "EMPTY"
	return EXIT_SUCCESS;
}
