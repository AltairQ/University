
#include "powerproduct.h"
#include "polynomial.h"
#include "bigint.h"
#include "rational.h"


template< typename N >
polynomial< N > exptaylor( unsigned int n )
{
   powerproduct v;

   N fact = 1;

   polynomial< N > result;
   for( unsigned int i = 0; i < n; ++ i )
   {
      result[v] += fact;
      v = v * powvar( "x" );
      fact = fact / (i+1);
   }

   return result;
}


void add_test()
{
   polynomial<int> a;
   polynomial<int> b;

   a[{"x"}] = 6;
   b[{"x"}] = 7;

   std::cout<<(a+b)<<"\n";
}

void mult_test()
{
   polynomial<int> a;
   polynomial<int> b;

   a[{}] = 6;
   b[{"x"}] = 7;

   std::cout<<(a*b)<<"\n";
}

void mult_test_2()
{
   polynomial<int> a;
   polynomial<int> b;
   polynomial<int> c;

   a[{powvar("x",4)}]=1;
   a[{}] = 1;

   std::cout<<a<<"\n";

   b[{powvar("x",1)}]=1;
   b[{}] = -1;

   std::cout<<b<<"\n";

   c = a*b;

   std::cout<<"c: "<<c<<"\n";
}


void mult_test_3()
{
   polynomial<int> a;
   polynomial<int> b;
   polynomial<int> c;

   a[{powvar("x",1), powvar("y",1)}]=1;
   a[{}] = 1;

   std::cout<<a<<"\n";

   b[{powvar("x",1)}]=1;
   b[{}] = -1;

   std::cout<<b<<"\n";

   c = a*b;
   std::cout<<"c: "<<c<<"\n";


   std::cout<<"coeff with x^4";
   std::cout<<(c[{powvar("x",4)}])<<"\n";


}


int main( int argc, char* argv [] )
{
   std::cout << "hello\n";

   std::cout<<"add test:\n";
   add_test();

   std::cout<<"mult test:\n";
   mult_test();

   std::cout<<"mult test2:\n";
   mult_test_2();

   std::cout<<"mult test3:\n";
   mult_test_3();


   std::cout<<"-------------------------------------------\n";

   // polynomial< rational > pol;

   // int N = 50;

   // pol[ { } ] = 1;

   // std::cout << "just one \n";

   // for( auto x : pol)
   //    std::cout<<"("<<x.first<<","<<x.second<<")\n";


   // pol[ { "x" } ] = rational( 1, N ); 

   // std::cout << "just x+1 \n";


   // for( auto x : pol)
   //    std::cout<<"("<<x.first<<","<<x.second<<")\n";

   // std::cout<<pol;

   
   // polynomial< rational > res = 1;
 
   // for( int i = 0; i < N; ++ i )
   //    res = res * pol;

   // std::cout << "rsult = " << res << "\n";

   // std::cout << " taylor expansion = " << exptaylor<rational>(20) << "\n";

   // std::cout << "difference = " ;  
   // std::cout << res - exptaylor<rational> ( 40 ) << "\n";
 
   return 0;
}


