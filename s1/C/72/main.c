// Mateusz Maciejewski
// Lista 7 zadanie 2
// modul sprawdzajacy

#include <stdio.h>
#include "cdq.h"

int main()
{
	cdq queue;
	queue=cdq_init();

	cdq queue2;
	queue2=cdq_init();

	int buf;
	cdq q_buf;

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
			printf("%.2lf\n", cdq_pop_front(&queue) );
			break;

			case 'Y':
			printf("%.2lf\n", cdq_pop_back(&queue) );
			break;

			case 'S':
			printf("%ld\n", cdq_size(queue));
			break;

			case 'X': //exchange
			q_buf = queue;
			queue = queue2;
			queue2 = q_buf;
			break;

			case 'M': //merge
			queue = cdq_merge(&queue, &queue2);
			break;

			case 'C': //copy
			cdq_erase(&queue2);
			queue2 = cdq_copy(queue);
			break;

			case 'I': //sorted insert
			scanf(" %lf ", &x);
			cdq_sorted_insert(&queue, x);
			break;

			case '1': //insertion sort
			cdq_sort_insert(&queue);
			break;

			case '2': //quick sort
			cdq_sort_quick(&queue);
			break;

			case 'D': //dump
			puts("");

			while(!cdq_is_empty(queue))
				printf("%.2lf ", cdq_pop_front(&queue) );
			puts("");

			break;

		}
	}


	return 0;
}