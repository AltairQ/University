#include <vector>

#include "surfs.h"


void print_surf(surf &in)
{
	in.print(std::cout);
}

std::ostream& operator << 
 ( std::ostream& stream, const surface& s )
{
	s.getsurf().print(stream);
	return stream;
}


void print_statistics( const std::vector< surface > & table )
{
	double total_area = 0.0;
	double total_circumference = 0.0;
	for( const auto& s : table )
	{
		std::cout << "adding info about " << s << "\n";
		total_area += s. getsurf( ). area( );
		total_circumference += s. getsurf( ). circumference( );
	}
	std::cout << "total area is " << total_area << "\n";
	std::cout << "total circumference is " << total_circumference << "\n";
}


int main()
{
	std::vector<surface> ss ={
		surface(rectangle(1,2,3,4)),
		surface(triangle(1,2,3,4,5,6)),
		surface(circle(1,2,10))
	};

	triangle tri(6,5,4,3,2,1);

	ss[0] = rectangle(2,3,4,5);
	ss[1] = surface(rectangle(3,4,5,6));
	ss[1] = surface(tri);
	ss[1] = tri;




	print_statistics(ss);
	
	return 0;
}