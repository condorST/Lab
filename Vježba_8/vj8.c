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
    Tree_position node;
    Queue_position next;
}queue;



Tree_position make_new_Tree_node(int number);
Tree_position insert(Tree_position current, Tree_position new_node);
int print_inorder(Tree_position current);
int print_preorder(Tree_position current);
int print_postorder(Tree_position current);
int print_level_order(Tree_position current, Queue_position head);
int push_in_queue(Queue_position head, Tree_position current);
Queue_position find_last_in_queue(Queue_position head);
Tree_position pop_from_queue(Queue_position head);
Tree_position delete_element(Tree_position current, int number);
Tree_position find_Min(Tree_position current);
Tree_position find_Max(Tree_position current);
Tree_position search_for_element(Tree_position current, int number);
Tree_position free_Tree(Tree_position current);
// int free_Queue(Queue_position top);

int main(void) {

    int num = 0;
    int choice = 0;
    Tree_position root = (Tree_position)malloc(sizeof(Tree));

    if (root == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    queue top = { .node = 0,.next = NULL };
    Queue_position head = &top;



    printf("Type in the value of root element: ");
    scanf(" %d", &num);
    root->number = num;
    root->left = NULL;
    root->right = NULL;


    // MENU
    while (1) {
        printf("\n");
        printf("============OPTIONS============");
        printf("\nChoose what you want to do:\n");
        printf("1 - insert element\n");
        printf("2 - print tree inorder\n");
        printf("3 - print tree preorder\n");
        printf("4 - print tree postorder\n");
        printf("5 - print tree level order\n");
        printf("6 - delete element from tree\n");
        printf("7 - find element in tree\n");
        printf("8 - exit\n");
        printf("============OPTIONS============");

        printf("\nYour choice: \n");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            printf("Type in the value of the new element in tree: ");
            scanf(" %d", &num);
            Tree_position new_el = make_new_Tree_node(num);
            root = insert(root, new_el);
            break;

        case 2:
            printf(" Tree inorder: ");
            print_inorder(root);
            printf("\n");
            break;

        case 3:
            printf(" Tree preorder: ");
            print_preorder(root);
            printf("\n");
            break;

        case 4:
            printf(" Tree postorder: ");
            print_postorder(root);
            printf("\n");
            break;

        case 5:
            printf(" Tree level order: ");
            print_level_order(root, head);
            printf("\n");
            break;

        case 6:
            printf("Insert value of element you want to delete: ");
            scanf("%d", &num);

            Tree_position res = NULL;
            res = search_for_element(root, num);

            if (res == NULL)
            {
                printf("There is no element with that value in this tree!\n");
            }

            root = delete_element(root, num);

            break;

        case 7:
            printf("Insert element you want to find: \n");
            scanf("%d", &num);


            res = search_for_element(root, num);

            if (res != NULL)
            {
                printf("There's an element with that value in this tree!\n");
            }
            else {
                printf("There is no element with that value in this tree!\n");
            }

            break;

        case 8:
            if (free_Tree(root) == 0) {
                printf("Successful memory cleaning tree!");
                printf("\n");
            }

            return EXIT_SUCCESS;
            break;

        default:
            printf("Error, Try Again!");
            break;
        }

    }



    return EXIT_SUCCESS;
}

Tree_position make_new_Tree_node(int number) {
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

    if (current->number < new_node->number) {
        current->right = insert(current->right, new_node);
    }
    else if (current->number > new_node->number) {
        current->left = insert(current->left, new_node);
    }
    else {
        free(new_node);
    }

    return current;
}

int print_inorder(Tree_position current) {

    if (current == NULL) {
        return EXIT_SUCCESS;
    }

    print_inorder(current->left);
    printf(" %d", current->number);
    print_inorder(current->right);


    return EXIT_SUCCESS;
}

int print_preorder(Tree_position current) {

    if (current == NULL) {
        return EXIT_SUCCESS;
    }


    printf(" %d", current->number);
    print_preorder(current->left);
    print_preorder(current->right);


    return EXIT_SUCCESS;
}


int print_postorder(Tree_position current) {

    if (current == NULL) {
        return EXIT_SUCCESS;
    }

    print_postorder(current->left);
    print_postorder(current->right);
    printf(" %d", current->number);


    return EXIT_SUCCESS;
}

int print_level_order(Tree_position current, Queue_position head) {
    Tree_position temp = current;


    if (temp == NULL)
    {
        printf("Tree is empty!\n");
        return EMPTY_TREE;
    }

    while (temp != NULL)
    {

        printf(" %d ", temp->number);

        if ((temp->left) != NULL)
        {
            push_in_queue(head, temp->left);
        }

        if ((temp->right) != NULL)
        {
            push_in_queue(head, temp->right);
        }

        temp = pop_from_queue(head);
    }


    return EXIT_SUCCESS;
}



int push_in_queue(Queue_position head, Tree_position current) {

    Queue_position new = NULL;
    Queue_position last = NULL;

    new = (Queue_position)malloc(sizeof(queue));

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    new->node = current;
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


Tree_position pop_from_queue(Queue_position head) {
    Queue_position temp = head->next;
    Tree_position data = NULL;

    if (head == NULL) {
        printf("Queue is empty!");
        return EMPTY_QUEUE;
    }

    data = temp->node;

    head->next = temp->next;
    free(temp);

    return data;
}


Tree_position delete_element(Tree_position current, int number) {

    if (current == NULL) {
        return NULL;
    }

    if (current->number < number) {
        current->right = delete_element(current->right, number);
    }

    else if (current->number > number) {
        current->left = delete_element(current->left, number);
    }

    else {

        if (current->left) {
            Tree_position temp = find_Max(current->left);
            current->number = temp->number;
            current->left = delete_element(current->left, temp->number);
        }

        else if (current->right) {
            Tree_position temp = find_Min(current->right);
            current->number = temp->number;
            current->right = delete_element(current->right, temp->number);
        }

        else {
            free(current);
            return NULL;
        }
    }

    return current;
}

Tree_position find_Min(Tree_position current) {

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

Tree_position find_Max(Tree_position current) {

    while (current->right != NULL) {
        current = current->right;
    }

    return current;
}

Tree_position search_for_element(Tree_position current, int number) {

    if (current == NULL)
    {
        return NULL;
    }

    else if (number == current->number)
    {
        return current;
    }

    else if (number < current->number)
    {
        return search_for_element(current->left, number);
    }

    else
    {
        return search_for_element(current->right, number);
    }

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

// int free_Queue(Queue_position top){
//   Queue_position head=top->next;
//   Queue_position temp=NULL;

//   if(top->next==NULL){
//     free(top);
//     return EXIT_SUCCESS;
//   }

//   while(head!=NULL){
//     temp=head->next;
//     free(head);
//     head=temp;
//   }

//   return EXIT_SUCCESS;
// }