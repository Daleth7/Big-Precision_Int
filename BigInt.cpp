#include "BigInt.h"
#include <algorithm>
#include <vector>

BigInt::BigInt( void ): value( "0" ){}
BigInt::BigInt( const std::string &value) : value( value ) {}

BigInt BigInt::operator* ( const BigInt &rhs )
{
    std::string temp( rhs.value );
    std::reverse( value.begin() , value.end() );
    std::reverse( temp.begin() , temp.end() );
    auto product( 0u ) , remainder( 0u ) , carry( 0u ) , count( 0u );
    std::string temp_value( "" ) ;
    std::vector<BigInt> products( 0 );

    for( auto i( 0u ); i < value.size(); ++i )
    {
        carry = 0;
        remainder = 0;
        for( auto j( 0u ); j < temp.size(); ++j )
        {
            product = ( value[ i ] - '0' ) * ( temp[ j ] - '0' ) + carry;
            remainder = product % 10;
            carry = ( product - remainder ) / 10;
            temp_value += remainder + '0';
        }
        if( carry > 0 ) temp_value += carry + '0';
        std::reverse( temp_value.begin() , temp_value.end() );
        for( auto k( 0u ); k < count; ++k ) temp_value += '0';
        products.emplace_back( BigInt( temp_value ) );
        temp_value = "";
        ++count;
    }
    for( auto i( 1u ); i < products.size(); ++i )
    {
        products[ 0 ] += products[ i ];
    }
   return( products[ 0 ] );
}

BigInt BigInt::operator/ ( const BigInt &rhs ){}
BigInt BigInt::operator+ ( const BigInt &rhs ){}
BigInt BigInt::operator- ( const BigInt &rhs ){}

BigInt& BigInt::operator+= ( const BigInt &rhs )
{
    std::string temp( rhs.value ) , result( "" );
    std::reverse( value.begin() , value.end() );
    std::reverse( temp.begin() , temp.end() );
    short sum( 0u ) , carry( 0u ) , remainder( 0u );

    while( value.size() != temp.size() ) value.size() > temp.size() ? temp += '0' : value += '0';

    for( auto i( 0u ); i < value.size(); ++i )
    {
        sum = ( value[ i ] - '0' ) + ( temp[ i ] - '0' ) + carry;
        remainder = sum % 10;
        carry = ( sum - remainder ) / 10;
        result += remainder + '0';
    }
    if( carry > 0 ) result += carry + '0';
    std::reverse( result.begin() , result.end() );
    value = result;

    return( *this );
}

BigInt& BigInt::operator-- ( void )
{
    std::reverse( value.begin() , value.end() );
    auto i( 1u );
    while( value[ 0 ] == '0' && value[ i ] == '0' )
    {
        value[ i ] = '9';
        ++i;
    }
    if( value[ 0 ] == '0' )
    {
        value[ 0 ] = '9';
        --value[ i ];
    }
    else{
        --value[ 0 ];
    }

    std::reverse( value.begin() , value.end() );
    if( value.front() == '0' ) value.erase( 0 , 1 );
    return( *this );
}

const bool operator> ( const BigInt &lhs , const BigInt &rhs )
{
    if( lhs.value.size() > rhs.value.size() ) return( true );
    else if( lhs.value.size() < rhs.value.size() ) return( false );
    else {
        for( auto i( 0u ); i < lhs.value.size(); ++i )
        {
            if( rhs.value[ i ] > lhs.value[ i ] ) return( false );
            if( lhs.value[ i ] > rhs.value[ i ] ) return( true );
        }
        return( false ); //they are equal
    }
}

BigInt BigInt::factorial( BigInt n )
{
    if( n > BigInt( "1" ) ) return( n * factorial( --n ) );
    else return( BigInt( "1" ) );
}
