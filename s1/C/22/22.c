//Mateusz Maciejewski
//lista 2 zadanie 2
//wersja poprawiona (po przeczytaniu ze zrozumieniem tresci)
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char const **argv)
{
	if(argc <= 1)
	{
		puts("Brak argumentow");
		return 1;
	}

	for(int argind =1; argind<argc; ++argind)
	{
		int a, b;
		if(sscanf(argv[argind], "%d-%d", &a, &b)==1)
			b=a;

		int wind=0;
		bool waswhite=true;
		bool first = true;

		while(true)
		{
			int x = getc(stdin);

			if(x==EOF)
				return 0;

			if(x=='\n')
				break;

			if(x==' ' || x=='\t')
			{
				if(waswhite==false && !first)
					putc(' ',stdout);

				waswhite=true;
			}

			if(x!=' ')
				if(waswhite)
				{
					waswhite=false;
					++wind;
				}

			if(!waswhite && a<=wind && wind<=b)
			{
				putc(x, stdout);
				first=false;
			}
				
		}

		putc("\n",stdout);

	}

	return 0;
}