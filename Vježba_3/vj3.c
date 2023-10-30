/*3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)

struct _person;
typedef struct _person* position;

typedef struct _person {
	char name[MAX_LINE];
	char lastName[MAX_LINE];
	int birthYear;

	position next;
}person;


int menu();
position CreateNewPerson(char* name, char* lastName, int birthYear);
int InsertAfter(position p, position q);
int PrependList(position p, char* name, char* lastName, int birthYear);
int PrintList(position p);
position FindLast(position p);
int AppendList(position p, char* name, char* lastName, int birthYear);
position FindByLastName(position p, char* lastName);
int DeleteByLastName(position p, position toDelete);
position FindPrevious(position p, position q);
int DeleteList(position p);

int InsertAfterPerson(position p, char* name, char* lastName, int birthYear);
int InsertBeforePerson(position q, position p, char* name, char* lastName, int birthYear, char* lastNameP);
int WriteIntoFile(char* fileName, position p);
int ReadFromFile(char* fileName, position p);
int bubble_sort(position p);

int main(void) {

	person head = { .birthYear = 0, .lastName = {0}, .name = {0}, .next = NULL };

	menu();
	DeleteList(&head);

	return EXIT_SUCCESS;
}

int menu() {

	char name[MAX_LINE] = { 0 };
	char lastName[MAX_LINE] = { 0 };
	int birthYear = 0;
	char lastNameDel[MAX_LINE] = { 0 };
	char lastNameP[MAX_LINE] = { 0 };
	char fileName[MAX_LINE] = { 0 };


	int choice;

	person head = { .birthYear = 0, .lastName = {0}, .name = {0}, .next = NULL };

	position temp = NULL;
	temp = (position)malloc(sizeof(person));

	if (temp == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}



	position q = NULL;
	q = (position)malloc(sizeof(person));

	if (q == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}



	while (1) {

		printf("\nChoose what you want to do:\n");
		printf("1 - Insert a person at the beginning of the list\n");
		printf("2 - Insert a person at the end of the list\n");
		printf("3 - Find a person in the list by last name\n");
		printf("4 - Delete a person with certain last name:\n");
		printf("5 - Insert a person after person with certain last name\n");
		printf("6 - Insert a person before person with certain last name\n");
		printf("7 - Write list into file\n");
		printf("8 - Read list from file\n");
		printf("9 - Print list\n");
		printf("10 - Sort list by LastName\n");
		printf("11 - Exit\n");
		printf("Your choice: ");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			PrependList(&head, name, lastName, birthYear);
			break;

		case 2:
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			AppendList(&head, name, lastName, birthYear);
			break;

		case 3:
			printf("Type in the last name of a person you want to find: ");
			scanf(" %s", lastName);
			temp = FindByLastName(&head, lastName);
			printf("\nPerson you were looking for is: %s %s, %d\n", temp->name, temp->lastName, temp->birthYear);
			break;

		case 4:
			printf("Type in the last name of a person you want to delete: ");
			scanf(" %s", lastNameDel);
			q = FindByLastName(&head, lastNameDel);
			DeleteByLastName(&head, q);
			break;

		case 5:
			printf("Type in the last name of a person you want to insert after: ");
			scanf(" %s", lastNameDel);
			q = FindByLastName(&head, lastNameDel);
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			InsertAfterPerson(q, name, lastName, birthYear);
			break;

		case 6:
			printf("Type in the last name of a person you want to insert before: ");
			scanf(" %s", lastNameP);
			q = FindByLastName(&head, lastNameP);
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			InsertBeforePerson(q, &head, name, lastName, birthYear, lastNameP);
			break;

		case 7:
			printf("Type in file name: ");
			scanf(" %s", fileName);
			WriteIntoFile(fileName, head.next);
			break;

		case 8:
			printf("Type in file name: ");
			scanf(" %s", fileName);
			ReadFromFile(fileName, &head);
			break;

		case 9:
			PrintList(head.next);
			break;

		case 10:
			bubble_sort(&head);
			PrintList(head.next);
			break;

		case 11:
			return EXIT_SUCCESS;
			break;

		default:
			printf("Error, wrong choice!");
			break;
		}

	}

	return EXIT_SUCCESS;
}



position CreateNewPerson(char* name, char* lastName, int birthYear) {

	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(person));

	if (newPerson == NULL)
	{
		printf("Memory not allocated correctly!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(position p, position q)
{
	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int PrependList(position p, char* name, char* lastName, int birthYear) {

	position q = NULL;
	q = CreateNewPerson(name, lastName, birthYear);

	if (q == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	InsertAfter(p, q);



	return EXIT_SUCCESS;
}

int PrintList(position p) {

	if (p == NULL) {
		printf("Nema elemenata, lista je prazna!");
		return FILE_DIDNT_OPEN_ERROR;
	}

	else {
		while (p != NULL) {

			printf("\nName: %s\n", p->name);
			printf("Last name: %s\n", p->lastName);
			printf("Birth year: %d\n", p->birthYear);

			p = p->next;
		}
		return EXIT_SUCCESS;
	}
}

position FindLast(position p) {

	while (p->next != NULL) {
		p = p->next;
	}

	return p;
}

int AppendList(position p, char* name, char* lastName, int birthYear) {
	position q = NULL;
	position last = NULL;

	q = CreateNewPerson(name, lastName, birthYear);

	if (q == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	last = FindLast(p);

	InsertAfter(last, q);

	return EXIT_SUCCESS;
}


position FindByLastName(position p, char* lastName)
{
	while (p != NULL && strcmp(p->lastName, lastName) != 0)
	{
		p = p->next;
	}

	if (p == NULL) {
		printf("There is no that element in the list\n");
	}

	return p;
}

int DeleteByLastName(position p, position toDelete) {
	position temp = NULL;
	position prev = NULL;

	temp = (position)malloc(sizeof(person));
	prev = (position)malloc(sizeof(person));


	if (temp == NULL)
	{
		printf("Memory not allocated correctly!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	if (prev == NULL)
	{
		printf("Memory not allocated correctly!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	temp = toDelete;
	prev = FindPrevious(p, toDelete);

	prev->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

position FindPrevious(position p, position q) {

	position temp = p;

	while (temp != NULL && temp->next != q)
	{
		temp = temp->next;
	}

	return temp;

}

int DeleteList(position p) {
	position temp = p;

	while (temp->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}


int InsertAfterPerson(position p, char* name, char* lastName, int birthYear) {

	position newPerson = NULL;
	newPerson = CreateNewPerson(name, lastName, birthYear);

	if (newPerson == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	InsertAfter(p, newPerson);

	return EXIT_SUCCESS;
}

int InsertBeforePerson(position q, position p, char* name, char* lastName, int birthYear, char* lastNameP) {

	position newPerson = NULL;
	newPerson = CreateNewPerson(name, lastName, birthYear);

	position prev = NULL;
	prev = (position)malloc(sizeof(person));

	if (newPerson == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	prev = FindPrevious(p, q);

	InsertAfter(prev, newPerson);

	return EXIT_SUCCESS;
}

int WriteIntoFile(char* fileName, position p) {

	FILE* fp = NULL;
	fp = fopen(fileName, "w");

	if (fp == NULL) {
		printf("File didn't open correctly!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (p != NULL) {
		fprintf(fp, "%s %s %d\n", p->name, p->lastName, p->birthYear);
		p = p->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;

}

int ReadFromFile(char* fileName, position p) {

	FILE* fp = NULL;
	fp = fopen(fileName, "r");

	char name[MAX_LINE] = { 0 };
	char lastName[MAX_LINE] = { 0 };
	int birthYear = 0;


	if (fp == NULL) {
		printf("File didn't open correctly!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %d\n", name, lastName, &birthYear);
		AppendList(p, name, lastName, birthYear);
	}


	fclose(fp);

	return EXIT_SUCCESS;
}


int bubble_sort(position p) {

	position j, prev_j, temp, end;

	end = NULL;
	while (p->next != end)
	{
		prev_j = p;
		j = p->next;

		while (j->next != end)
		{
			if (strcmp(j->lastName, j->next->lastName) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}
		end = j;
	}

	return EXIT_SUCCESS;
}