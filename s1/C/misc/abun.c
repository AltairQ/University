#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned int ui;

bool isAbun(ui in)
{
	ui sum = 1;

	for(ui i = 2; i*i <= in; i++ )
	{
		if(in%i==0)
		{
			if(i*i == in)
				sum+=i;
			else
				sum+= i + in/i;
	
			if(sum > INT_MAX)
				return true;
		}
	}

	return (sum>in)?true:false;

}


int main(void)
{
	int m;
	scanf("%d", &m);
	bool feven=false;
	bool fodd=false;

	int even=(m%2==0)? m+2 : m+1;

	if(even<1)
		goto nope1;

	
	while(even < INT_MAX-1)
	{
		if(isAbun((ui)even))
		{
			printf("%d ",even);
			feven = true;
			break;
		}
		even+=2;
	}
	nope1:
	if(!feven)
		printf("BRAK ");

	int odd=(m%2==1)? m+2 : m+1;
	if(odd<1)
		goto nope2;
	
	while(odd < INT_MAX-1)
	{
		if(isAbun((ui)odd))
		{
			printf("%d\n",odd);
			fodd = true;
			break;
		}
		odd+=2;
	}

	nope2:
	if(!fodd)
		printf("BRAK\n");

	return 0;
}
