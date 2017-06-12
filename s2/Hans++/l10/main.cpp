
#include <iostream>

#include "units.h"

// Useful if you want to compute the yield of an atomic bomb:

#if 1
quantity::energy mc2( quantity::mass m )
{
   auto C = 299792458.0_mps;   
   return m * C * C;
}
#endif 

const auto c = 299792458.0_mps;

int main( int argc, char* argv [ ] )
{
   std::cout << 9.81 * 1.0_m / ( 1.0_sec * 1.0_sec ) << "\n";
      // Acceleration on earth.

   std::cout << 1.0_m << "\n";
   std::cout << 2.0_hr << "\n";
   
   std::cout << 1000.0_watt << "\n";

   std::cout << "Energy of 800mAh battery @ 1.2 V:";
   std::cout << 800.0_mAh * 1.2_V << "\n";

   std::cout << "Car B kinetic energy:";
   std::cout << 1200.0_kg * (100.0_kmh + 30.0_kmh) * (100.0_kmh + 30.0_kmh) / 2.0 <<"\n";

   std::cout << "Special relativity velocity of car B:";
   auto v1 = 100.0_kmh;
   auto v2 = 30.0_kmh;
   auto res = ( (v1 + v2) / (1.0 + (v1 * v2) / (c*c) ) );
   std::cout << res;
   std::cout << "\n(Difference: " << res - ( v1 + v2)  <<" m/s)\n\n";

   std::cout << "Tsar Bomb is equivalent to ";

   //TNT energy density
   auto TNT_ED = 4184.0_joule / 1.0_g;

   std::cout << mc2(2.3_kg) / TNT_ED;


   std::cout << " of TNT";






   return 0;

}


