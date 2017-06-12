// Mateusz Maciejewski
// Lista 7 zadanie 1
// modul sprawdzajacy

#include "cdq.h"
#include <stdio.h>

int main()
{
	cdq queue;
	queue=cdq_init();

	int buf;

	while((buf = getchar()) != EOF)
	{
		double x;
		switch(buf)
		{

			case 'F':
			scanf(" %lf ", &x);
			cdq_push_front(&queue, x);
			break;

			case 'B':
			scanf(" %lf ", &x);
			cdq_push_back(&queue, x);
			break;

			case 'T':
			printf("%lf\n", cdq_pop_front(&queue) );
			break;

			case 'Y':
			printf("%lf\n", cdq_pop_back(&queue) );
			break;

			case 'S':
			printf("%ld\n", cdq_size(queue));
			break;
		}
	}


	return 0;
}