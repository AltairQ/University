#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node
{
	struct node *A, *B, *C, *D;
	bool mono;
	bool color;
}  node;

bool tab[1024][1024];

int read()
{
	scanf("P1\n");
	int n;
	scanf("%d %d", &n, &n);
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			char t;
			scanf(" %c", &t);
			tab[j][i] = t-'0';
		}
	}
	return n;
}

int c = 0;

node* construct(int beg_x, int end_x, int beg_y, int end_y)
{
	//printf("in:%d\n", c++);
	node *res = malloc(sizeof(node));
	if((beg_x == end_x-1) && (beg_y == end_y-1))
	{
		res->mono = true;
		res->color = tab[beg_x][beg_y];
		res->A = NULL;
		res->B = NULL;
		res->C = NULL;
		res->D = NULL;
		return res;
	}
	node *A, *B, *C, *D;
	int mid_x = (beg_x+end_x)/2, mid_y = (beg_y+end_y)/2;
	A = construct(beg_x, mid_x, beg_y, mid_y);
	B = construct(mid_x, end_x, beg_y, mid_y);
	D = construct(beg_x, mid_x, mid_y, end_y);
	C = construct(mid_x, end_x, mid_y, end_y);
	res->mono = false;
	if(A->mono && B->mono && C->mono && D->mono)
	{
		if((A->color == B->color) && (A->color == C->color) && (A->color == D->color))
		{
			res->mono = true;
			res->color = A->color;
		}
	}
	res->A = A;
	res->B = B;
	res->C = C;
	res->D = D;
	return res;
}

char word[11];

node* find(node *tree, int len)
{
	for(int i = 0; i < len; ++i)
	{
		if(word[i] == 'A') tree = tree->A;
		else if(word[i] == 'B') tree = tree->B;
		else if(word[i] == 'C') tree = tree->C;
		else if(word[i] == 'D') tree = tree->D;
	}
	return tree;
}

void check(node *tree, int len, int ix)
{
	if(ix < len)
	{
		if(word[ix] == 'A') tree = tree->A;
		else if(word[ix] == 'B') tree = tree->B;
		else if(word[ix] == 'C') tree = tree->C;
		else if(word[ix] == 'D') tree = tree->D;
		check(tree, len, ix+1);
	}
	if(tree->A == NULL) return;
	tree->mono = false;
	if(tree->A->mono && tree->B->mono && tree->C->mono && tree->D->mono)
	{
		if((tree->A->color == tree->B->color) && (tree->A->color == tree->C->color) && (tree->A->color == tree->D->color))
		{
			tree->mono = true;
			tree->color = tree->A->color;
		}
	}
}

void rotate(node *tree, int len)
{
	node *n, *t;
	n = find(tree, len);
	t = n->A;
	n->A = n->D;
	n->D = n->C;
	n->C = n->B;
	n->B = t;
}

int diversity_rec(node *tree)
{
	if(tree->mono == true) return 1;
	return diversity_rec(tree->A)+diversity_rec(tree->B)+diversity_rec(tree->C)+diversity_rec(tree->D);
}

int diversity(node *tree, int len)
{
	tree = find(tree, len);
	return diversity_rec(tree);
}

void turn_on_rec(node *tree)
{
	if(tree->A == NULL)
	{
		tree->color = true;
		return;
	}
	if(tree->mono && tree->color) return;
	tree->mono = true;
	tree->color = true;
	turn_on_rec(tree->A);
	turn_on_rec(tree->B);
	turn_on_rec(tree->C);
	turn_on_rec(tree->D);
}

void turn_on(node *tree, int len)
{
	node *ntree = find(tree, len);
	turn_on_rec(ntree);
	check(tree, len, 0);
}

void turn_off_rec(node *tree)
{
	if(tree->A == NULL)
	{
		tree->color = false;
		return;
	}
	if(tree->mono && !(tree->color)) return;
	tree->mono = true;
	tree->color = false;
	turn_off_rec(tree->A);
	turn_off_rec(tree->B);
	turn_off_rec(tree->C);
	turn_off_rec(tree->D);
}

void turn_off(node *tree, int len)
{
	node *ntree = find(tree, len);
	turn_off_rec(ntree);
	check(tree, len, 0);
}

void neg_rec(node *tree)
{
	if(tree->A == NULL)
	{
		tree->color = !tree->color;
		return;
	}
	tree->color = !tree->color;
	neg_rec(tree->A);
	neg_rec(tree->B);
	neg_rec(tree->C);
	neg_rec(tree->D);
}

void neg(node *tree, int len)
{
	node *ntree = find(tree, len);
	neg_rec(ntree);
	check(tree, len, 0);
}

int chess_rec(node *tree)
{
	if(tree->mono) return 0;
	if(tree->A->mono && tree->B->mono && tree->C->mono && tree->D->mono &&
		tree->A->color == tree->C->color && tree->B->color == tree->D->color && 
		tree->A->color != tree->B->color)
		return 1;
	return chess_rec(tree->A)+chess_rec(tree->B)+chess_rec(tree->C)+chess_rec(tree->D);

}

int chess(node *tree, int len)
{
	tree = find(tree, len);
	return chess_rec(tree);
}

void handle(int n, node *tree)
{
	while(true)
	{
		char op;
		scanf(" %c", &op);
		if(op == '.') return;
		int len = 0;

		char t;
		while((t = getchar()) != '\n') word[len++] = t-('a'-'A')*(t >= 'a');
		//printf("len%d\n", len);

		switch(op)
		{
			case '*': rotate(tree, len);
				break;
			case '=': printf("%d\n", diversity(tree, len));
				break;
			case '1': turn_on(tree, len);
				break;
			case '0': turn_off(tree, len);
				break;
			case '-': neg(tree, len);
				break;
			case '#': printf("%d\n", chess(tree, len));
				break;
		}
	}
}

int main()
{
	int size = read();
	node* tree = construct(0, size, 0, size);
	handle(size, tree);
	return 0;
}