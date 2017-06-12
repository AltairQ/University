// Mateusz Maciejewski
// 20.11.2016
// Lista 4 Zadanie 2
// definicje funkcji

#include "rational.h"

long gcd(long a, long b)
{
	while(b!=0)
	{
		long c = b;
		b = a%b;
		a=c;
	}

	return a;
}

long* getNumPtr(rational* in)
{
	return (((long*)in)+1);
}

long* getDenPtr(rational* in)
{
	return (((long*)in));
}


rational toRational(long a, long b)
{
	rational res;

	long c = gcd(a, b);

	a=a/c;
	b=b/c;

	*getNumPtr(&res) = (b<0)?-a:a;
	*getDenPtr(&res) = (b<0)?-b:b;

	return res;
}

rational addRationals(rational a, rational b)
{
	return toRational( (*getNumPtr(&a)) * (*getDenPtr(&b))
	 					+ (*getNumPtr(&b)) * (*getDenPtr(&a)),
	 					  (*getDenPtr(&a))*(*getDenPtr(&b)));
}

rational subRationals(rational a, rational b)
{
	*getNumPtr(&b) = -(*getNumPtr(&b));
	return addRationals(a, b);
}

rational multRationals(rational a, rational b)
{
	return toRational((*getNumPtr(&a)) * (*getNumPtr(&b)), (*getDenPtr(&a)) * (*getDenPtr(&b)));
}

rational divRationals(rational a, rational b)
{
	if(*getDenPtr(&b) == 0)
		return toRational(0,1); //no exceptions in C 

	long buf;
	buf = *getNumPtr(&b);
	*getNumPtr(&b) = *getDenPtr(&b);
	*getDenPtr(&b) = buf;

	return multRationals(a, b); 
}

void printRational(rational a)
{
	printf("%ld/%ld\n", *getNumPtr(&a), *getDenPtr(&a) );
}

rational readRational(void)
{
	long a;
	long b;
	scanf("%ld/%ld", &a, &b);

	if(b==0)
		return toRational(0,1); //no exceptions in C

	return toRational(a, b);
}