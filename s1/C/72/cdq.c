// Mateusz Maciejewski
// Lista 7 zadanie 2
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

	return NULL;
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

	return NULL;

}

long cdq_size(cdq q)
{
	if(q == NULL)
		return 0;

	node* ptr = q->left;
	long size=1;

	while(ptr != q)
	{
		ptr = ptr->left;
		size++;
	}

	return size;
}


cdq cdq_merge(cdq* q1, cdq* q2)
{
	cdq tmp;

	if (cdq_is_empty(*q2))
	{
		tmp = *q1;
		*q1 = NULL;
		return tmp;
	}

	if (cdq_is_empty(*q1))
	{
		tmp = *q2;
		*q2 = NULL;
		return tmp;
	}


	cdq tmp_beg = *q1;
	cdq tmp_end = (*q1)->left;
	*q1 = NULL;

	cdq tmp2_beg = (*q2);
	cdq tmp2_end = (*q2)->left;
	*q2 = NULL;

	tmp_beg->left = tmp2_end;
	tmp2_end->right = tmp_beg;

	tmp_end->right = tmp2_beg;
	tmp2_beg->left = tmp_end;

	return tmp_beg;

}

cdq cdq_copy(const cdq q)
{
	cdq tmp = cdq_init();

	if(cdq_is_empty(q))
		return tmp;

	cdq_push_back(&tmp, q->val);

	node* ptr = q->right;

	while(ptr != q)
	{
		cdq_push_back(&tmp, ptr->val);
		ptr = ptr->right;
	}

	return tmp;

}

void cdq_erase(cdq *q)
{
	while(!cdq_is_empty(*q))
		cdq_pop_front(q);
}

void cdq_sorted_insert(cdq *q1, double val)
{
	if(cdq_is_empty(*q1))
	{
		cdq_push_front(q1, val);
		return;
	}

	cdq q = *q1;

	double prev_val = q->val;
	node* ptr = q->right;

	while(ptr != q)
	{
		if(prev_val <= val && val <= ptr->val)
		{
			cdq_insert_between(ptr->left, ptr, val);
			return;
		}


		prev_val = ptr->val;
		ptr = ptr->right;
	}

	if(prev_val <= val)
		cdq_push_back(q1, val);
	else
		cdq_push_front(q1, val);


}

void cdq_insert_between(node *n1, node *n2, double val)
{
	node *tmp_node = malloc(sizeof(node));

	if(tmp_node == NULL)
		return;

	tmp_node->val=val;

	tmp_node->left = n1;
	tmp_node->right = n2;
	n1->right = tmp_node;
	n2->left = tmp_node;
}

void cdq_sort_insert(cdq *q)
{
	cdq tmp = cdq_init();

	//let's reuse our work
	while(!cdq_is_empty(*q))
		cdq_sorted_insert(&tmp, cdq_pop_front(q));

	*q = tmp;
}

//still not bad memory-wise
void cdq_sort_quick(cdq *q)
{
	if(cdq_is_empty(*q))
		return;

	cdq tq = *q;

	double pivot_val = cdq_pop_front(&tq);

	cdq pq  = cdq_init();
	cdq_push_front(&pq, pivot_val);
	//we must isolate the pivot
	//otherwise we will never end

	cdq low = cdq_init();
	cdq top = cdq_init();

	while(!cdq_is_empty(tq))
	{
		double x = cdq_pop_front(&tq);

		if(x <= pivot_val)
			cdq_push_back(&low, x);

		if(x > pivot_val)
			cdq_push_back(&top, x);
	}

	cdq_sort_quick(&low);
	cdq_sort_quick(&top);

	top = cdq_merge(&pq, &top);
	*q = cdq_merge(&low, &top);

}