#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char tab[3000];
int P[3000];


char subchar(char in)
{
	switch(in)
	{
		case 'b':
		case 'd':
		case 'p':
			return 'b';

		case 's':
		case 'g':
			return 's';

		case 'c':
		case 'y':
			return 'c';

		default:
			return in;

	}
}

bool eq(char a, char b)
{
	a = subchar(a);
	b = subchar(b);
	return (a == b);
}



bool findpal(int n)
{
int C = 0, R = 0;

for (int i = 1; i < n-1; i++)
{
	int i_mirror = 2*C-i; 

	if(R > i)
	{
		P[i]= (R-i < P[i_mirror])?(R-i):(P[i_mirror]);
	}
	else
	{
		P[i]=0;
	}
	
	while (eq(tab[i + 1 + P[i]],tab[i - 1 - P[i]]))
		P[i]++;		
	
	if (i + P[i] > R)
	{
		C = i;
		R = i + P[i];
	}
}

for (int i = 0; i < n-1; ++i)
	if(P[i]>=3)
		return true;

return false;

}

int main()
{
	int n;
	scanf("%d ", &n);
	int cnt=0;

	while(n--)
	{
		memset(P, 0,3000);
		int i=1;
		tab[0]='^';
		int buf;
		while((buf=getchar()) != '\n' && buf != EOF)
		{
			tab[i++]='-';
			tab[i++]=(char)buf;
		}

		tab[i++]='-';
		tab[i++]='#';

		// printf("%s\n", tab );
		cnt = (findpal(i))?cnt+1:cnt;
	}

	printf("%d\n", cnt);
	
	return 0;
}