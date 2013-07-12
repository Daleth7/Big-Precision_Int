#ifndef MATHEMATICSTOOLBOX_H
#define MATHEMATICSTOOLBOX_H

#include <vector>
#include <string>
#include <list>
#include <limits>
#include <cmath>

namespace MTool{
/*********************************************************************
                           Precision_Int
*********************************************************************/
/*********************************************************************************
            Add support for arithmetic with longI and comparison operators
*********************************************************************************/
    //Type aliases
    using str = std::string;
    using longI = long long int;
    using diglist = std::vector<longI>;
    
    class Precision_Int{
        public:
    //Arithmetic operators
            Precision_Int& operator+=(const Precision_Int&);
            Precision_Int& operator-=(const Precision_Int&);
            Precision_Int& operator*=(const Precision_Int&);
/*          Precision_Int& operator/=(const Precision_Int&);
            Precision_Int& operator%=(const Precision_Int&);
*/          Precision_Int& operator--();
            Precision_Int operator--(int);
            Precision_Int& operator++();
            Precision_Int operator++(int);
    //Comparison operators
        friend bool operator>
            (const Precision_Int&,const Precision_Int&);
        friend bool operator!(const Precision_Int&);
    //Read-only functions
            short sign()const;
            str string()const;
            str scientific_notation()const;
            str scientific_notation_with_spaces()const;
            Precision_Int Magnitude()const;
            size_t count_digits()const;
    //Constructors and destructor
            Precision_Int(longI=0);
            Precision_Int(diglist, short=1);

            Precision_Int(const Precision_Int&)             =default;
            Precision_Int(Precision_Int&&)                  =default;
            Precision_Int& operator=(const Precision_Int&)  =default;
            Precision_Int& operator=(Precision_Int&&)       =default;
            ~Precision_Int()                                =default;
    //Friends
            friend bool operator>=(const Precision_Int&, const Precision_Int&);
            friend bool operator==(const Precision_Int&, const Precision_Int&);
        private:
        //Numbers are stored in reverse, i.e. 190 040 002 would be
        //   stored as 002 040 190
            diglist __number;
            short __sign;
        //Each digit set is an unsigned long long int, so it can 
        //   handle at least 20 digits. In order to counter overflow,
        //   use 10^20 as the basis and set limit according to
        //   multiplication: sqrt(10^20)
            static constexpr longI
                __digitlimit = 10,
                __limit = 1e10
            ;
    };
    //Other overloaded operators
    Precision_Int operator+
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator-
        (const Precision_Int&, const Precision_Int&);
    Precision_Int operator*
        (const Precision_Int&, const Precision_Int&);
/*    Precision_Int operator/
        (const Precision_Int&, const Precision_Int&);
	Precision_Int operator%
        (const Precision_Int&, const Precision_Int&);
*/	Precision_Int operator-(const Precision_Int&);
    bool operator>(const Precision_Int&,const Precision_Int&);
    inline bool operator<(const Precision_Int&,const Precision_Int&);
    //inline bool operator>=(const Precision_Int&,const Precision_Int&);
    inline bool operator<=(const Precision_Int&,const Precision_Int&);
    //inline bool operator==(const Precision_Int&,const Precision_Int&);
    inline bool operator!=(const Precision_Int&,const Precision_Int&);
    inline bool operator!(const Precision_Int&);
    
    Precision_Int Pow(const Precision_Int&, const Precision_Int&);
    
    Precision_Int operator"" _Precision_Int(char const *const raw);
    Precision_Int operator"" _Precision_Int_E(char const *const raw);
}
/*********************************************
             End MTool Namespace
*********************************************/

#endif
