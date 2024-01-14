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



struct _gradovi;
typedef struct _gradovi* positionG;
typedef struct _gradovi {
	char ime_grada[MAX_LINE];
	int br_stan;

	positionG next;
}gradovi;


// Binary tree structure
struct _tree;
typedef struct _tree* Tree_position;
typedef struct _tree {
	char ime_drzave[MAX_LINE];
	positionG head;

	Tree_position left;
	Tree_position right;
}Tree;


Tree_position nova_Drzava(char* imeDrzave);
Tree_position insert_in_Tree(Tree_position current, Tree_position novaDrzava);
int read_Tree_from_file(char* filename, Tree_position current);
int print_Tree_inorder(Tree_position current);
positionG make_new_city(char* imeGrada, int br_stan);
int insert_to_list_from_file(positionG head, char* filename);
int insertSortedList(positionG head, positionG noviGrad);
int printList(positionG head);
Tree_position search_for_element(Tree_position current, char* imeDrzave);
int print_cities_from_current_state(positionG head, Tree_position trazenaDrzava, int broj_stan);
int gradoviCmp(positionG grad1, positionG grad2);
Tree_position free_Tree(Tree_position current);
int delete_list(positionG top);



int main(void) {


	Tree_position current = NULL;
	Tree_position trazenaDrzava = NULL;
	int br_stan = 0;
	char imeDrzave[MAX_LINE] = { 0 };


	char filename[MAX_FILE_NAME];
	printf("Upisi ime filea: \n");
	scanf(" %s", filename);


	current = read_Tree_from_file("drzave.txt", current);

	print_Tree_inorder(current);
	printf("\n");


	printf("Upisite ime drzave koju zelite pretraziti: ");
	scanf(" %s", imeDrzave);

	trazenaDrzava = search_for_element(current, imeDrzave);

	if (trazenaDrzava == NULL) {
		printf("Drzava ne postoji!");
		return EXIT_SUCCESS;
	}
	else {
		printf("Uspjesno pronadena drzava!\n");
	}

	printf("Upisite minimalan broj stanovnika za trazenu drzavu: \n");
	scanf("%d", &br_stan);
	print_cities_from_current_state(trazenaDrzava->head, trazenaDrzava, br_stan);


	printf("==================================\n");

	if (free_Tree(current) == 0) {
		printf("Successful memory cleaning tree!");
		printf("\n");
	}

	if (delete_list(current->head) == 0) {
		printf("Successful memory cleaning list!");
		printf("\n");
	}

	return EXIT_SUCCESS;
}


