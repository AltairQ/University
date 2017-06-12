#include "string.h"



std::ostream& operator << ( std::ostream& out, const string& s )
{
   for( char c: s )
      out << c;
   return out; 
}


void string::operator+= (char c)
{
	char* buf = new char[len+1];
	memcpy(buf, p, sizeof(char)*len);

	buf[len]=c;

	delete [] p;
	p = buf;
	len++;
}

void string::operator+= (const string& s)
{

	char* buf = new char[len + s.size()];

	memcpy(buf, p, sizeof(char)*len);

	for (int i = 0; i < s.size(); ++i)
		buf[len+i] = s[i];

	len += s.size();
	
	delete [] p;
	p = buf;


}

string operator+(const string& s1, const string& s2)
{
	string buf = s1;
	buf+=s2;
	return buf;
}

string operator+(string s1, const string& s2)
{
	s1+=s2;
	return s1;
}


bool operator < ( const string& s1, const string& s2 )
{
	size_t ind = 0;
	size_t s1s = s1.size();
	size_t s2s = s2.size();

	while(ind < s1s && ind < s2s && s1[ind] == s2[ind])
		ind++;

	if( ind == s1s && ind != s2s)
		return true;

	if(ind == s2s)	
		return false;
	

	return (s1[ind] < s2[ind]);

}

bool operator > ( const string& s1, const string& s2 )
{
	return (s2 < s1);
}

bool operator <= ( const string& s1, const string& s2 )
{
	return (s1 == s2) || (s1 < s2);
		
}

bool operator >= ( const string& s1, const string& s2 ) 
{
	return (s2 <= s1);
}

bool operator == ( const string& s1, const string& s2 )
{
	if (s1.size() != s2.size())
		return false;

	for (size_t i = 0; i < s1.size(); ++i)
		if (s1[i] != s2[i])
			return false;

	return true;	
}

bool operator != ( const string& s1, const string& s2 )
{
	return !(s1 == s2);
}

