/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)



struct _polinom;
typedef struct _polinom* position;

typedef struct _polinom {
    int koef;
    int eksp;
    position next;
}polinom;


int readFromFile(position p1, position p2, char* fileName);
position createNewPoli(int koef, int eksp);
int insertSort(position p, int koef, int eksp);
int insertAfter(position p, position q);
int printPoliList(position p);
int polyAdd(position add, position p1, position p2);
int deleteAfter(position p);
int polyMult(position multy, position p1, position p2);

int main(void) {

    polinom p1 = { .koef = 0, .eksp = {0}, .next = NULL };
    polinom p2 = { .koef = 0, .eksp = {0}, .next = NULL };
    polinom resAdd = { .koef = 0, .eksp = {0}, .next = NULL };
    polinom resMult = { .koef = 0, .eksp = {0}, .next = NULL };

    char fileName[MAX_FILE_NAME] = { 0 };

    printf("Type in file name: ");
    scanf(" %s", fileName);
    readFromFile(&p1, &p2, fileName);

    printf("Polinom 1: ");
    printPoliList(p1.next);
    printf("Polinom 2: ");
    printPoliList(p2.next);

    polyAdd(&resAdd, &p1, &p2);
    printf("Result of add function: ");
    printPoliList(resAdd.next);

    polyMult(&resMult, &p1, &p2);
    printf("Result of multyply function: ");
    printPoliList(resMult.next);

    printf("==================================\n");
    if (Delete(p1.next) == 0) {
        printf("Successful memory cleaning p1!");
        printf("\n");
    }
    if (Delete(p2.next) == 0) {
        printf("Successful memory cleaning p2!");
        printf("\n");
    }
    if (Delete(resAdd.next) == 0) {
        printf("Successful memory cleaning resAdd!");
        printf("\n");
    }
    if (Delete(resMult.next) == 0) {
        printf("Successful memory cleaning resMult!");
        printf("\n");
    }

    return EXIT_SUCCESS;
}



int readFromFile(position p1, position p2, char* fileName) {

    FILE* fp = NULL;
    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", fileName);
        return FILE_DIDNT_OPEN_ERROR;
    }


    char buffer[MAX_LINE] = { 0 };
    char* ptr = buffer;
    int koef = 0;
    int eksp = 0;
    int n = 0;
    int counter = 1;

    while (!feof(fp)) {

        fgets(ptr, MAX_LINE, fp);

        while (strlen(ptr) > 0)
        {
            sscanf(ptr, "%d %d %n", &koef, &eksp, &n);
            if (counter == 1) {
                if (koef != 0)
                    insertSort(p1, koef, eksp);
            }
            else if (counter == 2) {
                if (koef != 0)
                    insertSort(p2, koef, eksp);
            }
            ptr += n;

        }
        counter++;
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

position createNewPoli(int koef, int eksp)
{
    position new = NULL;
    new = (position)malloc(sizeof(polinom));

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    new->koef = koef;
    new->eksp = eksp;
    new->next = NULL;

    return new;
}


int insertSort(position p, int koef, int eksp) {

    position new = NULL;
    new = createNewPoli(koef, eksp);

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    if (p == NULL || eksp < p->eksp) {
        new->next = p;
        p = new;
    }

    else {

        position temp = p;
        while (temp->next != NULL && temp->next->eksp < eksp) {
            if (temp->next->koef == 0) {
                deleteAfter(temp);
            }
            temp = temp->next;
        }
        if (temp->next != NULL && temp->next->eksp == eksp) {
            if (temp->next->koef == -koef)
                deleteAfter(temp);
            else
                temp->next->koef += koef;
        }

        else {
            insertAfter(temp, new);
        }

    }

    return EXIT_SUCCESS;
}

int insertAfter(position p, position q)
{
    q->next = p->next;
    p->next = q;

    return EXIT_SUCCESS;
}

int printPoliList(position p) {

    if (p == NULL) {
        printf("No polynomials!");
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (p != NULL) {

        printf(" %dx^%d ", p->koef, p->eksp);
        if (p->next != NULL) {
            if (p->next->koef >= 0)
                printf("+");
            else
                printf("");
        }

        p = p->next;
    }
    printf("\n");


    return EXIT_SUCCESS;
}

int deleteAfter(position p) {
    position toDel = NULL;

    toDel = p->next;
    p->next = p->next->next;
    free(toDel);

    return EXIT_SUCCESS;
}



int polyAdd(position add, position p1, position p2)
{
    position pt1 = p1->next;
    position pt2 = p2->next;


    while (pt1 != NULL && pt2 != NULL) {

        if (pt1->eksp == pt2->eksp) {
            insertSort(add, pt1->koef + pt2->koef, pt1->eksp);
            pt1 = pt1->next;
            pt2 = pt2->next;
        }

        else if (pt1->eksp > pt2->eksp) {
            insertSort(add, pt1->koef, pt1->eksp);
            pt1 = pt1->next;
        }

        else if (pt1->eksp < pt2->eksp) {
            insertSort(add, pt2->koef, pt2->eksp);
            pt2 = pt2->next;
        }

    }
    while (pt1 != NULL) {
        insertSort(add, pt1->koef, pt1->eksp);
        pt1 = pt1->next;
    }
    while (pt2 != NULL) {
        insertSort(add, pt2->koef, pt2->eksp);
        pt2 = pt2->next;
    }



    return EXIT_SUCCESS;
}

int polyMult(position multy, position p1, position p2)
{
    position i = NULL;
    position j = NULL;

    int koeficijent = 0;
    int eksponent = 0;

    if (p1->next == NULL || p2->next == NULL)
        return EXIT_SUCCESS;

    for (i = p1->next; i != NULL; i = i->next) {
        for (j = p2->next; j != NULL; j = j->next)
        {
            koeficijent = i->koef * j->koef;
            eksponent = i->eksp + j->eksp;

            insertSort(multy, koeficijent, eksponent);

        }
    }

    return EXIT_SUCCESS;
}


int Delete(position p) {
    position head = p;
    position temp;

    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }

    return EXIT_SUCCESS;
}