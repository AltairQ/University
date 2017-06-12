
#include "powerproduct.h"
#include <algorithm>


std::ostream& operator << ( std::ostream& out, const powvar & p )
{
   if( p.n == 0 )
   {
      out << "1"; // Should not happen, but we still have to print something.
      return out;
   }

   out << p.v;

   if( p.n == 1 )
      return out;

   if( p.n > 0 )
      out << "^" << p.n;
   else
      out << "^{" << p.n << "}";
   return out;
}


std::ostream& operator << ( std::ostream& out, const powerproduct& c )
{
   if( c. isunit( ))
   {
      out << "1";
      return out;
   }

   for( auto p = c. repr. begin( ); p != c. repr. end( ); ++ p )
   {
      if( p != c. repr. begin( ))
         out << ".";
      out << *p;
   }

   return out;
}


int powerproduct::power( ) const 
{
   int p = 0;
   for( auto pv : repr )
      p += pv. n;
   return p;
}


void powerproduct::normalize()
{
   // std::cout<<"\nbefore normal: "<<(*this);

   std::sort(
      repr.begin(),
      repr.end(),
      [](const powvar &a, const powvar &b) -> bool
      {
         return a.v < b.v;
      }
      );

   for(size_t i = 1; i < repr.size(); i++)
   {
      if(repr[i-1].v == repr[i].v)
      {
         repr[i-1].n += repr[i].n;
         repr.erase(repr.begin()+i);
      }
   }

   for(size_t i =0; i < repr.size(); i++)
   {
      if(repr[i].n == 0)
         repr.erase(repr.begin()+i);
   }

   // std::cout<<"\n after normal: "<<(*this)<<"\n";
}


powerproduct operator * (const powerproduct& c1, const powerproduct& c2 )
{
   std::vector <powvar> buf = c1.repr;
   buf.insert(buf.end(), c2.repr.begin(), c2.repr.end());
   powerproduct buf2(buf);


   buf2.normalize();
   
   return buf2;

}