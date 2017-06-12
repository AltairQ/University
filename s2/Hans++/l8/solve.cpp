
#include "move.h"
#include "fifteen.h" 
#include <unordered_map>
#include <queue>


// Table of states and their levels:

using leveltable = 
std::unordered_map< fifteen, unsigned int, 
                    fifteen_hash, fifteen_equals > ;


#if 1

leveltable 
solve( const fifteen& start )
{
   leveltable levels;

   std::priority_queue< fifteen, std::vector< fifteen >, 
                        fifteen_further > unchecked;

   unchecked. push( start );
   levels[ start ] = 0; 

   // We have start unexplored, at its level is zero.

   std::vector<move> moves = { move::up, move::down, move::left, move::right };
      // All possible moves in a vector.

   // As long as there is a state whose neighbours are unexplored,
   // we explore them:

   while( unchecked. size( ))
   {
      fifteen best = unchecked. top( );
      unsigned int level = levels [ best ]; 
         // The best state is the state that is closest to the
         // solution. level is the number of moves that was required
         // to reach it.
   
      // std::cout << "best = " << best << "\n";
      // std::cout << "distance = " << best. distance( ) << "\n";

      if( best. issolved( ))
         return levels;

      unchecked. pop( ); 

      for( auto m : moves )
      {
         fifteen next = best;
         try
         {
            next. makemove( m );
            auto p = levels. find( next );
            if( p == levels. end( ) || level + 1 < p -> second ) 
            {
               // We did not reach next before, or we reached it
               // in more steps. 

               levels[ next ] = level + 1; 
               unchecked. push( next );
            }
         }
         catch( illegalmove& m ) { /* catch and do nothing */ } 
      }
   }

   return levels;  // In move we trust.  
}

#endif

std::list< move > findpath( const leveltable& levels,
                            fifteen f, unsigned int level )
{

   std::vector<move> moves = { move::up, move::down, move::left, move::right };
   std::list< move > path;

   if(level > 0 )
   {
      for(auto m : moves)
      {
         try
         {
            fifteen buf_level = f;
            buf_level.makemove(m);
      
            if (levels.at(buf_level) == level-1)
            {
               path = findpath(levels, buf_level, level-1 );
               path.insert(path.end(), -m);               
               break;
            }
   
         }
         catch(illegalmove& ex) {}
         catch(std::out_of_range& ex){}

      }
   }


   return path;
}
 




int main( int argc, char* argv [] )
{
   leveltable test;

   // fifteen f{ { 1, 3, 4, 12 }, 
   //            { 5, 2, 7, 11 }, 
   //            { 9, 6, 14, 10 }, 
   //            { 13, 15, 0, 8 } } ;
  
   // fifteen f{ { 1, 2, 3, 4}, 
   //            { 5, 6, 7, 8 }, 
   //            { 9, 10, 11, 12 }, 
   //            { 13, 14, 0, 15 } } ;


   // fifteen f
   // {
   //    {2, 13, 4, 12},
   //    {1, 5, 7, 10},
   //    {0, 8, 9, 3},
   //    {6, 14, 11, 15}

   // };

   // fifteen f 
   // {
   //    {0 , 2},
   //    {1,  3}
   // };

   fifteen f
   {
      {2, 3, 6},
      {1, 5, 0},
      {4, 7, 8}
   };

   auto dist = solve(f);
   // for( const auto& p : dist )
   // {
   //    std::cout << "---------------------------\n";
   //    std::cout << p.first << " " << p. second << "\n";
   // }


   auto path = findpath( dist, fifteen( ), dist[ fifteen( ) ] );
   for( move m : path )
      std::cout << m << "\n";

   for( move m : path)
      f.makemove(m);

   std::cout<<f<<"\n\n";
   std::cout<<f.issolved()<<std::endl;


   return 0;

   // fifteen f;
   // std::cout<<f<<std::endl;

   // std::cout<<f.hashvalue()<<std::endl;
}


