#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
	struct node *prev;
}Node;

void add_node(Node **start, int value);
void print_list(Node *node);
void inverse_print_list(Node *node);
void free_list(Node *node);

int main(int argc, char* argv[])
{
	// create first node "head"
	Node *head = NULL;
	add_node(&head, 5);
	add_node(&head, 128);
	add_node(&head, 41);

	print_list(head);
	inverse_print_list(head);
	free_list(head);
	
	return 0;	
}

void add_node(Node **start, int value)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->data = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	if(*start == NULL) {
		*start = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
		return;
	}
	else {
		Node *current;	
		current = *start;
		do {
			current = current->next;
		}while(current->next != *start);
		current->next = new_node;
		new_node->next = *start;
		new_node->prev = current;
		(*start)->prev = new_node;
		return;
	}
}

void print_list(Node *node)
{
	Node *start = node;
	printf("List:\n");
	do{
		printf("%d ", node->data); 
		node = node->next;
	}while(node != start); 
	printf("%d\n", node->data);
}

void inverse_print_list(Node *node)
{
	Node *start = node;
	printf("Inverse List:\n");
	do{
		printf("%d ", node->data); 
		node = node->prev;
	}while(node != start);
	printf("%d\n", node->data);
}

void free_list(Node *node)
{
	int total_node = 1;
	Node *first = node;
	node = node->next;
	while(node != first) {
		node = node->next;
		total_node++;
	}

	Node *current = first;
	Node *temp;
	int i;
	for(i = 0; i < total_node; i++) {
		temp = current;
		current = current->next;
		free(temp);
	}
}
