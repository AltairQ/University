// Mateusz Maciejewski
// 20.11.2016
// Lista 4 Zadanie 2
// plik główny - testy w funkcji main

#include "rational.h"

int main(void)
{
	//the program expects two rational numbers
	puts("please enter two rational numbers:");
	rational a, b, c;
	a= readRational();
	b= readRational();

	puts("sum:");
	c= addRationals(a,b);
	printRational(c);

	puts("difference:");
	c= subRationals(a,b);
	printRational(c);

	puts("product:");
	c= multRationals(a,b);
	printRational(c);

	puts("quotient:");
	c= divRationals(a,b);
	printRational(c);

}