#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

void add_node(Node **start, int value);
void insert_node(Node **start, int insert_after_value, int value);
void delete_node(Node **start, int value);
void print_list(Node *node);
void free_list(Node *node);

int main(int argc, char *argv[])
{
    // create first node "head"
    Node *head = NULL;
    add_node(&head, 5);
    add_node(&head, 128);
    add_node(&head, 41);

    // insert non-exist node, linked list would not have changed
    insert_node(&head, 77, 92);
    // insert after node of data 128
    insert_node(&head, 128, 84);
    // insert after the last node
    insert_node(&head, 41, 97);

    // delete the first node
    delete_node(&head, 5);
    // delete the node of data 41
    delete_node(&head, 41);
    // delete the last node
    delete_node(&head, 97);

    print_list(head);
    free_list(head);

    return 0;
}

void add_node(Node **start, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (*start == NULL) {
        *start = new_node;
        (*start)->next = *start;
        return;
    } else {
        Node *current;
        current = *start;
        while (current->next != *start) {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = *start;
        return;
    }
}

void insert_node(Node **start, int insert_after_value, int value)
{
    Node *current = *start;

    do {
        if (insert_after_value == current->data) {
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->data = value;

            new_node->next = current->next;
            current->next = new_node;
            break;
        }
        current = current->next;
    } while (current != *start);
}

void delete_node(Node **start, int value)
{
    Node *current = *start;
    Node *temp;
    Node *ori_start = *start;

    if (value == current->data) {
        *start = current->next;
        free(current);
        do {
            current = current->next;
        } while (current->next != ori_start);
        current->next = *start;
        return;
    }

    do {
        if (current->next->data == value) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    } while (current != *start);

}

void print_list(Node *node)
{
    Node *first_node = node;
    printf("%d ", node->data);
    node = node->next;

    while (node != NULL) {
        if (node == first_node) break;
        printf("%d ", node->data);
        node = node->next;
    }
    printf("%d\n", node->data);
}

void free_list(Node *node)
{
    int total_node = 1;
    Node *first = node;
    node = node->next;
    while (node != first) {
        node = node->next;
        total_node++;
    }

    Node *current = first;
    Node *temp;
    int i;
    for (i = 0; i < total_node; i++) {
        temp = current;
        current = current->next;
        free(temp);
    }
}
