#include "surfs.h"

static double Pi =  3.1415926535897932384626;

double circle::area() const
{
	return Pi * radius * radius;
}

double circle::circumference( ) const
{
	return 2.0*Pi*radius;
}

circle* circle::clone( ) const &
{
	return new circle(x,y,radius);
}

circle* circle::clone( ) &&
{
	return new circle(x,y,radius);
}

void circle::print( std::ostream& in ) const
{
	in << "circle:[";
	in << "(" << x <<", "<<y<<"), "<<radius;
	in << "]";
}