int print_cities_from_current_state(positionG head, Tree_position trazenaDrzava, int broj_stan) {

	positionG temp = head->next;

	printf("Drzava: %s\n", trazenaDrzava->ime_drzave);
	while (temp != NULL) {
		if (temp->br_stan >= broj_stan) {
			printf("Grad: %s sa brojem stanovnika: %d\n", temp->ime_grada, temp->br_stan);
		}
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}


Tree_position search_for_element(Tree_position current, char* imeDrzave) {

	if (current == NULL)
	{
		printf("\n%s nije u stablu!\n", imeDrzave);
		return NULL;
	}

	else if (strcmp(current->ime_drzave, imeDrzave) == 0)
	{
		return current;
	}

	else if (strcmp(current->ime_drzave, imeDrzave) > 0)
	{
		return search_for_element(current->left, imeDrzave);
	}

	else
	{
		return search_for_element(current->right, imeDrzave);
	}

}



int print_Tree_inorder(Tree_position current) {

	if (current == NULL) {
		return EXIT_SUCCESS;
	}

	print_Tree_inorder(current->left);
	printf("\nDrzava: %s\n", current->ime_drzave);
	printList(current->head);
	print_Tree_inorder(current->right);


	return EXIT_SUCCESS;
}



int printList(positionG head) {

	positionG temp = head->next;

	if (temp == NULL) {
		printf("Lista je prazna!");
		return 0;
	}

	while (temp != NULL) {
		printf("\tGrad: %s sa brojem stanovnika: %d\n", temp->ime_grada, temp->br_stan);
		temp = temp->next;
	}

	return EXIT_SUCCESS;

}



int read_Tree_from_file(char* filename, Tree_position current) {

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	char imeD[MAX_LINE] = { 0 };
	char file_gradovi[MAX_LINE] = { 0 };


	if (fp == NULL) {
		printf("Dear customer, the file %s didn't open! \r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}


	while (!feof(fp)) {

		fscanf(fp, "%s %s\n", imeD, file_gradovi);
		Tree_position temp = nova_Drzava(imeD);

		current = insert_in_Tree(current, temp);
		insert_to_list_from_file(temp->head, file_gradovi);

	}


	fclose(fp);
	return current;
}

int insert_to_list_from_file(positionG head, char* filename) {

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	char ime_grada[MAX_LINE] = { 0 };
	int br_stan = 0;
	int result = 0;



	if (fp == NULL) {
		printf("Dear customer, the file %s didn't open! \r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}


	while (!feof(fp)) {
		fscanf(fp, "%s %d\n", ime_grada, &br_stan);
		positionG temp = make_new_city(ime_grada, br_stan);

		insertSortedList(head, temp);

	}


	fclose(fp);
	return EXIT_SUCCESS;
}

positionG make_new_city(char* imeGrada, int br_stan) {

	positionG newCity = NULL;
	newCity = (positionG)malloc(sizeof(gradovi));

	if (newCity == NULL) {
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	strcpy(newCity->ime_grada, imeGrada);
	newCity->br_stan = br_stan;
	newCity->next = NULL;

	return newCity;
}

int insertSortedList(positionG head, positionG noviGrad) {

	positionG temp = head;

	while (temp->next != NULL && temp->next->br_stan < noviGrad->br_stan) {
		if (temp->next->br_stan == noviGrad->br_stan) {
			while (temp->next != NULL && strcmp(temp->next->ime_grada, noviGrad->ime_grada) < 0) {
				temp = temp->next;
			}
		}
		temp = temp->next;
	}

	noviGrad->next = temp->next;
	temp->next = noviGrad;


	return EXIT_SUCCESS;

}

Tree_position insert_in_Tree(Tree_position current, Tree_position novaDrzava) {

	if (NULL == current) {
		return novaDrzava;
	}

	if (strcmp(current->ime_drzave, novaDrzava->ime_drzave) > 0) {
		current->left = insert_in_Tree(current->left, novaDrzava);
	}
	else if (strcmp(current->ime_drzave, novaDrzava->ime_drzave) < 0) {
		current->right = insert_in_Tree(current->right, novaDrzava);
	}
	else {
		free(novaDrzava);
	}

	return current;
}


Tree_position nova_Drzava(char* imeDrzave) {

	Tree_position novaDrzava = NULL;
	novaDrzava = (Tree_position)malloc(sizeof(Tree));

	if (novaDrzava == NULL)
	{
		printf("Memory not allocated correctly!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	strcpy(novaDrzava->ime_drzave, imeDrzave);

	novaDrzava->left = NULL;
	novaDrzava->right = NULL;

	novaDrzava->head = (positionG)malloc(sizeof(gradovi));
	novaDrzava->head->next = NULL;

	return novaDrzava;
}


int gradoviCmp(positionG grad1, positionG grad2) {
	int res = 0;
	res = grad1->br_stan - grad2->br_stan;

	if (res == 0) {
		res = strcmp(grad1->ime_grada, grad2->ime_grada);
	}

	return res;
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

int delete_list(positionG top) {
	positionG head = top->next;
	positionG temp;

	while (head != NULL) {
		temp = head->next;
		free(head);
		head = temp;
	}

	return EXIT_SUCCESS;
}