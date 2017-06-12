
#include "listtest.h"
#include "vectortest.h"

#include <random>
#include <chrono>
#include <algorithm>


void listtest::sort_move( std::list< std::string > & v )
{
   for( auto j = v.begin(); j != v.end( ); ++j )   
      for( auto i = v.begin(); i != j; ++i )      
         if( *i > *j )
            std::swap( *i, *j );    
}


void listtest::sort_assign( std::list< std::string > & v )
{
   for( auto j = v.begin(); j != v.end( ); ++j )   
      for( auto i = v.begin(); i != j; ++i )  
      {
         if( *i > *j )
         {
            std::string s = *i;
            *i = *j;
            *j = s;
         }
      }   
}



std::list<std::string> listtest::to_list(std::vector< std::string > & v )
{
   return std::list<std::string>(v.begin(), v.end());
}



void listtest::sort_std( std::list< std::string > & v )
{
   //btw there is a .sort() method in std::list

   std::vector<std::string> buf{v.begin(), v.end()};
   std::sort(buf.begin(), buf.end());

   v = listtest::to_list(buf);
   
}


std::ostream& 
operator << ( std::ostream& out, const std::list< std::string > & in_list )
{
   for(auto elem : in_list)
      out<<elem<<" ";

   return out;

}


std::list<std::string> listtest::readfile( std::istream& input )
{
   std::list<std::string> rec_list;
   std::string c_word;

   int c_char;

   while((c_char = input.get()) != EOF)
      if (isspace(c_char) || ispunct(c_char))
      {
         if (!c_word.empty())
         {
            rec_list.push_back(c_word);
            c_word = "";
         }
      }
      else
      {
         c_word.push_back((char)c_char);
      }

   return rec_list;

}