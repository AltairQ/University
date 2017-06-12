//Mateusz Maciejewski
//lista 1 zadanie 2
//2016.10.17
#include <stdio.h>
#include <stdlib.h>

int *tab;

int gcd(int a, int b)
{
	int c;
	while(b!=0)
	{
		c=a%b;
		a=b;
		b=c;
	}

	return a;
}

int decshift(int in)
{
	int a=0, b=0;
	while(in%2==0)
	{
		++a;
		in/=2;
	}

	while(in%5==0)
	{
		++b;
		in/=5;
	}

	return (a>b)?a:b;

}


int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int bgcd = gcd(n, m); //skracam ułamek
	n/=bgcd;
	m/=bgcd;

	printf("%d.",n/m); //ułamek niewłaściwy
	n=n%m;

	if(n==0) //gdy nie ma mantysy
	{
		puts("0");
		return 0;
	}

	int x = decshift(m); //max z liczby 2 i 5
	int r = n%m;
	int index = 0;

	for(int i =0; i<x; i++) //wyznacz częśc nieokresową
	{
		r*=10;
		printf("%d", r/m);
		r%=m;
		if(r%m==0) //żeby nie generowac okresu (0)
			return 0;
	}

	tab = malloc(sizeof(int)*(size_t)(m+x+10));

	printf("("); //początek okresu

	for(;;) //wyznacz czesc okresowa
	{
		r*=10;
		for(int i = 0; i < index; ++i) //czy reszta juz wystapila
			if(tab[i]==r%m)
			{
				printf(")"); //zakoncz okres
				return 0;
			}

		printf("%d",r/m);
		r%=m;
		tab[index++]=r;	//zapis reszte
	}
	return 0;
}