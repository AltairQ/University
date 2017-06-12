// Mateusz Maciejewski
// Lista 7 zadanie 1
// implementacja wlasciwa

#include "cdq.h"

struct node
{
	node *left;
	node *right;
	double val;	
	
};

cdq cdq_init()
{
	return NULL;
}

int cdq_push_front(cdq *q, double val)
{
	node *tmp_node = malloc(sizeof(node));

	if(tmp_node == NULL)
		return 0;

	tmp_node->val=val;

	if(*q == NULL)
	{
		*q = tmp_node;
		tmp_node->left = tmp_node;
		tmp_node->right = tmp_node;
		return 1;
	}

	if(*q != NULL)
	{
		node *top = *q;

		top->left->right = tmp_node;		

		tmp_node->left = top->left;
		tmp_node->right = top;

		top->left = tmp_node;
		*q = tmp_node;

		return 1;
	}

}


bool cdq_is_empty(const cdq q)
{
	return (q == NULL);
}

double cdq_pop_front(cdq *q)
{
	if (*q == NULL)
	{
		return NAN;
	}

	double res = (*q)->val;

	node *top = *q;

	if(top->left == top && top->right == top)//single node
	{
		free(top);
		*q = NULL;
	}
	else
	{
		top->left->right = top->right;
		top->right->left = top->left;
		(*q)=top->right;
		free(top);
	}

	return res;
}

double cdq_pop_back(cdq *q)
{
	if (*q == NULL)
	{
		return NAN;
	}

	node *top = (*q)->left;
	double res = top->val;

	if(top->left == top && top->right == top)//single node
	{
		free(top);
		*q = NULL;
	}
	else
	{
		top->left->right = top->right;
		top->right->left = top->left;
		// (*q)=top->right;
		free(top);
	}

	return res;
}


int cdq_push_back(cdq *q, double val)
{
	node *tmp_node = malloc(sizeof(node));

	if(tmp_node == NULL)
		return 0;

	tmp_node->val=val;

	if(*q == NULL)
	{
		*q = tmp_node;
		tmp_node->left = tmp_node;
		tmp_node->right = tmp_node;
		return 1;
	}

	if(*q != NULL)
	{
		node *top = *q;

		top->left->right = tmp_node;		

		tmp_node->left = top->left;
		tmp_node->right = top;

		top->left = tmp_node;
		// *q = tmp_node;

		return 1;
	}

}

size_t cdq_size(cdq q)
{
	if(q == NULL)
		return 0;

	node* ptr = q->left;
	size_t size=1;

	while(ptr != q)
	{
		ptr = ptr->left;
		size++;
	}

	return size;
}
