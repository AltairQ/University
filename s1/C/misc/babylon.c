#include <stdio.h>

int main(int argc, char const *argv[])
{
	int sq;
	scanf("%d", &sq);
	double a=sq/2;

	for (int i = 0; i < 1000; ++i)
	{		
		a = (a + (double)sq/a)/2;		
	}

	printf("%lf\n",a );

	return 0;
}