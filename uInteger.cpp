#include "Integer.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

Integer::Integer( void ) : value( "NAN" ){}
Integer::Integer( const Integer &i ) : value( i.value ) , real( i.real ){}
Integer::Integer( const std::string value ) : value( value ) , real( true )
{
     if( *value.begin() == '-' )
     {
         this->value.erase( 0 , 1 );
         real = false;
     }
     if( *value.begin() == '+' )
     {
         this->value.erase( 0 , 1 );
     }
     assert( *this->value.begin() < 58 || *this->value.begin() > 48 );
}


Integer& Integer::operator+=( const Integer &rhs )
{
    auto lhs_crit( value.crbegin() ) , rhs_crit( rhs.value.crbegin() );
    unsigned short remainder( 0 ) , carry( 0 );
    std::string temp( "" );

    while( lhs_crit != value.crend() || rhs_crit != rhs.value.crend() )
    {
        remainder = carry;
        if( lhs_crit != value.crend() && rhs_crit != rhs.value.crend() )
        {
            remainder += *lhs_crit - '0' + *rhs_crit - '0';
            ++lhs_crit;
            ++rhs_crit;
        }
        else if( lhs_crit == value.crend() && rhs_crit != rhs.value.crend() )
        {
            remainder += *rhs_crit - '0';
            ++rhs_crit;
        }
        else if( lhs_crit != value.crend() && rhs_crit == rhs.value.crend() )
        {
            remainder += *lhs_crit - '0';
            ++lhs_crit;
        }
        if( remainder > 9 )
        {
            carry = 1;
            remainder -= 10;
        }
        else
        {
            carry = 0;
        }
        temp += ( remainder + '0' );
    }
    if( carry == 1 ) temp += '1';
    std::reverse( temp.begin() , temp.end() );
    value = temp;
    return( *this );
}
Integer operator+( const Integer &rhs , const Integer &lhs )
{
    Integer result( rhs );
    return( result += lhs );
}

Integer& Integer::operator-=( const Integer &rhs )
{
    auto lhs_crit( value.rbegin() );
    auto rhs_crit( rhs.value.crbegin() );
    unsigned short remainder( 0 ) , count( 0 );
    std::string temp( "" );

    while( lhs_crit != value.rend() || rhs_crit != rhs.value.crend() )
    {
        count = 0;
        if( lhs_crit != value.rend() && rhs_crit != rhs.value.crend() )
        {
            if( *lhs_crit >= *rhs_crit ) remainder = *lhs_crit - '0' - *rhs_crit - '0';
            else
            {
                *lhs_crit += 10;
                while( *( lhs_crit + ++count ) == '0' )
                {
                    *( lhs_crit + count ) = '9';
                }
                --*( lhs_crit + count );
            }
                remainder = *lhs_crit - '0' - (*rhs_crit - '0');
            ++lhs_crit;
            ++rhs_crit;
        }
        else
        {
            remainder = *lhs_crit - '0';
            ++lhs_crit;
        }
        temp += ( remainder + '0' );
    }
    while( temp.back() == '0' ) temp.pop_back();
    std::reverse( temp.begin() , temp.end() );
    value = temp;
    return( *this );
}

Integer operator-( const Integer &rhs , const Integer &lhs )
{
    Integer result( rhs );
    return( result -= lhs );
}

Integer& Integer::operator*=( const Integer &rhs )
{
    if( rhs == Integer( "1" ) ) return( *this );
    if( rhs == Integer( "0" ) )
    {
        value = "0";
        return( *this );
    }
    const Integer temp( *this );
    for( Integer i("0"); i < rhs - Integer( "1" ); ++i )
    {
        *this += temp;
    }
    return( *this );
}

Integer operator*( const Integer &lhs , const Integer &rhs )
{
    Integer result( rhs );
    return( result *= lhs );
}

Integer& Integer::operator/=( const Integer &rhs )
{
    if( rhs == Integer( "1" ) ) return( *this );
    assert( rhs != Integer( "0" ) );
    Integer count( "0" );
    while( *this >= rhs )
    {
        *this -= rhs;
        ++count;
    }
    *this = count;
    return( *this );
}

Integer operator/( const Integer &lhs , const Integer &rhs )
{
    Integer result( lhs );
    return( result /= rhs );
}

Integer& Integer::operator%=( const Integer &rhs )
{
    assert( rhs != Integer( "0" ) );
    if( rhs == Integer( "1" ) ) return( *this );
    if( rhs == Integer( "2" ) && rhs.value.back() % 2 == 0 )
    {
        value = "0";
        return( *this );
    }
    else
    {
        value = "1";
        return( *this );
    }
    while( *this >= rhs )
    {
        *this -= rhs;
    }
    return( *this );
}

Integer operator%( const Integer &lhs , const Integer &rhs )
{
    Integer result( lhs );
    return( result %= rhs );
}

bool operator==( const Integer &lhs , const Integer &rhs )
{
    return( lhs.value == rhs.value );
}

bool operator !=( const Integer &lhs , const Integer &rhs )
{
    return( !( lhs == rhs ) );
}

bool operator<( const Integer &lhs , const Integer &rhs )
{
    if( lhs.value.size() != rhs.value.size() ) return( lhs.value.size() < rhs.value.size() );
    return( lhs.value < rhs.value );
}

bool operator <=( const Integer &lhs , const Integer &rhs )
{
    return( ( lhs < rhs ) || ( lhs == rhs ) );
}

bool operator>( const Integer& lhs , const Integer &rhs )
{
    return( !( lhs < rhs ) && lhs != rhs );
}

bool operator>=( const Integer& lhs , const Integer &rhs )
{
    return( ( lhs > rhs ) || ( lhs == rhs ) );
}

Integer& Integer::operator++( void )
{
    return( *this += Integer( "1" ) );
}

Integer Integer::operator++( int )
{
    return( *this += Integer( "1" ) );
}

Integer& Integer::operator--( void )
{
    return( *this -= Integer( "1" ) );
}

Integer Integer::operator--( int )
{
    return( *this -= Integer( "1" ) );
}


std::ostream& operator<<( std::ostream &stm , const Integer &i )
{
    return( stm << i.value );
}
