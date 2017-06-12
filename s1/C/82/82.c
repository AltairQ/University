#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct node node;

struct node
{
	node *a;
	node *b;
	node *c;
	node *d;
	bool type; //is leaf
	int val;	
};

node* qtr_from_point(node* tree, int n, int x, int y)
{
	if(x < n/2)
	{
		if (y < n/2)
			return tree->a;
		else
			return tree->d;
	}
	else
	{
		if (y < n/2)
			return tree->b;
		else
			return tree->c;
	}

	return NULL;
}

node *qtr_from_char(node* tree, char in)
{
	if(tree->type)
	{
		#ifdef DEBUGOWN
		puts("qtr_from_char leaf!!!");
		#endif

		return NULL;
	}

	in = (char)tolower((int)in);

	switch(in)
	{
		case 'a':
			return tree->a;
		break;

		case 'b':
			return tree->b;
		break;

		case 'c':
			return tree->c;
		break;

		case 'd':
			return tree->d;
		break;

		default:
		#ifdef DEBUGOWN
		puts("qtr_from_char illegal character!");
		#endif

		return NULL;

	}

}

node* req_tree_alloc(int n)
{
	node* tmp = malloc(sizeof(node));

	if (tmp == NULL)
	{
		#ifdef DEBUGOWN
		puts("fatal malloc error!");
		#endif

		return NULL;		
	}

	if(n==1)
	{
		tmp->val = 0;
		tmp->type= true;
		tmp->a = NULL;
		tmp->b = NULL;
		tmp->c = NULL;
		tmp->d = NULL;
		return tmp;
	}

	tmp->type = false;
	tmp->val = 0;	

	tmp->a = req_tree_alloc(n/2);
	tmp->b = req_tree_alloc(n/2);
	tmp->c = req_tree_alloc(n/2);
	tmp->d = req_tree_alloc(n/2);


	return tmp;
}


void point_to_cmd(int n, int x, int y, char* cmd)
{
	while(n!=1)
	{
		x %= n;
		y %= n;

		if(x < n/2)
		{
			if (y < n/2)
				*cmd = 'a';
			else
				*cmd = 'd';
		}
		else
		{
			if (y < n/2)
				*cmd = 'b';
			else
				*cmd = 'c';
		}

		n/=2;
		cmd++;
	}

	*cmd=0;

}


node* ptr_from_point(node* tree, int n, int x, int y)
{
	if(x>= n || y>= n)
	{
		#ifdef DEBUGOWN
		puts("ptr_from_point out of bounds!");
		#endif

		return NULL; //meh;
	}

	if(n==1 || tree->type)
		return (tree);

	return ptr_from_point(qtr_from_point(tree, n, x, y ), n/2, x % (n/2), y % (n/2));

}

node* ptr_from_cmd(node* tree, char* cmd)
{
	if(*cmd == 0x0)
		return tree;

	return ptr_from_cmd(qtr_from_char(tree, *cmd), cmd+1);
}

void rotate(node *tree, int n, char* cmd)
{
	if(*cmd == 0x0)
	{
		node* tmp1, * tmp2;
	
		tmp1 = tree->b;
		tree->b = tree->a;

		tmp2 = tree->c;
		tree->c = tmp1;

		tree->a = tree->d;
		tree->d = tmp2;
		return;

	}

	rotate(qtr_from_char(tree, *cmd), n/2, cmd+1);
	return;

}

int negate(node *tree, int n, char* cmd)
{
	if(*cmd != 0x0)
	{
		int buf = negate(qtr_from_char(tree, *cmd), n/2, cmd+1);
		tree->val +=buf;		
		return buf;
	}
	

	if(tree->type)
	{
		tree->val = (tree->val == 0)?1:0;
		return (tree->val==0)?-1:1;
	}

	int buf=0;

	buf += negate(tree->a, n/2, cmd);
	buf += negate(tree->b, n/2, cmd);
	buf += negate(tree->c, n/2, cmd);
	buf += negate(tree->d, n/2, cmd);

	tree->val += buf;
	return buf;
}

