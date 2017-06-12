//Mateusz Maciejewski
//Lista 4 Zadanie 3
//sklejenie modułów 

//f-protot.h ======================================================
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 10000

// extern int n;
// extern int m;

// extern int A[MAX_SIZE];
// extern int mniejsze[MAX_SIZE];
// extern int rowne[MAX_SIZE];
// extern int B[MAX_SIZE];

// io
void input_and_check_data(void);
void output_data(int*);

// alg
int* C_K_E(int*, int, int);
int* C_K_L(int*, int);
int* Reorg(int*, int*, int, int);
int* C_S(int*, int, int);

//end f-protot.h ======================================================


//spz_io.c ======================================================

int n;
int m;

int A[MAX_SIZE];


void input_and_check_data(void)
{
	scanf("%d %d", &n, &m);

	if(n < 1 || n > MAX_SIZE)
	{
		printf("\nError: size of input table out of range;\n" 
			   " must be between 1 and %d (inclusive).\n", MAX_SIZE);
		exit(0);
	}

	if(m < 1 || m > n )
	{
		printf("\nError: cardinality of key set out of range;\n"
			   " must be between 1 and %d (inclusive).\n", n);
		exit(0);
	}

	for (int i = 0; i < n; ++i)
	{
		int buf;
		scanf("%d", &buf);
		if(buf >= m || buf < 0)
		{
			printf("\nError: value of element of input data out of range;\n"
				   " must be between 0 and %d (inclusive).\n", m-1);
			exit(0);
		}
		A[i]=buf;

	}


}

void output_data(int B[])//shadow, ale tak kazali 
{
	for (int i = 0; i < n; ++i)
		printf("%d ", B[i]);
	
	puts("");
}
//end spz_io.c ======================================================

//spz_alg.c
int rowne[MAX_SIZE];
int mniejsze[MAX_SIZE];
int B[MAX_SIZE];
int nastepny[MAX_SIZE];

int* C_K_E(int* A, int n, int m)//znowu shadow
{
	for (int i = 0; i < m; ++i)
		rowne[i]=0;

	for (int i = 0; i < n; ++i)
	{
		int klucz = A[i];
		rowne[klucz]++;
	}

	return rowne;
	
}

int* C_K_L(int* rowne, int m)
{
	mniejsze[0]=0;

	for (int i = 1; i < m; ++i)
	{
		mniejsze[i] = mniejsze[i-1] + rowne[i-1];		
	}

	return mniejsze;
}

int* Reorg(int* A, int* mniejsze, int n, int m)
{
	int klucz, indeks;

	for (int i = 0; i < m; ++i)
		nastepny[i] = mniejsze[i];

	for (int i = 0; i < n; ++i)
	{
		klucz = A[i];
		indeks = nastepny[klucz];
		B[indeks] = A[i];
		nastepny[klucz]++;
	}

	return B;	
	
}

int* C_S(int* A, int n, int m)
{
	int *rowne = C_K_E(A, n, m);
	int *mniejsze = C_K_L(rowne, m);
	int *B = Reorg(A, mniejsze, n, m);
	return B;
}
//end spz_alg.c ======================================================

//spz_main.c

int main()
{
 	input_and_check_data();

 	puts("Tablica nieposortowana:\n");
 	output_data(A);

 	puts("\nTablica posortowana:\n");
 	output_data(C_S(A, n, m));

 	
	return 0;
}
//end spz_main.c ======================================================
