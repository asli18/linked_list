#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    struct node *next;
    unsigned int data;
} NODE;

void push(NODE **head, unsigned int data) {
    NODE *new = (NODE *)malloc(sizeof(NODE));
    
    new->data = data;
    new->next = *head;
    *head = new;
}

void reverse(NODE **head) {
    NODE *pre = NULL;
    NODE *next = NULL;
    NODE *root = *head;
    
    while (root != NULL) {
        next = root->next;
        root->next = pre;
        pre = root;
        root = next;
    }
    *head = pre;
}

void print_list(NODE *head) {
    while (head != NULL) {
        printf("%02u ", head->data);
        head = head->next;
    }
    printf("\r\n");
}

int main() {
    NODE *head = NULL;

    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    push(&head, 0);

    print_list(head);
    
    reverse(&head);
    print_list(head);

	return 0;
}
