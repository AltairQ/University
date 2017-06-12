// Mateusz Maciejewski
// Lista 7 zadanie 1
// plik naglowkowy

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

typedef struct node node;
typedef node *cdq;

cdq cdq_init();

size_t cdq_size(cdq q);
bool cdq_is_empty(const cdq);

int cdq_push_front(cdq *q, double val);
int cdq_push_back(cdq *q, double val);

double cdq_pop_front(cdq*);
double cdq_pop_back(cdq *q);
