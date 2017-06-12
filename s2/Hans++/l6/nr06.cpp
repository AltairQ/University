
#include <fstream>
#include <iostream>
#include <random>

#include "listtest.h"
#include "vectortest.h"
#include "timer.h"



void tests()
{

   char str_buf[256];

   std::vector<size_t> size_vect = 
   {100, 200, 300, 400, 500, 1000, 2000, 3000, 3500, 4000, 5000,
    8000, 10000, 11000, 12000, 13000, 15000, 18000, 20000, 22000, 25000 };

   // std::vector<size_t> size_vect = 
   // {100, 1000, 2000, 3000, 4000, 5000};

   size_t samples_count = 3;


   std::cout<<"vector sort_move\n";

   for(auto siz : size_vect)
   {

      snprintf(str_buf, sizeof(str_buf), "%zu\t", siz);
      printf("%s", str_buf);

      double t_sum = 0.0;

      for (size_t sample_no = 0; sample_no < samples_count; ++sample_no)
      {
            auto vect = vectortest::randomstrings(siz,50);

            auto t1 = std::chrono::high_resolution_clock::now( ); 
            vectortest::sort_move( vect );
            auto t2 = std::chrono::high_resolution_clock::now( );
         
            std::chrono::duration< double > d = ( t2 - t1 );         
            t_sum += d.count();
      }

      std::cout<< t_sum / (double)samples_count<<"\n";
   }

   std::cout<<"\n\n";


   std::cout<<"vector sort_assign\n";

   for(auto siz : size_vect)
   {

      snprintf(str_buf, sizeof(str_buf), "%zu\t", siz);
      printf("%s", str_buf);

      double t_sum = 0.0;

      for (size_t sample_no = 0; sample_no < samples_count; ++sample_no)
      {
            auto vect = vectortest::randomstrings(siz,50);

            auto t1 = std::chrono::high_resolution_clock::now( ); 
            vectortest::sort_assign( vect );
            auto t2 = std::chrono::high_resolution_clock::now( );
         
            std::chrono::duration< double > d = ( t2 - t1 );         
            t_sum += d.count();
      }

      std::cout<< t_sum / (double)samples_count<<"\n";
   }

   std::cout<<"\n\n";



   std::cout<<"vector sort_std\n";

   for(auto siz : size_vect)
   {

      snprintf(str_buf, sizeof(str_buf), "%zu\t", siz);
      printf("%s", str_buf);

      double t_sum = 0.0;

      for (size_t sample_no = 0; sample_no < samples_count; ++sample_no)
      {
            auto vect = vectortest::randomstrings(siz,50);

            auto t1 = std::chrono::high_resolution_clock::now( ); 
            vectortest::sort_std( vect );
            auto t2 = std::chrono::high_resolution_clock::now( );
         
            std::chrono::duration< double > d = ( t2 - t1 );         
            t_sum += d.count();
      }

      std::cout<< t_sum / (double)samples_count<<"\n";
   }

   std::cout<<"\n\n";

   std::cout<<"list sort_move\n";

   for(auto siz : size_vect)
   {

      snprintf(str_buf, sizeof(str_buf), "%zu\t", siz);
      printf("%s", str_buf);

      double t_sum = 0.0;

      for (size_t sample_no = 0; sample_no < samples_count; ++sample_no)
      {
            auto vect = vectortest::randomstrings(siz,50);

            auto list =  listtest::to_list(vect);

            auto t1 = std::chrono::high_resolution_clock::now( ); 
            listtest::sort_move( list );
            auto t2 = std::chrono::high_resolution_clock::now( );
         
            std::chrono::duration< double > d = ( t2 - t1 );         
            t_sum += d.count();
      }

      std::cout<< t_sum / (double)samples_count<<"\n";
   }

   std::cout<<"\n\n";



   std::cout<<"list sort_assign\n";

   for(auto siz : size_vect)
   {

      snprintf(str_buf, sizeof(str_buf), "%zu\t", siz);
      printf("%s", str_buf);

      double t_sum = 0.0;

      for (size_t sample_no = 0; sample_no < samples_count; ++sample_no)
      {
            auto vect = vectortest::randomstrings(siz,50);

            auto list =  listtest::to_list(vect);

            auto t1 = std::chrono::high_resolution_clock::now( ); 
            listtest::sort_assign( list );
            auto t2 = std::chrono::high_resolution_clock::now( );
         
            std::chrono::duration< double > d = ( t2 - t1 );         
            t_sum += d.count();
      }

      std::cout<< t_sum / (double)samples_count<<"\n";
   }

   std::cout<<"\n\n";



}


int main( int argc, char* argv [] )
{

   // std::vector< std::string > vect = vectortest::readfile(std::cin);
   // std::cout << vect << "\n";

   // std::list < std::string > list = listtest::readfile(std::cin);
   // std::cout << list << "\n";

   // listtest::sort_std(list);

   // std::cout << list << "\n";

   tests();


   return 0;
}


