
#include "tree.h"


int main( int argc, char* argv [ ] )
{
	tree t1( std::string( "a" ));
	tree t2( std::string( "c" )); 
	tree t3 = tree( std::string( "f" ), { t1, t2 } );
	tree t4("sth");



	std::vector< tree > arguments = { t1, t2, t3 };
	std::cout << tree( "F", std::move( arguments )) << "\n";

	t4 = t4;
	t4 = t3;
	t4 = std::move(t3);

	tree t5 = t3;
	std::cout << t5 << "\n";
	std::cout << subst(t5, "nie ma tego w drzewie", t2) << "\n";


	std::cout<<"\n\nsubst test\n\n";
	tree t6("z",   {t1, t2, t3, t5});
	std::cout << t6 << "\n";
	t6 = subst(t6, "a", t6);
	std::cout << subst(t6, "a", t6) << "\n";


}



