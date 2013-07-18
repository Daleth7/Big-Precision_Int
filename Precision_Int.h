#ifndef PRECISION_INT_H
#define PRECISION_INT_H

#include <vector>
#include <string>
#include <list>
#include <limits>
#include <cmath>

namespace MTool{
/*********************************************************************
                           Precision_Int
*********************************************************************/
    //Type aliases
    using str         = std::string;
    using longI       = long long int;
    using longUI      = unsigned long long int;
    using diglist_s   = std::string;
    using dig         = char;

    class Precision_Int{
        public:
    //Arithmetic operators
            Precision_Int& operator+=(const Precision_Int&);
            Precision_Int& operator-=(const Precision_Int&);
            Precision_Int& operator*=(const Precision_Int&);
            Precision_Int& operator/=(const Precision_Int&);
            Precision_Int& operator%=(const Precision_Int&);
            Precision_Int& operator--();
            Precision_Int operator--(int);
            Precision_Int& operator++();
            Precision_Int operator++(int);
    //Bitwise operators
            Precision_Int& operator&=(const Precision_Int&);
            Precision_Int& operator|=(const Precision_Int&);
            Precision_Int& operator^=(const Precision_Int&);
            Precision_Int& operator<<=(const Precision_Int&);
            Precision_Int& operator>>=(const Precision_Int&);
    //Comparison operators
            friend bool operator>
                (const Precision_Int&,const Precision_Int&);
            friend bool operator!(const Precision_Int&);
    //Read-only functions
            short sign()const;
            str string()const;
    //Set the precision through parameter
            str scientific_notation(size_t=3)const;
            str scientific_notation_with_spaces(size_t=3)const;
            Precision_Int Magnitude()const;
            size_t count_digits()const;
    //Constructors and destructor
            Precision_Int(longI=0);
            Precision_Int(diglist_s, short=1);

            Precision_Int(const Precision_Int&)             =default;
            Precision_Int(Precision_Int&&)                  =default;
            Precision_Int& operator=(const Precision_Int&)  =default;
            Precision_Int& operator=(Precision_Int&&)       =default;
            ~Precision_Int()                                =default;
    //Friends
            friend bool operator>=(const Precision_Int&,
                const Precision_Int&);
            friend bool operator==(const Precision_Int&, const
                Precision_Int&);
            friend double sin(Precision_Int);
        private:
        //Numbers are stored in reverse, i.e. 190 040 002 would be
        //   stored as 002 040 190
            diglist_s __number;
            short __sign;
            static constexpr short __limit = 10;
    };
    //Other overloaded operators
    Precision_Int operator+
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator-
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator*
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator/
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator%
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator&
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator|
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator^
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator<<
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator>>
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator-(const Precision_Int&);
    bool operator>(const Precision_Int&,const Precision_Int&);
    inline bool operator<(const Precision_Int&,const Precision_Int&);
    inline bool operator>=(const Precision_Int&,const Precision_Int&);
    inline bool operator<=(const Precision_Int&,const Precision_Int&);
    inline bool operator==(const Precision_Int&,const Precision_Int&);
    inline bool operator!=(const Precision_Int&,const Precision_Int&);
    inline bool operator!(const Precision_Int&);

    Precision_Int Pow(const Precision_Int&, const Precision_Int&);
    Precision_Int Factorial(const Precision_Int&);
//Trigonomic functions -- default is radians
    //sin needs to make an internal copy anyway, so make non-const
    double sin(Precision_Int);
    double cos(const Precision_Int&);
    double tan(const Precision_Int&);
    double csc(const Precision_Int&);
    double sec(const Precision_Int&);
    double cotan(const Precision_Int&);
    //Note: make no arcFOO functions because their domains suggest
    //   no need for Precision_Int
}
MTool::Precision_Int operator""
    _Precision_Int(char const *const, size_t);
MTool::Precision_Int operator""
    _Precision_Int_E(char const *const, size_t);
MTool::Precision_Int operator""
    _Precision_Int(unsigned long long);
/*********************************************
             End MTool Namespace
*********************************************/

#endif
