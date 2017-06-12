//Mateusz Maciejewski
//lista zadan 3 zadanie 2
//3.11.2016
#include <stdio.h>
#include <stdbool.h>

//global stream position
int lpos = 1; //line number
int cpos = 0; //character number

//global counter
size_t tab[4];

int ntclsd_lpos; //not closed position
int ntclsd_cpos; 

int fetchIt()
{
	int buf;

	int lc = lpos;
	int cc = cpos;

	// ( = 1
	// [ = 2
	// { = 3
	// opposite = negative

	while((buf=getchar()) !=EOF )
	{
		int mycode;

		cc++;

		switch(buf)
		{
			case '(': mycode =  1; break;
			case ')': mycode = -1; break;
			case '[': mycode =  2; break;
			case ']': mycode = -2; break;
			case '{': mycode =  3; break;
			case '}': mycode = -3; break;
			case '\n':mycode =  0; break;
			default:  mycode =  4; //whatever
		}

		if(mycode == 0)
		{
			lc++;
			cc=0;
		}
		
		if(mycode !=0 && mycode != 4)
		{
			lpos = lc;
			cpos = cc;
			return mycode;
		}
	}

	//if EOF
	return 0;
}

void perr(int a, int b)
{
	printf("%d %d\n", a, b);
}


int inside(int my_code)
{
	tab[my_code]++;
	int my_lpos = lpos;
	int my_cpos = cpos;

	while(true)//unless something happens that is
	{
		int fetch_res = fetchIt();
		
		if(fetch_res == 0) //EOF, abort
		{
			perr(my_lpos, my_cpos); //print that we are bad
			tab[my_code]--;
			return 0; //pass EOF back
		}

		if(fetch_res > 0)// if found opening
		{
			int c_res = inside(fetch_res);

			if(c_res==0) // if EOF
			{
				perr(my_lpos, my_cpos);
				tab[my_code]--;
				return 0;
			}

			if(c_res < 0)// if found unhandled closing
			{
				if(c_res == -my_code)
				{
					tab[my_code]--;
					return 16; //ok, we handled it
				}
				else
				{
					perr(my_lpos, my_cpos);
					tab[my_code]--;
					return c_res;
				}
			}
		}

		if(fetch_res < 0)// if found closing
		{
			if(fetch_res == -my_code) //found our one
			{
				tab[my_code]--;
				return 16; // all good
			}
			else
			{
				if(tab[fetch_res]>0) //there is some chance of recovery
				{
					perr(my_lpos, my_cpos); // didn't found our one	
					ntclsd_cpos = cpos;
					ntclsd_lpos = lpos;
					tab[my_code]--;			
					return fetch_res; //pass it back
				}
				else
				{
					perr(lpos, cpos);
				}

			}
		}


	}	
	
	

}


int main()
{
	int my_lpos;
	int my_cpos;

	while(true) //just like top-level "inside"
				//we can handle only openings
	{
		int res = fetchIt();
		my_lpos = lpos;
		my_cpos = cpos;
	
		switch(res)
		{
			case 0:
			return 0; break; //EOF

			case 1://(
			case 2://[
			case 3://{
			if(inside(res)<0)
			perr(ntclsd_lpos, ntclsd_cpos);
			 break;

			case -1://)
			case -2://]
			case -3://}
			perr(my_lpos, my_cpos); break;
		}
	}

	return 0;
}