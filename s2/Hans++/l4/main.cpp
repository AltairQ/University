
#include "string.h"
#include <iostream>

#include <stdexcept>
#include <vector>

// From the lecture. Not needed for the task:

void fail_often( )
{
   srand( time( NULL ));
   if( rand( ) & 1 )
      throw std::runtime_error( "i failed" );
}

void f( )
{
   string s = "this is a string";
   
   std::vector< string > vect = { "these", "are", "also", "string" };
   string more [] = {"these", "are", "even", "more", "string" };

   // fail_often( );
}

int main( int argc, char* argv [ ] )
{
   // Add more tests by yourself. Untested code = unwritten code. 

   string s;
   string s2 = "hello";

   s = s2;  // Assignment, not initialization.
   s = s;

   std::cout << "s = " << s << "\n";

   s = "this is a string";
   std::cout << s << "\n";

   for( char& c : s )
   c = toupper(c);
   std::cout << s << "\n";



   string r1 = "abc";
   string r2 = "aaa";
   string r3 = "abc";
   string r4 = "abcd";

   std::cout << "r1 = " << r1 << "\n";
   std::cout << "r2 = " << r2 << "\n";
   std::cout << "r3 = " << r3 << "\n";
   std::cout << "r4 = " << r4 << "\n";

   std::cout<<"\n";

   std::cout<<"r1+r2= "<<(r1+r2)<<std::endl;

   std::cout<<r1<<" == "<<r2<<" ? -> "<<(r1 == r2)<<std::endl;
   std::cout<<r1<<" == "<<r3<<" ? -> "<<(r1 == r3)<<std::endl;

   std::cout<<r1<<" < "<<r3<<" ? -> "<<(r1 < r3)<<std::endl;
   std::cout<<r1<<" <= "<<r3<<" ? -> "<<(r1 <= r3)<<std::endl;
   std::cout<<r1<<" < "<<r4<<" ? -> "<<(r1 < r4)<<std::endl;


   string r6 ="";

   for (int i = 0; i < 200; ++i)   
      r6+='a';
   
   std::cout << "r6 = " << r6 << "\n";   


}


