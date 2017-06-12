// Mateusz Maciejewski
// Lista 5 Zadanie 2

#include <stdio.h>
#include <stdbool.h>

int n;
int m;

int tab[100];


bool req(int in)
{
	if(in==1)
		return false;


	

	if(tab[in-1] == in)
	{
		if(req(in-1))
		{

			for (int i = in-1; i > 0 ; --i)			
				tab[i]=tab[i-1];			
		
			tab[0]=in;
			return true;

		}
		else
		{
			return false;
		}

	}


	int id;

	for (int i = 0; i < in; ++i)
	{
		if(tab[i]==in)
		{
			id = i;
			break;
		}
		
	}


	if(id != in-1)
	{
		int buf = tab[id+1];
		tab[id+1]=tab[id];
		tab[id]=buf;
		return true;
	}

	return true;


}

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s (size) (number)\n", argv[0] );
		return -1;
	}

	sscanf(argv[1], " %d ", &n);
	sscanf(argv[2], " %d ", &m);

	if (n==1)
	{
		puts("1");

		if (m != 1)
		{
			puts("There are no more magical squares of this size.");			
		}
		return 0;
	}

	if (n==2)
	{
		puts("No magical squares of size 2 exist.");
		return 0;
	}

	for (int i = 0; i < n*n; ++i)
	{
		tab[i]=n*n - i;
	}

	int cnt=0;

	while(cnt < m)
	{
		cnt++;

		for (int i = 0; i < n; ++i)
		{
			for (int ii = 0; ii < n; ++ii)
			{
				printf("%d ", *(tab+i*n+ii) );
			}
			puts("");
		}
		puts("");



		if (req(n*n) == false)
		{
			break;
		}
	}

	return 0;
}