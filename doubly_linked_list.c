#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

void add_node(Node **head, int value);
void print_list(Node *node);
void insert_node(Node **head, int insert_after_value, int value);
void delete_node(Node **head, int value);
void inverse_print_list(Node *node);
void free_list(Node *node);

int main(int argc, char *argv[])
{
    Node *head = NULL;

    add_node(&head, 5);
    add_node(&head, 128);
    add_node(&head, 41);
    print_list(head);

    /* insert non-exist node, linked list would not have changed */
    insert_node(&head, 77, 92);
    /* insert after node of data 128 */
    insert_node(&head, 128, 84);
    /* insert after the last node */
    insert_node(&head, 41, 97);
    print_list(head);

    /* delete the first node */
    delete_node(&head, 5);
    /* delete the node of data 41 */
    delete_node(&head, 41);
    /* delete the last node */
    delete_node(&head, 97);
    print_list(head);

    Node *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    inverse_print_list(last);

    free_list(head);

    return 0;
}

void add_node(Node **head, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    } else {
        Node *current;
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
        return;
    }
}

void insert_node(Node **head, int insert_after_value, int value)
{
    Node *current = *head;

    while (current != NULL) {
        if (insert_after_value == current->data) {
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->data = value;

            new_node->next = current->next;
            new_node->prev = current;

            if (new_node->next != NULL)
                new_node->next->prev = new_node;

            current->next = new_node;

            break;
        }
        current = current->next;
    }
}

void delete_node(Node **head, int value)
{
    Node *current = *head;
    Node *temp;

    if ((current != NULL) && (value == current->data)) {
        *head = current->next;
        (*head)->prev = NULL;
        free(current);
        return;
    }

    while (current != NULL) {
        if ((current->next != NULL) && (current->next->data == value)) {
            temp = current->next;
            current->next = current->next->next;

            if (current->next != NULL)
                current->next->prev = current;

            free(temp);
            return;
        }
        current = current->next;
    }
}

void print_list(Node *node)
{
    printf("List:\n");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void inverse_print_list(Node *node)
{
    printf("Inverse List:\n");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->prev;
    }
    printf("\n");
}

void free_list(Node *node)
{
    Node *current, *temp;
    current = node;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}
