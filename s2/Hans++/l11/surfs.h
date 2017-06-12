#ifndef SURFS
#define SURFS

#include <iostream>
#include <cmath>


//(C) HANS NIVELLE

struct surf
{
	virtual double area( ) const = 0;
	virtual double circumference( ) const = 0;
	virtual surf* clone( ) const & = 0;
	virtual surf* clone( ) && = 0;
	virtual void print( std::ostream& ) const = 0;
	virtual ~surf() {} ; // a destructor must be defined
};

struct rectangle : public surf
{
	double x1, y1;
	double x2, y2;
	double area( ) const override;
	double circumference( ) const override;
	rectangle* clone( ) const & override;
	rectangle* clone( ) && override;
	void print( std::ostream& ) const override;
	rectangle(double a, double b, double c, double d);
};

struct triangle : public surf
{
	double x1, y1; // Positions of corners.
	double x2, y2;
	double x3, y3;

	triangle(double a1, double b1,
	 double a2, double b2,
	 double a3, double b3)
		:x1(a1),
		 y1(b1),
		 x2(a2),
		 y2(b2),
		 x3(a3),
		 y3(b3)
	{

	}

	double area( ) const override;
	double circumference( ) const override;
	
	triangle* clone( ) const & override;
	triangle* clone( ) && override;
	void print( std::ostream& ) const override;
};

struct circle : public surf
{
	double x; // Position of center.
	double y;
	double radius;
	double area( ) const override;
	double circumference( ) const override;
	circle* clone( ) const & override;
	circle* clone( ) && override;
	void print( std::ostream& ) const override;

	circle(double a, double b, double rr)
		:x(a),
		 y(b),
		 radius(rr)
	{

	}
};

struct surface
{
	surf* ref;
	surface( const surface& s );
	surface( surface&& s );
	surface( const surf& s );
	surface( surf&& s );
	void operator = ( const surface& s );
	void operator = ( surface&& s );
	void operator = ( const surf& s );
	void operator = ( surf&& s );
	~surface( )
	{
	delete ref;
	}
	
	const surf& getsurf( ) const { return *ref; }
	// There is no non-const access, because
	// changing would be dangerous.
};

#endif