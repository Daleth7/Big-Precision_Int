#ifndef BIGINT_H
#define BIGINT_H
#include <string>

class BigInt
{
public:
    BigInt( void );
    BigInt( const std::string& );

    BigInt operator* ( const BigInt& );
    BigInt operator/ ( const BigInt& );
    BigInt operator+ ( const BigInt& );
    BigInt operator- ( const BigInt& );

    BigInt& operator+= ( const BigInt& );
    BigInt& operator-- ( void );
    friend const bool operator> ( const BigInt& , const BigInt& );
    BigInt factorial( BigInt );
    std::string value;
};


#endif // BIGINT_H
