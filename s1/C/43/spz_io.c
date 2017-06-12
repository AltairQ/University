#include "f-protot.h"

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