//Mateusz Maciejewski
#include <stdio.h>

int main(void)
{
	int n;
	scanf("%d", &n);

	if(n==0)
	{
		puts("0^1");
		return 0;	
	}

	if(n==1)
	{
		puts("1^1");
		return 0;
	}

	int dv=2, dcount=0;
	char first=1;

	while(n!=1)
	{
		if(n%dv==0)
		{
			n/=dv;
			dcount++;
		}
		else
		{
			if(dcount!=0)
			{
				if(first==0)
					printf("*");
				
				printf("%d^%d", dv, dcount);
				first = 0;
				
			}
			dv++;
			dcount=0;
		}
	}

	if(dcount!=0)
	{
		if(first==0)
		{
			printf("*");
			first = 0;
		}				
		printf("%d^%d", dv, dcount);
		
	}
	puts("");

	return 0;
}