#include "surfs.h"


rectangle::rectangle(double a, double b, double c, double d)
	:x1(a),
	 y1(b),
	 x2(c),
	 y2(d)
{

}

double rectangle::area() const
{
	return std::abs((x1-x2)*(y1-y2));
}

double rectangle::circumference() const
{
	return 2.0*(abs(x1-x2) + abs(y1-y2));
}

rectangle* rectangle::clone() const &
{
	return new rectangle(x1, y1, x2, y2);
}

rectangle* rectangle::clone() &&
{
	return this;
}

void rectangle::print( std::ostream& in ) const
{
	in << "rectangle:[";
	in << "(" << x1 << ", " << y1<<"), ";
	in << "(" << x2 << ", " << y2<<")";
	in <<  "]";
}
