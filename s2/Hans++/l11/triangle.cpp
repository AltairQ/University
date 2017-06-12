#include "surfs.h"

double triangle::area() const
{
	double a,b,c,s;
	a = sqrt( pow((x2-x1),2) + pow((y2-y1),2) );
	b = sqrt( pow((x3-x2),2) + pow((y3-y2),2) );
	c = sqrt( pow((x1-x3),2) + pow((y1-y3),2) );
	s = (a+b+c)/2.0;

	return sqrt(s*(s-a)*(s-b)*(s-c));
}

double triangle::circumference() const
{
	return sqrt( pow((x2-x1),2) + pow((y2-y1),2) )
	+ sqrt( pow((x3-x2),2) + pow((y3-y2),2) )
	+ sqrt( pow((x1-x3),2) + pow((y1-y3),2) );
}

triangle* triangle::clone() const &
{
	return new triangle(x1, y1, x2, y2, x3, y3);
}

triangle* triangle::clone() &&
{
	return new triangle(x1, y1, x2, y2, x3, y3);
}

void triangle::print( std::ostream& in) const
{
	in << "triangle:[";
	in << "(" << x1 << ", " << y1<<"), ";
	in << "(" << x2 << ", " << y2<<"), ";
	in << "(" << x3 << ", " << y3<<")";
	in <<  "]";
}