// Mateusz Maciejewski
// Lista 6 zadanie 2
// sortest.h - interfejs modułu, załączenie nagłówków

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//generator losowej tablicy
void sortest_generate_array(double*, size_t);
//test czy out jest posortowaną wersją in
bool sortest_test_arrays(double* in, double* out, size_t size);

//konwersja z c_time na milisekundy(float)
float sortest_2msec(clock_t in);

//wrapper do std quick sorta
void sortest_qsort(double*, size_t );
//select sort
void sortest_ssort(double*, size_t );
//merge sort
void sortest_msort(double*, size_t );


//pojedynczy test
void sortest_single_test(void (*sort)(double*, size_t), double*, size_t , clock_t* );
//generator liczby (reps) testów i nadzorca
bool sortest_test(void (*sort)(double*, size_t), double* tab, size_t size, size_t reps, clock_t* res );
