#include "surfs.h"

surface::surface(const surface& s)
{
	ref = s.getsurf().clone();
}

surface::surface( surface&& s )
{
	ref = s.ref;
	s.ref = nullptr;
}

surface::surface(const surf& s)
{
	ref = s.clone();
}

surface::surface(surf && s)
{
	ref = s.clone();
}

void surface::operator = ( const surface& s )
{
	delete ref;
	ref = s.getsurf().clone();
}

void surface::operator = ( surface&& s )
{
	delete ref;
	ref = s.ref;
	s.ref = nullptr;
}

void surface::operator = ( const surf& s )
{
	delete ref;
	ref = s.clone();
}

void surface::operator = ( surf&& s )
{
	delete ref;
	ref = s.clone();
}
