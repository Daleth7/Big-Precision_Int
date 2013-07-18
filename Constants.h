#ifndef CONSTANTS_H
	#define CONSTANTS_H
	#include <cstddef>
	
	namespace{
			//Number literal constants
		const double
			PI__ = 3.141592653589793,
			e__  = 2.718281828459045,
			epsilon__ = 1e-15
		;
		
			//GAL - Get Array Length
		template < typename T, size_t N >
		inline constexpr size_t GAL( T(&)[N] )
			{ return N; }

			//List of prime numbers for general use
		const int __prime[] = {
			2,3,5,7,11,13,17,19,23,
			29,31,37,41,43,47,53,57,59,
			61,67,71,73,79,83,87,89,97,
			101,103,107,109,113,127,131
		};
		const size_t __prime_size = GAL(__prime);
	}
	
	inline constexpr long double operator"" _PI(long double literal)
        {return literal*PI__;}
	inline constexpr long double operator"" _e(long double literal)
        {return literal*e__;}
	inline constexpr long double operator"" _Per(long double literal)
        {return literal/100;}
	
#endif