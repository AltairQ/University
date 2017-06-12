#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int x, d, n, *tab;

int counter;

void req(int pos, int sum, int min, int max)
{
	if(sum > x)
		return;

	if (max - min > d)
		return;

	if (pos == n) //we go from 0 so @n we have nothing to do
	{	
		if(sum==x)
			counter++; //we arrived here and the sequence is good

		return;
	}

	for (int i = 0; sum + i*tab[pos] <= x+1; ++i)
	{
		req(pos+1, sum + i*tab[pos], (i<min)?i:min , (i>max)?i:max  );		
	}
	

}


int main()
{
	scanf("%d %d %d ", &x, &d, &n );


	tab = malloc((unsigned int)n*sizeof(int));

	for (int i = 0; i < n; ++i)
		scanf("%d ", tab+i);

	
	for (int i = 0; i*tab[0] <= x; ++i)
		req(1, i*tab[0], i, i);

	printf("%d\n", counter);

	
	
	return 0;
}