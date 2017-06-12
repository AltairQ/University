#include "f-protot.h"

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




