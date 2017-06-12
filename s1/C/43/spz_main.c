#include "f-protot.h"

int main()
{
 	input_and_check_data();

 	puts("Tablica nieposortowana:\n");
 	output_data(A);

 	puts("\nTablica posortowana:\n");
 	output_data(C_S(A, n, m));

 	
	return 0;
}