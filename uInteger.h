#ifndef INTEGER_H
#define INTEGER_H

#include <string>

class Integer;

Integer operator+( const Integer& , const Integer& );
Integer operator-( const Integer& , const Integer& );
Integer operator*( const Integer& , const Integer& );
Integer operator/( const Integer& , const Integer& );
Integer operator%( const Integer& , const Integer& );
Integer operator^( const Integer& , const Integer& );

bool operator!=( const Integer& , const Integer& );
bool operator<=( const Integer& , const Integer& );
bool operator>=( const Integer& , const Integer& );
bool operator>( const Integer& , const Integer& );

class Integer
{
    public:
        Integer( void );
        Integer( const Integer& );
        Integer( const std::string value );

        Integer& operator+=( const Integer& );
        Integer& operator-=( const Integer& );
        Integer& operator*=( const Integer& );
        Integer& operator/=( const Integer& );
        Integer& operator%=( const Integer& );

        friend bool operator==( const Integer& , const Integer& );
        friend bool operator<( const Integer& , const Integer& );

        Integer& operator<<( const Integer& );
        Integer& operator>>( const Integer& );

        Integer& operator++( void );
        Integer operator++( int );
        Integer& operator--( void );
        Integer operator--( int );

        friend std::ostream& operator<<( std::ostream& , const Integer& );

        /***Power***/
        Integer pow( const Integer& ) const; //*this to power of param
        Integer sq( void ) const; //square of *this
        Integer sqrt( void ) const; //square root of *this
        Integer cbrt( void ) const; //cube root of *this
        Integer hypot( const Integer& ) const; //*this == a | param == b | return == c

        /***Min/Max***/
        Integer dif( const Integer& ) const; //difference between *this and param
        Integer imax( const Integer& ) const; //return the greatest value *this or param
        Integer imin( const Integer& ) const; //return the minimum value *this or param

        /***Other***/
        Integer GCF( const Integer& ) const; //return the greatest common factor between *this and param
        Integer abs( void ) const; //return the absolute value of *this
        std::string to_binary( void ) const;  //return a string of the binary value

    private:
        std::string value;
};

#endif // INTEGER_H
