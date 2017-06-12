#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

template< typename C = std::less< std::string >>
std::map< std::string, unsigned int, C >
frequencytable( const std::vector< std::string > & text )
{
	std::map<std::string, unsigned int, C> freq;

	for(auto word: text)
		freq[word]++;

	return freq;

}

template< typename C >
std::ostream& operator << ( std::ostream& out,
const std::map< std::string, unsigned int, C > & m )
{
	for(auto pair: m)
		out<<pair.first<<":\t"<<pair.second<<"\n";

	return out;
}

struct case_insensitive_cmp
{
	bool operator() ( const std::string& s1, const std::string& s2 ) const
	{
		size_t ind = 0;
		size_t s1s = s1.size();
		size_t s2s = s2.size();
	
		while(ind < s1s && ind < s2s && tolower(s1[ind]) == tolower(s2[ind]))
			ind++;
	
		if( ind == s1s && ind != s2s)
			return true;
	
		if(ind == s2s)	
			return false;
		
	
		return (tolower(s1[ind]) < tolower(s2[ind]));


	}

};

struct case_insensitive_hash
{
	size_t operator()  ( const std::string& s ) const
	{
		size_t acc = 0;
		for(char x: s)
		{
			acc += (size_t)tolower(x);
			acc *= 66456456;
			acc %= 4294967291;
		}

		return acc;

	}
};

struct case_insensitive_equality
{
	bool operator ( ) ( const std::string& s1,const std::string& s2 ) const
	{
		size_t ind = 0;
		size_t s1s = s1.size();
		size_t s2s = s2.size();

		if (s1s != s2s)
			return false;

		while(ind < s1s && ind < s2s && tolower(s1[ind]) == tolower(s2[ind]))
			ind++;
	
		if(ind == s2s && ind == s1s)	
			return true;
		
		return false;
	}
};


template< typename H = std::hash< std::string >,
typename E = std::equal_to< std::string >>
std::unordered_map< std::string, unsigned int, H, E >
hashed_frequencytable( const std::vector<std::string> & text )
{
	std::unordered_map< std::string, unsigned int, H, E > toret;

	for(auto word: text)
		toret[word]++;

	return toret;	
}

std::vector<std::string> readfile( std::istream& input ) 
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


int main()
{
	std::vector<std::string> text = {"a","a","b","ala","bardek"};
	auto freq = frequencytable(text);
	std::cout<<freq;

	std::cout<<"-------------------------------\n\n";

	case_insensitive_cmp c;
	std::cout << c( "a", "A" ) << c( "a","b" ) << c( "A", "b" )<<"\n";
	std::cout<<"-------------------------------\n\n";


	std::cout << frequencytable<case_insensitive_cmp>( std::vector< std::string >
	{ "AA", "aA", "Aa", "this", "THIS" } );

	std::cout<<"\n-------------------------------\n\n";

	case_insensitive_hash h;
	std::cout << h( "xxx" ) << " " << h( "XXX" ) << "\n";
	std::cout << h( "Abc" ) << " " << h( "abC" ) << "\n";
	// Hash value should be case insensitive.
	case_insensitive_equality e;
	std::cout << e( "xxx", "XXX" ) << "\n";
	// Prints ’1’.

	std::cout<<"\n-------------------------------\n\n";

	std::ifstream confessions ("confessions.txt", std::ifstream::in);

	auto conf_words = readfile(confessions);

	auto f_conf = hashed_frequencytable<case_insensitive_hash, case_insensitive_equality>(conf_words);


	for(auto quer: std::vector<std::string>{"magnus", "hominium", "memoria"})	
		std::cout<<quer<<":\t"<<f_conf[quer]<<"\n";

	std::pair<std::string, unsigned int> max_occ = {"*none*", 0};

	for(std::pair<std::string, unsigned int> m: f_conf)
		if (m.second > max_occ.second)
			max_occ = m;


	std::cout << "most frequent word is:\n";
	std::cout << max_occ.first<<":\t"<<max_occ.second<<"\n";

	
	return 0;
}