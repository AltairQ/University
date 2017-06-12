#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 10000

extern int n;
extern int m;

extern int A[MAX_SIZE];
extern int mniejsze[MAX_SIZE];
extern int rowne[MAX_SIZE];
extern int B[MAX_SIZE];

// io
void input_and_check_data(void);
void output_data(int B[]);

// alg
int* C_K_E(int*, int, int);
int* C_K_L(int*, int);
int* Reorg(int*, int*, int, int);
int* C_S(int*, int, int);

