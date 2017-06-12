// Mateusz Maciejewski
// Lista 6 zadanie 2
// sortest.c - moduł testujący i funkcje sortujące

#include "sortest.h"

float sortest_2msec(clock_t in)
{
	return 1000.0f*((float)in ) / CLOCKS_PER_SEC; 

}

void sortest_generate_array(double* tab, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		tab[i] = (double)rand();		

}

bool sortest_compare_arrays(double* in, double* out, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		if(in[i] != out[i])
			return false;

	return true;
}

int sortest_double_comp(const void* a, const void* b)
{
	if(*(double*)a  <  *(double*)b )  return -1;
	if(*(double*)a  == *(double*)b )  return  0;
	if(*(double*)a  >  *(double*)b )  return  1;

	return -1;
}

//std qsort
void sortest_qsort(double* tab, size_t size)
{
	qsort((void*)tab, size, sizeof(double), sortest_double_comp);
}

//select sort
void sortest_ssort(double* tab, size_t size)
{
	size_t k;

	for(size_t i = 0; i < size; i++)
	{
		k = i;
		for(size_t j=i+1; j < size; j++ )
			if(tab[j] < tab[k])
				k=j;

		double buf = tab[k];
		tab[k]=tab[i];
		tab[i]=buf;
	}
}

//merge sort
void sortest_msort_merge(double *a, size_t n, size_t m)
{
	size_t i, j, k;
	double* x = malloc(n * sizeof (double));

	for (i = 0, j = m, k = 0; k < n; k++) {
		x[k] = j == n      ? a[i++]
			 : i == m      ? a[j++]
			 : a[j] < a[i] ? a[j++]
			 :               a[i++];
	}

	for (i = 0; i < n; i++)
		a[i] = x[i];
	
	free(x);
}
 
void sortest_msort(double *a, size_t size)
{
	if (size < 2)
		return;

	size_t m = size / 2;
	sortest_msort(a, m);
	sortest_msort(a + m, size - m);
	sortest_msort_merge(a, size, m);
}



//in libc we trust
bool sortest_test_arrays(double* in, double* out, size_t size)
{
	double *buf = malloc(size*sizeof(double));
	memcpy(buf, in, size*sizeof(double));

	sortest_qsort((void*)buf, size);

	bool to_return = sortest_compare_arrays(buf, out, size);
	free(buf);
	return to_return;
}


void sortest_single_test(void (*sort)(double*, size_t), double* tab, size_t size, clock_t* res )
{
	clock_t t0= clock();
	sort(tab, size);
	clock_t delta = clock() - t0;

	res[0] = (res[0] > delta)?delta : res[0];
	res[1] = (res[1] < delta)?delta : res[1];
	res[2] += delta;
}

bool sortest_test(void (*sort)(double*, size_t), double* tab, size_t size, size_t reps, clock_t* res )
{
	double* tab_dirty= (double*) malloc(size*sizeof(double) );

	for (size_t rep_index = 0; rep_index < reps; ++rep_index)
	{	
		sortest_generate_array(tab, size);	
		memcpy(tab_dirty, tab, sizeof(double)*size);
		sortest_single_test(sort, tab_dirty, size, res);
		if(!sortest_test_arrays(tab, tab_dirty, size))
			return false;		
	}

	free(tab_dirty);

	return true;
}


