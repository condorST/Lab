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
	char ime_grada[MAX_LINE];
	int br_stan;
	Tree_position left;
	Tree_position right;
}Tree;

struct _drzave;
typedef struct _drzave* positionD;
typedef struct _drzave {
	char ime_drzave[MAX_LINE];

	Tree_position root;
	positionD next;
}drzave;



positionD novaDrzava(char* imeDrzave);
int readListFromFile(char* filename, positionD head);
int insertSortedList(positionD head, positionD novaDrzava);
int printList(positionD head);
Tree_position make_new_city(char* imeGrada, int br_stan);
Tree_position insert_in_Tree(Tree_position current, Tree_position newCity);
int insert_in_Tree_from_file(char* filename, positionD novaDrzava);
int print_Tree_inorder(Tree_position current);
int gradoviCmp(Tree_position grad1, Tree_position grad2);
positionD find_state(char* imeDrzave, positionD head);
int print_cities_from_current_state(Tree_position current, int broj_stan);
Tree_position free_Tree(Tree_position current);
int delete_list(positionD top);


int main(void)
{
	drzave drzava = { .ime_drzave = {0},.next = NULL,.root = NULL };
	positionD head = &drzava;

	char imeDrzave[MAX_LINE] = { 0 };
	positionD trazenaDrzava = NULL;
	int br_stan = 0;

	char filename[MAX_FILE_NAME];
	printf("Upisi ime filea: \n");
	scanf(" %s", filename);


	readListFromFile(filename, head);
	printList(head);
	printf("\n");


	printf("Upisite ime drzave koju zelite pretraziti: ");
	scanf(" %s", imeDrzave);

	trazenaDrzava = find_state(imeDrzave, head);

	if (trazenaDrzava == NULL) {
		printf("Drzava ne postoji!");
		return EXIT_SUCCESS;
	}
	else {
		printf("Uspjesno pronadena drzava!\n");
	}

	printf("Upisite minimalan broj stanovnika za trazenu drzavu: \n");
	scanf("%d", &br_stan);
	print_cities_from_current_state(trazenaDrzava->root, br_stan);


	printf("==================================\n");

	if (free_Tree(head->root) == 0) {
		printf("Successful memory cleaning tree!");
		printf("\n");
	}

	if (delete_list(head) == 0) {
		printf("Successful memory cleaning list!");
		printf("\n");
	}

	return EXIT_SUCCESS;
}

int print_cities_from_current_state(Tree_position current, int broj_stan) {

	if (current == NULL) {
		return EXIT_SUCCESS;
	}

	print_cities_from_current_state(current->left, broj_stan);
	if ((current->br_stan) >= broj_stan) {
		printf(" %s %d\n", current->ime_grada, current->br_stan);
	}
	print_cities_from_current_state(current->right, broj_stan);

	return EXIT_SUCCESS;
}


positionD find_state(char* imeDrzave, positionD head) {

	positionD temp = head;

	while (temp != NULL && strcmp(temp->ime_drzave, imeDrzave) != 0) {
		temp = temp->next;
	}

	return temp;
}


Tree_position make_new_city(char* imeGrada, int br_stan) {

	Tree_position newCity = NULL;
	newCity = (Tree_position)malloc(sizeof(Tree));

	if (newCity == NULL) {
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	strcpy(newCity->ime_grada, imeGrada);
	newCity->br_stan = br_stan;
	newCity->left = NULL;
	newCity->right = NULL;

	return newCity;
}


Tree_position insert_in_Tree(Tree_position current, Tree_position newCity) {

	int result = 0;

	if (NULL == current) {
		return newCity;
	}

	result = gradoviCmp(current, newCity);

	if (result < 0) {
		current->right = insert_in_Tree(current->right, newCity);
	}
	else if (result > 0) {
		current->left = insert_in_Tree(current->left, newCity);
	}
	else {
		free(newCity);
	}

	return current;
}

int gradoviCmp(Tree_position grad1, Tree_position grad2) {
	int res = 0;
	res = grad1->br_stan - grad2->br_stan;

	if (res == 0) {
		res = strcmp(grad1->ime_grada, grad2->ime_grada);
	}

	return res;
}


positionD novaDrzava(char* imeDrzave) {

	positionD novaDrzava = NULL;
	novaDrzava = (positionD)malloc(sizeof(drzave));

	if (novaDrzava == NULL)
	{
		printf("Memory not allocated correctly!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	strcpy(novaDrzava->ime_drzave, imeDrzave);

	novaDrzava->next = NULL;
	novaDrzava->root = NULL;

	return novaDrzava;
}

int insert_in_Tree_from_file(char* filename, positionD novaDrzava) {


	FILE* fp = NULL;
	fp = fopen(filename, "r");

	char imeGrada[MAX_LINE] = { 0 };
	int br_stan = 0;



	if (fp == NULL) {
		printf("Dear customer, the file %s didn't open! \r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %d\n", imeGrada, &br_stan);
		Tree_position newCity = make_new_city(imeGrada, br_stan);

		novaDrzava->root = insert_in_Tree(novaDrzava->root, newCity);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}



int readListFromFile(char* filename, positionD head)
{

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	char imeD[MAX_LINE] = { 0 };
	char file_gradovi[MAX_LINE] = { 0 };

	drzave pom = { .ime_drzave = "", .root = NULL, .next = NULL };
	positionD temp = &pom;


	if (fp == NULL) {
		printf("Dear customer, the file %s didn't open! \r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}


	while (!feof(fp)) {
		fscanf(fp, "%s %s\n", imeD, file_gradovi);
		temp = novaDrzava(imeD);

		insert_in_Tree_from_file(file_gradovi, temp);

		insertSortedList(head, temp);

	}


	fclose(fp);
	return EXIT_SUCCESS;
}


int insertSortedList(positionD head, positionD novaDrzava) {

	positionD temp = head;

	while (temp->next != NULL && strcmp(temp->next->ime_drzave, novaDrzava->ime_drzave) < 0) {
		temp = temp->next;
	}


	novaDrzava->next = temp->next;
	temp->next = novaDrzava;

	return EXIT_SUCCESS;
}


int print_Tree_inorder(Tree_position current) {

	if (current == NULL) {
		return EXIT_SUCCESS;
	}

	print_Tree_inorder(current->left);
	printf("\tGrad: %s sa brojem stanovnika: %d\n", current->ime_grada, current->br_stan);
	print_Tree_inorder(current->right);


	return EXIT_SUCCESS;
}

int printList(positionD head) {

	positionD temp = head->next;

	if (temp == NULL) {
		printf("Lista je prazna!");
		return 0;
	}

	while (temp != NULL) {
		printf(" Drzava: %s \n", temp->ime_drzave);
		print_Tree_inorder(temp->root);
		temp = temp->next;
	}

	return EXIT_SUCCESS;

}

// FREE MEMORY
Tree_position free_Tree(Tree_position current) {

	if (current == NULL) {
		return NULL;
	}

	free_Tree(current->left);
	free_Tree(current->right);
	free(current);

	return EXIT_SUCCESS;
}

int delete_list(positionD top) {
	positionD head = top->next;
	positionD temp;

	while (head != NULL) {
		temp = head->next;
		free(head);
		head = temp;
	}

	return EXIT_SUCCESS;
}
