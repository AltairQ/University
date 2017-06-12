#include <stdio.h>
#include <stdbool.h>

int size;
char tab[20][20];

bool fetchAndSetSize()
{
	int buf;
	while((buf=getchar()) != EOF)
	{
		if(buf == 'S')
		{
			if((buf=getchar()) == EOF)
				return false;

			if(buf=='Z')
			{
				scanf("[%d]", &size);
				return true;
			}
		}

	}

	return false;
}

bool fetchAndApplyMove()
{
	int buf;
	while((buf=getchar()) != EOF)
	{
		if(buf == ';')
		{
			if((buf=getchar()) == EOF)
				return false;

			char a, b;
			if(scanf("[%c%c",&b,&a) != 2)//inverted because why not
				return false;

			int buf2=getchar(); //fix for malformed data
			if(buf2!=']')
				return true;

			int x, y;

			x=(a-'a'<0)?a-'A':a-'a';
			y=(b-'a'<0)?b-'A':b-'a';

			if(x<0 || y<0 || x>=size || y>=size)
				return false;


			tab[x][y]=(char)buf; //we hope it's a real char

			return true;


		}

	}

	return false;
}

void printBoard(void)
{
	printf("  ");
	for (char i = 0; i < size; ++i)
	{
		printf("%c ", 'A'+i);
	}
	puts("");

	int maxWcount=0;
	int maxBcount=0;

	for (int i = 0; i < size; ++i)
	{
		printf("%c ", 'A'+i);
		int curWcount=0;
		int curBcount=0;
		for (int ii = 0; ii < size; ++ii)
		{
			char toprint;
			switch(tab[i][ii])
			{
				case 'B': curBcount++; toprint='X'; break;
				case 'W': curWcount++; toprint='O'; break;
				default: toprint='.'; break;
			}
			printf("%c ",toprint);
		}
		maxBcount=(maxBcount>curBcount)?maxBcount:curBcount;
		maxWcount=(maxWcount>curWcount)?maxWcount:curWcount;

		puts("");
	}
	printf("%d %d\n", maxBcount, maxWcount );
}

int main()
{
	if(!fetchAndSetSize())
		return -1;

	while(fetchAndApplyMove());

	printBoard();


	return 0;
}