#include "fifteen.h"
using position = std::pair< size_t, size_t > ;




fifteen::fifteen()
{
	for (size_t row = 0; row < dimension; row++)
		for (size_t col = 0; col < dimension; col++)
			table[row][col] = col + row*dimension + 1;

	open_i = dimension - 1;
	open_j = dimension - 1;

	table[open_i][open_j] = 0;

}

fifteen::fifteen( std::initializer_list< std::initializer_list< size_t >> init )
{
	if (init.size() != dimension)
		throw std::range_error("wrong init_list length!");

	size_t c_row = 0;

	for(const auto& row : init)
	{
		if(row.size() != dimension)
			throw std::range_error("wrong init_list length!");

		size_t c_col = 0;

		for(const auto& item : row)
		{
			table[c_row][c_col] = item;

			if(item == 0)
			{
				open_i = c_row;
				open_j = c_col;
			}

			c_col++;
		}

		c_row++;
	}
}


//TO TEST
position fifteen::solvedposition( size_t val )
{
	if (val == 0)
		return std::make_pair(dimension-1, dimension-1);

	return std::make_pair((val-1)/dimension, (val-1) % dimension);
	
}

size_t fifteen::hashvalue( ) const
{
	size_t hash = 0;

	for (size_t row = 0; row < dimension; row++)	
		for (size_t col = 0; col < dimension; col++)
		{
			hash += row + col + table[row][col];
			hash *= 79345569;
			hash %= 4294967291;
		}


	return hash;

}

bool fifteen::equals( const fifteen& other ) const
{
	for (size_t row = 0; row < dimension; row++)	
		for (size_t col = 0; col < dimension; col++)
			if(table[row][col] != other.table[row][col])
				return false;

	return true;
}

bool fifteen::issolved() const
{
	return this->equals(fifteen());
}


size_t fifteen::distance( ) const
{
	size_t sum = 0;

	for (size_t row = 0; row < dimension; row++)	
		for (size_t col = 0; col < dimension; col++)
			sum += distance(std::make_pair(row,col),
							fifteen::solvedposition(table[row][col])
							);

	return sum;

}


void fifteen::makemove(move m)
{
	size_t ofr, ofc;

	ofr = 0; //row offset
	ofc = 0; //col offset

	switch(m)
	{
		case move::up   :  ofr = -1; break;
		case move::left :  ofc = -1; break;
		case move::right:  ofc =  1; break;
		case move::down :  ofr =  1; break;

		defult:
			throw std::range_error( "unkown move" ); 
		break;
	}

	if (open_i + ofr < dimension && 0 <= open_i + ofr &&
		open_j + ofc < dimension && 0 <= open_j + ofc)
	{
		std::swap(table[open_i][open_j], 
					table[open_i+ofr][open_j+ofc]);
		open_i += ofr;
		open_j += ofc;
	}
	else
	{
		throw illegalmove(m);
	}


}


std::ostream& operator << ( std::ostream& stream, const fifteen& f )
{
	size_t dimension = f.dimension;

	for (size_t row = 0; row < dimension; row++)
	{
		for (size_t col = 0; col < dimension; col++)
		{
			stream << f.table[row][col] << "\t";
		}
		stream << "\n";
	}

	return stream;
}