int zero(node *tree, int n, char* cmd)
{
	if(*cmd != 0x0)
	{
		int buf = zero(qtr_from_char(tree, *cmd), n/2, cmd+1);
		tree->val -= buf;
		return buf;
	}
	

	if(tree->type)
	{
		bool incr= (tree->val == 1);
		tree->val = 0;

		return (incr)?1:0;
	}

	int adj=0;

	adj += zero(tree->a, n/2, cmd);
	adj += zero(tree->b, n/2, cmd);
	adj += zero(tree->c, n/2, cmd);
	adj += zero(tree->d, n/2, cmd);

	tree->val -= adj;

	return adj;

}

int ones(node *tree, int n, char* cmd)
{
	if(*cmd != 0x0)
	{
		int buf = ones(qtr_from_char(tree, *cmd), n/2, cmd+1);
		tree->val += buf;
		return buf;
	}
	

	if(tree->type)
	{
		bool incr= (tree->val == 0);
		tree->val = 1;

		return (incr)?1:0;
	}

	int adj=0;

	adj += ones(tree->a, n/2, cmd);
	adj += ones(tree->b, n/2, cmd);
	adj += ones(tree->c, n/2, cmd);
	adj += ones(tree->d, n/2, cmd);

	tree->val += adj;

	return adj;

}


int variety(node *tree, int n, char* cmd)
{
	if(*cmd != 0x0)
		return variety(qtr_from_char(tree, *cmd), n/2, cmd+1);

	if(tree->type)
		return 1;


	if(tree->val == n*n || tree->val == 0)
		return 1;


	int adj=0;

	adj += variety(tree->a, n/2, cmd);
	adj += variety(tree->b, n/2, cmd);
	adj += variety(tree->c, n/2, cmd);
	adj += variety(tree->d, n/2, cmd);

	return adj;	

}

int check(node *tree, int n, char* cmd)
{
	if(*cmd != 0x0)
		return check(qtr_from_char(tree, *cmd), n/2, cmd+1);

	if (tree->type)
		return 0;

	int qsu = (n/2)*(n/2);

	if ((tree->a->val == 0 && tree->c->val==0 && tree->b->val == qsu && tree->d->val==qsu ) ||
		(tree->b->val == 0 && tree->d->val==0 && tree->a->val == qsu && tree->c->val==qsu ))
	{
		return 1;
	}

	qsu=0;
	qsu += check(tree->a, n/2, cmd);
	qsu += check(tree->b, n/2, cmd);
	qsu += check(tree->c, n/2, cmd);
	qsu += check(tree->d, n/2, cmd);

	return qsu;


}

int main()
{
	#ifdef DEBUGOWN
	puts("!!!!!!  debugOWN mode  !!!!!!");
	#endif

	//eat the "P1\n"
	getchar();
	getchar();
	getchar();

	char cmd_tab[20];
	char* cmd = (char*)cmd_tab;

	int n;
	scanf("%d ", &n);
	scanf("%d ", &n);

	node* tree = req_tree_alloc(n);

	for (int i = 0; i < n; ++i)
	{
		for (int ii = 0; ii < n; ++ii)
		{
			point_to_cmd(n, ii, i, cmd);

			if(getchar()=='1')
			{
				ones(tree, n, cmd);
			}
			else
			{
				zero(tree, n, cmd);
			}
		}

		getchar(); //eat the '\n'
	}



	int buf, buf2;


	while((buf=getchar()) != EOF)
	{
		if(buf=='\n')
			continue;

		if(buf == '.')
			break;
			// return 0;

		buf2=getchar();

		if(buf2 != '\n' )
		{
			ungetc(buf2, stdin);
			scanf("%s ", cmd);
		}
		else
		{
			cmd[0]=0x0; //nullstr
			cmd[1]=0x0;
		}

		#ifdef DEBUGOWN		
		printf("%s\n", cmd );
		#endif


		switch(buf)
		{
			case '*':
				rotate(tree, n, cmd);
			break;

			
			case '-':
				negate(tree, n, cmd);
			break;

			
			case '0':
				zero(tree, n, cmd);
			break;

			
			case '1':
				ones(tree, n, cmd);
			break;

			
			case '=':
				printf("%d\n", variety(tree, n, cmd));
			break;

			
			case '#':
				printf("%d\n", check(tree, n, cmd));
			break;			
		}

	}

#ifdef DEBUGOWN
	for (int i = 0; i < n; ++i)
	{
		for (int ii = 0; ii < n; ++ii)
		{
			point_to_cmd(n, ii, i, cmd);
			printf("%d", (ptr_from_cmd(tree, cmd))->val);
		}
		puts("");

	}
#endif
	
	return 0;
}