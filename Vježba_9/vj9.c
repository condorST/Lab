#pragma warning (disable: 4047)
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)
#define EMPTY_TREE (-1)
#define EMPTY_QUEUE (-1)


// Binary tree structure
struct _tree;
typedef struct _tree* Tree_position;
typedef struct _tree {
    int number;
    Tree_position left;
    Tree_position right;
}Tree;

// Queue structure
struct _queue;
typedef struct _queue* Queue_position;
typedef struct _queue {
    int num;
    Queue_position next;
}queue;



Tree_position make_new_node(int number);
Tree_position insert(Tree_position current, Tree_position new_node);
int replace(Tree_position current);
int print_inorder(Tree_position current);
int push_in_queue(Queue_position head, int number);
Queue_position find_last_in_queue(Queue_position head);
int pop_from_queue(Queue_position head);
int sort_inorder(Tree_position new_el, Queue_position head);
int print_to_file(char* filename, Queue_position head);
int print_to_file_replaced(char* filename, Queue_position head);
Tree_position free_Tree(Tree_position current);




int main(void) {

    srand(time(NULL));
    int i = 0;
    // int array[10]={2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int rand_array[10] = { 0 };
    char filename[MAX_FILE_NAME] = { 0 };


    Tree_position root = NULL;
    queue top = { .num = 0,.next = NULL };
    Queue_position head = &top;

    printf("Insert filename: ");
    scanf(" %s", filename);



    for (i = 0; i < 10; i++) {
        rand_array[i] = rand() % 80 + 10;
    }


    for (i = 0; i < 10; i++) {
        Tree_position new_el = make_new_node(rand_array[i]);
        root = insert(root, new_el);
    }

    printf("Print tree:\n");
    print_inorder(root);

    // Print to file before replace
    sort_inorder(root, head);
    print_to_file(filename, head);

    printf("\n");
    replace(root);
    printf("Print tree after replace:\n");
    print_inorder(root);
    printf("\n");

    // Print to file after replace
    sort_inorder(root, head);
    print_to_file_replaced(filename, head);


    // Free memory
    if (free_Tree(root) == 0) {
        printf("Successful memory cleaning tree!");
        printf("\n");
    }


    return EXIT_SUCCESS;
}

Tree_position make_new_node(int number) {
    Tree_position new_node = NULL;
    new_node = (Tree_position)malloc(sizeof(Tree));

    if (new_node == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    new_node->number = number;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}


Tree_position insert(Tree_position current, Tree_position new_node) {

    if (NULL == current) {
        return new_node;
    }

    if (current->number <= new_node->number) {
        current->left = insert(current->left, new_node);
    }
    else {
        current->right = insert(current->right, new_node);
    }


    return current;
}

int replace(Tree_position current) {

    int value;

    if (current == NULL) {
        return 0;
    }

    value = current->number;

    current->number = replace(current->left) + replace(current->right);
    return value + current->number;

}

int print_to_file(char* filename, Queue_position head) {

    int i = 0;
    FILE* output = NULL;
    output = fopen(filename, "w");

    if (output == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (head->next != NULL) {
        fprintf(output, " %d ", pop_from_queue(head));
    }

    fprintf(output, "\n");
    fclose(output);

    return EXIT_SUCCESS;
}

int print_to_file_replaced(char* filename, Queue_position head) {
    int i = 0;
    FILE* output = NULL;
    output = fopen(filename, "a");

    if (output == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (head->next != NULL) {
        fprintf(output, " %d ", pop_from_queue(head));
    }

    fclose(output);

    return EXIT_SUCCESS;
}


int sort_inorder(Tree_position new_el, Queue_position head) {

    if (new_el == NULL) {
        return EXIT_SUCCESS;
    }


    sort_inorder(new_el->right, head);
    push_in_queue(head, new_el->number);
    sort_inorder(new_el->left, head);

    return EXIT_SUCCESS;
}



int push_in_queue(Queue_position head, int number) {

    Queue_position new = NULL;
    Queue_position last = NULL;

    new = (Queue_position)malloc(sizeof(queue));

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    new->num = number;
    new->next = NULL;

    last = find_last_in_queue(head);

    new->next = last->next;
    last->next = new;

    return EXIT_SUCCESS;
}


Queue_position find_last_in_queue(Queue_position head) {

    while (head->next != NULL) {
        head = head->next;
    }

    return head;
}


int pop_from_queue(Queue_position head) {
    Queue_position temp = head->next;
    int data = 0;

    if (head == NULL) {
        printf("Queue is empty!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    if (head->next == NULL) {
        return NULL;
    }

    data = temp->num;

    head->next = temp->next;
    free(temp);

    return data;
}


int print_inorder(Tree_position current) {

    if (current == NULL) {
        return EXIT_SUCCESS;
    }

    print_inorder(current->right);
    printf(" %d", current->number);
    print_inorder(current->left);


    return EXIT_SUCCESS;
}


Tree_position free_Tree(Tree_position current) {

    if (current == NULL) {
        return NULL;
    }

    free_Tree(current->left);
    free_Tree(current->right);
    free(current);

    return EXIT_SUCCESS;
}