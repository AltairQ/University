// Mateusz Maciejewski
// 20.11.2016
// Lista 4 Zadanie 2
// plik nagłówkowy

#include <stdio.h>
#include <stdbool.h>

typedef long long int rational;

long gcd(long a, long b);
long* getNumPtr(rational* in);
long* getDenPtr(rational* in);

void printRational(rational a);
rational readRational(void);

rational toRational(long a, long b);

rational addRationals(rational a, rational b);
rational multRationals(rational a, rational b);
rational subRationals(rational a, rational b);
rational divRationals(rational a, rational b);
