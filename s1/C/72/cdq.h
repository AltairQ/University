// Mateusz Maciejewski
// Lista 7 zadanie 2
// plik naglowkowy
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>


typedef struct node node;
typedef node *cdq;

cdq cdq_init();

long cdq_size(cdq q);
bool cdq_is_empty(const cdq);

void cdq_erase(cdq *q);

int cdq_push_front(cdq *q, double val);
int cdq_push_back(cdq *q, double val);

double cdq_pop_front(cdq*);
double cdq_pop_back(cdq *q);

cdq cdq_merge(cdq *q1, cdq *q2);
cdq cdq_copy(const cdq q);

void cdq_insert_between(node *n1, node *n2, double val);
void cdq_sorted_insert(cdq *q1, double val);

void cdq_sort_insert(cdq *q);
void cdq_sort_quick(cdq *q);