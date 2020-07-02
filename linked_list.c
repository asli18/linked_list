#include <stdio.h>
#include <stdlib.h>

/* IDE Output
 * https://ide.geeksforgeeks.org/8tVHZmpvty
 * https://ideone.com/eCYrKN
 */

typedef struct node {
    int data;
    struct node *next;
} Node;

void add_node(Node **head, int value);
void insert_node(Node **head, int insert_after_value, int value);
void delete_node(Node **head, int value);
void push_node(Node **head, int data);
void reverse(Node **head);
void print_list(Node *node);
void free_list(Node *node);
Node *get_intersection_node(Node *headA, Node *headB);

int main(void)
{
    {
        Node *head = NULL;

        push_node(&head, 4);
        push_node(&head, 3);
        push_node(&head, 2);
        push_node(&head, 1);
        push_node(&head, 0);
        print_list(head);

        reverse(&head);
        print_list(head);

        free_list(head);
    }

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

        free_list(head);
    }

    return 0;
}

void add_node(Node **head, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

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

    if (value == current->data) {
        *head = current->next;
        free(current);
        return;
    }

    while (current != NULL) {
        if (current->next->data == value) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

void push_node(Node **head, int data)
{
    Node *new = (Node *)malloc(sizeof(Node));

    new->data = data;
    new->next = *head;
    *head = new;
}

void reverse(Node **head)
{
    Node *cur = *head;
    Node *prev = NULL;
    Node *next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *head = prev;
}

void print_list(Node *node)
{
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\r\n");
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

Node *get_intersection_node(Node *headA, Node *headB)
{
    Node *p1 = headA;
    Node *p2 = headB;

    while (p1 != p2) {
        /* When pA reaches the end of a list, then redirect it to the head of B;
         * similarly when pB reaches the end of a list, redirect it the head of A.
         */
        p1 = p1 ? p1->next : headB;
        p2 = p2 ? p2->next : headA;
    }
    return p1; /* return intersection or NULL */
}

