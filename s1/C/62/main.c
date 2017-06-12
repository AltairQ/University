// Mateusz Maciejewski
// Lista 6 zadanie 2
// main.c - uruchomienie testów i zwrócenie wyników

#include "sortest.h"
#include <stdio.h>

const size_t alg_count = 3;
char* alg_names[3] = {"select sort", "merge sort", "std qsort"};
void (*alg_fptrs[3])(double*, size_t ) = {sortest_ssort, sortest_msort, sortest_qsort};

int main()
{
	size_t lengths[] = {5000, 10000, 50000 };

	size_t number = 3;
	size_t reps = 100;

	size_t current_array_size=lengths[0];

	double *tab = malloc(lengths[0]*sizeof(double));

	srand((unsigned int)time(NULL));



	for (size_t i = 0; i < number; ++i)
	{
		if(current_array_size != lengths[i])
		{
			tab= (double*) realloc(tab, lengths[i]*sizeof(double) );
			current_array_size = lengths[i];
		}

		puts("Current test size:");
		printf("%ld\n\n", (long)lengths[i] );
		puts("name\t\t\tmin(ms)\t\tmax(ms)\t\tavg(ms)");

		for (size_t alg_index = 0; alg_index < alg_count; ++alg_index)
		{
			printf("%s\t\t", alg_names[alg_index] );

			clock_t res[3]={INT_MAX, 0, 0};		
	
			if(!sortest_test(alg_fptrs[alg_index], tab, current_array_size, reps, res))
			{
				puts("sort error!");
				return -1;
			}
	
			printf("%.2f \t\t%.2f \t\t %.2f\n",
							sortest_2msec(res[0]),
							sortest_2msec(res[1]),
							sortest_2msec(res[2])/ (float)reps ) ;
	
			
		}
		puts("---------------------------------------------\n");


	}

	free(tab);
	
	return 0;
}