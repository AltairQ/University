
#include "vectortest.h"

#include <random>
#include <chrono> 
#include <algorithm>

std::vector< std::string >
vectortest::randomstrings( size_t nr, size_t s )
{
   static std::default_random_engine gen( 
      std::chrono::system_clock::now( ). time_since_epoch( ). count( ) );
         // Narrowing long int into int, but that is no problem.

   static std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345689";
   static std::uniform_int_distribution<int> distr( 0, alphabet. size( ) - 1);
      // More narrowing.

   std::vector< std::string > res;

   for( size_t i = 0; i < nr; ++ i )
   {
      std::string rand;
      for( size_t j = 0; j < s; ++ j )
      {
         rand. push_back( alphabet[ distr( gen ) ] );  
      }

      res. push_back( std::move( rand ));
   }
   return res;
}
         

 
std::vector<std::string> 
vectortest::readfile( std::istream& input ) 
{
   std::vector<std::string> rec_vec;
   std::string c_word;

   int c_char;

   while((c_char = input.get()) != EOF)
      if (isspace(c_char) || ispunct(c_char))
      {
         if (!c_word.empty())
         {
            rec_vec.push_back(c_word);
            c_word = "";
         }
      }
      else
      {
         c_word.push_back((char)c_char);
      }

   return rec_vec;

}

std::ostream& 
operator << ( std::ostream& out, const std::vector< std::string > & vect ) 
{ 
   for(auto v: vect)   
      out << v << " ";   

   return out;
}

void vectortest::sort_assign( std::vector< std::string > & v )
{
   for( size_t j = 0; j < v. size( ); ++ j )
      for( size_t i = 0; i < j; ++ i )
      {
         if( v[i] > v[j] )
         {
            std::string s = v[i];
            v[i] = v[j];
            v[j] = s;
         }
      }
}

void vectortest::sort_move( std::vector< std::string > & v )
{
   for( size_t j = 0; j < v. size( ); ++ j )
   {
      for( size_t i = 0; i < j; ++ i )
      {
         if( v[i] > v[j] )
            std::swap( v[i], v[j] );
      }
   }
}

void vectortest::sort_std( std::vector< std::string > & v )
{
   std::sort( v. begin( ), v. end( ));
}


