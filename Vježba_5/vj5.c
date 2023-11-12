#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_LINE 100
//Napisati program koji cita postfiks izraz i zatim koristenjem stoga racuna rezultat. Stog je potrebno realizirati preko vezane liste

struct _postfiks;
typedef struct _postfiks* Pozicija;
typedef struct _postfiks
{
	float broj;
	Pozicija next;
}postfiks;

float mnozi(Pozicija P);
float dijeli(Pozicija P);
float zbroji(Pozicija P);
float oduzmi(Pozicija P);
int unos(int broj, Pozicija P);
int brisi_sve(Pozicija P);
int ispisi_listu(Pozicija P);
Pozicija trazi_prethodni(Pozicija P, int broj);




int main()
{
	char ime_datoteke[MAX_LINE] = { '\0' };
	char buffer[MAX_LINE] = { '\0' };
	char* p = buffer;
	FILE* f = NULL;
	float broj = 0;
	int n = 0;
	char znak = '\0';
	int provjera = 0;
	int provjera_c = 0;
	int br_clanova = 0;
	int provjera_0 = 0;
	Pozicija head = NULL;
	head = (postfiks*)malloc(sizeof(postfiks));
	if (head == NULL)
	{
		printf("\nGreska pri inicijalizaciji memorije");
		return -1;
	}
	head->next = NULL;
	printf("\nUnesite ime datoteke\n");
	provjera = scanf("%s", ime_datoteke);
	if (provjera != 1)
	{
		printf("Krivi znak\n");
		return -1;
	}
	f = fopen(ime_datoteke, "r");
	if (f == NULL)
	{
		printf("Datoteka se nije mogla otvoriti\n");
		return -1;
	}

	while (!feof(f))
	{
		if (fgets(buffer, MAX_LINE, f) != NULL);
		{

			while (strlen(p) > 0)
			{
				provjera = sscanf(p, "%f %n", &broj, &n);
				provjera_c = sscanf(p, "%c", &znak);

				if (provjera == 1)
				{
					printf("\n%f\n", broj);
					unos(broj, head);
					br_clanova++;
				}
				else
				{
					if (provjera_c == 1)
					{
						printf("\n%c\n", znak);
						if (br_clanova < 2)
						{
							printf("Krivi izraz\n");
							return -1;
						}
						else
						{
							switch (znak)
							{
							case '+':
								zbroji(head);
								br_clanova--;

								break;
							case '-':
								oduzmi(head);
								br_clanova--;

								break;
							case '*':
								mnozi(head);
								br_clanova--;

								break;
							case '/':
								provjera_0 = dijeli(head);
								br_clanova--;
								if (provjera_0 == -1)
								{
									brisi_sve(head);
									fclose(f);
									return -1;
								}
								break;
							default:
								printf("Nepoznat znak\n");
								return -1;
								break;
							}
						}
					}
				}
				p = p + n;
			}
		}
	}
	if (br_clanova > 1)
	{
		printf("Krivi izraz\n");
		return -1;
	}
	ispisi_listu(head->next);
	brisi_sve(head);

	fclose(f);
	return 0;
}

int unos(int broj, Pozicija P)
{
	Pozicija q;
	while (P->next != NULL)
	{
		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(postfiks));
	if (q != NULL)
	{
		q->broj = broj;
		P->next = q;
		q->next = NULL;
	}
	else
	{
		printf("Greska pri alokaciji memorije\n");
		return -1;
	}
}
Pozicija trazi_prethodni(Pozicija P, int broj)
{
	while (P->next != NULL && P->next->broj != broj)
	{
		P = P->next;
	}
	return P;
}
float mnozi(Pozicija P)
{
	Pozicija head = P;
	Pozicija temp1 = NULL;
	Pozicija temp2 = NULL;
	float broj = 0;
	while (P->next != NULL)
	{
		P = P->next;
	}
	temp1 = trazi_prethodni(head, P->broj);
	temp2 = trazi_prethodni(head, temp1->broj);
	broj = temp1->broj * P->broj;
	temp2->next = NULL;
	free(P);
	free(temp1);
	printf("\n\n%f", broj);
	unos(broj, head);
	return 1;
}
float dijeli(Pozicija P)
{
	Pozicija head = P;
	Pozicija temp1 = NULL;
	Pozicija temp2 = NULL;
	float broj = 0;
	while (P->next != NULL)
	{
		P = P->next;
	}
	temp1 = trazi_prethodni(head, P->broj);
	temp2 = trazi_prethodni(head, temp1->broj);
	if (P->broj == 0)
	{
		printf("Greska, dijeljenje s 0\n");
		return -1;
	}
	broj = temp1->broj / P->broj;
	temp2->next = NULL;
	free(P);
	free(temp1);
	printf("\n\n%f", broj);
	unos(broj, head);
	return 1;
}
float zbroji(Pozicija P)
{
	Pozicija head = P;
	Pozicija temp1 = NULL;
	Pozicija temp2 = NULL;
	float broj = 0;
	while (P->next != NULL)
	{
		P = P->next;
	}
	temp1 = trazi_prethodni(head, P->broj);
	temp2 = trazi_prethodni(head, temp1->broj);
	broj = temp1->broj + P->broj;
	temp2->next = NULL;
	free(P);
	free(temp1);
	printf("\n\n%f", broj);
	unos(broj, head);
	return 1;
}
float oduzmi(Pozicija P)
{
	Pozicija head = P;
	Pozicija temp1 = NULL;
	Pozicija temp2 = NULL;
	float broj = 0;
	while (P->next != NULL)
	{
		P = P->next;
	}
	temp1 = trazi_prethodni(head, P->broj);
	temp2 = trazi_prethodni(head, temp1->broj);
	broj = temp1->broj - P->broj;
	temp2->next = NULL;
	free(P);
	free(temp1);
	printf("\n\n%f", broj);
	unos(broj, head);
	return 1;
}
int ispisi_listu(Pozicija P)
{
	while (P != NULL)
	{
		printf("\nBROJ: %f\n", P->broj);
		P = P->next;
	}
	return 0;
}
int brisi_sve(Pozicija P)
{
	while (P->next != NULL)
	{
		Pozicija prev = NULL, temp = NULL;
		prev = P;
		temp = prev->next;
		prev->next = temp->next;
		free(temp);
	}
	free(P);
	return 1;
}