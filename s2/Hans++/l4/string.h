
#ifndef STRING_INCLUDED 
#define STRING_INCLUDED 1

#include <iostream> 
#include <cstring>
#include <stdexcept>

class string
{
	size_t len;
	char *p; 

public: 
	string( )
		: len{0},
		  p{ nullptr }   
	{ }

	string( const char* s )
		: len{ strlen(s) },
		  p{ new char[ len ] }
	{
		for( size_t i = 0; i < len; ++ i )
			p[i] = s[i]; 
	}

	string( const string& s )
		: len{ s. len },
		  p{ new char[ len ] }
	{
		for( size_t i = 0; i < len; ++ i )
			p[i] = s.p[i]; 
	}

	void operator = ( const string& s )
	{ 
		if( len != s.len )
		{
			delete[] p; 
			len = s. len;
			p = new char[ len ];
		}

		for( size_t i = 0; i < len; ++ i )
			p[i] = s.p[i];
	}

	char operator[] (size_t i) const
	{
		if(i >= this->size())
			throw std::runtime_error("index out of bounds");

		return p[i];
	}

	char& operator[] (size_t i)
	{
		if(i >= this->size())
			throw std::runtime_error("index out of bounds");

		return p[i];
	}

	void operator+= (char c);

	void operator+= (const string& s);

	size_t size( ) const { return len; }



	using iterator = char* ;
	using const_iterator = const char* ;
	const_iterator begin( ) const { return p; }
	const_iterator end( ) const { return p + len; }
	iterator begin( ) { return p; }
	iterator end( ) { return p + len; }


	~string( )
	{
		delete[] p;
	}

};

std::ostream& operator << ( std::ostream& out, const string& s );


string operator+(string s1, const string& s2);

bool operator == ( const string& s1, const string& s2 );
bool operator != ( const string& s1, const string& s2 );
bool operator < ( const string& s1, const string& s2 );
bool operator > ( const string& s1, const string& s2 );
bool operator <= ( const string& s1, const string& s2 );
bool operator >= ( const string& s1, const string& s2 );




#endif


