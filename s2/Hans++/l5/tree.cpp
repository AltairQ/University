
#include "tree.h"

tree::tree(const tree& t)
		:pntr{t.pntr}
{
	pntr->refcnt++;	
}

void tree::operator=(tree&& t)
{
	std::swap(pntr, t.pntr);	
}

void tree::operator=(const tree& t)
{
	*this = tree(t);
}


tree::~tree()
{
	if(--(pntr->refcnt) == 0)
		delete pntr;

}

const string& tree::functor() const
{
	return pntr->f;
}

const tree& tree::operator[] (size_t i) const
{
	return pntr->subtrees[i];
}

size_t tree::nrsubtrees() const
{
	return pntr->subtrees.size();
}

std::ostream& operator << ( std::ostream& stream, const tree& in)
{
	stream << in.functor()<<"/"<<in.nrsubtrees() << " at "<< in.getaddress()<<"\n";

	if(in.nrsubtrees() != 0)
	{
		//not so pretty on the inside
		stream <<"{ ";
	
		for (size_t i = 0; i < in.nrsubtrees(); ++i)
		{
			stream << " " << in[i];
		}
	
		stream << "}";
	}

	return stream;
}

string& tree::functor()
{
	ensure_not_shared();

	return pntr->f;

}

tree& tree::operator[] (size_t i)
{
	ensure_not_shared();

	return pntr->subtrees[i];
}

void tree::ensure_not_shared()
{
	if(pntr->refcnt == 1)
		return;

	pntr->refcnt--;

	pntr = new trnode(pntr->f, pntr->subtrees, 1);
}


tree subst( const tree& t, const string& var, const tree& val)
{

	if(t.nrsubtrees() > 0)
	{
		tree tmp_tree = t;

		for(size_t i = 0; i<tmp_tree.nrsubtrees(); i++)
			tmp_tree.replacesubtree(i, subst(t[i], var, val));

		return tmp_tree;
	}
	else
	{
		if(t.functor() == var)
			return val;
	}

	return t;
	
}
