#ifndef PRECISION_INT_H
#define PRECISION_INT_H

#include <vector>
#include <string>
#include <list>
#include <limits>
#include <cmath>

/*********************************************************************
                           Precision_Int
*********************************************************************/
namespace MTool{
    //Type aliases
    using str           = std::string;
    using longI         = long long int;
    using longUI        = unsigned long long int;
    using diglist_s     = std::string;
    using dig           = char;
    using ld            = long double;

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
    //Read-only functions
            short sign()const;
            str string()const;
        //Set the precision through parameter
            str scientific_notation(size_t=3)const;
            str scientific_notation_with_spaces(size_t=3)const;
            Precision_Int Magnitude()const;
            size_t count_digits()const;
            short compare(const Precision_Int&)const;
    //Constructors and destructor
            Precision_Int(longI=0);
            Precision_Int(diglist_s, short=1);

            Precision_Int(const Precision_Int&)             =default;
            Precision_Int(Precision_Int&&)                  =default;
            Precision_Int& operator=(const Precision_Int&)  =default;
            Precision_Int& operator=(Precision_Int&&)       =default;
            ~Precision_Int()                                =default;
        private:
        //Numbers are stored in reverse, e.g. 190 040 002 would be
        //   stored as 002 040 190. The number is reversed because
        //   the length is varied according to the leftmost side.
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
    inline bool operator>(const Precision_Int&,const Precision_Int&);
    inline bool operator<(const Precision_Int&,const Precision_Int&);
    inline bool operator>=(const Precision_Int&,const Precision_Int&);
    inline bool operator<=(const Precision_Int&,const Precision_Int&);
    inline bool operator==(const Precision_Int&,const Precision_Int&);
    inline bool operator!=(const Precision_Int&,const Precision_Int&);
    inline bool operator!(const Precision_Int&);
//Other related functions
    short Compare(const Precision_Int&, const Precision_Int&);
    Precision_Int Pow(const Precision_Int&, const Precision_Int&);
    Precision_Int Factorial(const Precision_Int&);
    Precision_Int Log(const Precision_Int&, const Precision_Int&);
//Trigonomic functions -- default is radians
    //sin needs to make an internal copy anyway, so make non-const
    double Sin(Precision_Int);
    double Cos(const Precision_Int&);
    double Tan(const Precision_Int&);
    double Csc(const Precision_Int&);
    double Sec(const Precision_Int&);
    double Cot(const Precision_Int&);
    //Note: support no arcFOO functions because their domains suggest
    //   no need for Precision_Int
}
MTool::Precision_Int operator""
    _Precision_Int(char const *const, size_t);
MTool::Precision_Int operator""
    _Precision_Int_E(char const *const, size_t);
MTool::Precision_Int operator""
    _Precision_Int(unsigned long long);
/*********************************************************************
                           Precision_Float
*********************************************************************/
namespace MTool{
    class Precision_Float{
        public:
    //Arithmetic operators
            Precision_Float& operator+=(const Precision_Float&);
            Precision_Float& operator-=(const Precision_Float&);
            Precision_Float& operator*=(const Precision_Float&);
            Precision_Float& operator/=(const Precision_Float&);
            Precision_Float& operator%=(const Precision_Float&);
            Precision_Float& operator--();
            Precision_Float operator--(int);
            Precision_Float& operator++();
            Precision_Float operator++(int);
    //Read-only functions
            short sign()const;
            str string(Precision_Int = -1)const;
        //Set the precision through parameter
            str scientific_notation(Precision_Int = -1)const;
            str scientific_notation_with_spaces(
                Precision_Int = -1)const;
            Precision_Float Magnitude()const;
            size_t count_digits()const;
            size_t count_left_digits()const;
            size_t count_right_digits()const;
            Precision_Int precision()const;
            short compare(const Precision_Float&)const;
            Precision_Int integer()const;
    //Overload cast operators
            explicit operator Precision_Int() const;
    //Constructors and destructor
            Precision_Float(ld=0.0, Precision_Int = 50);
            Precision_Float(
                diglist_s,
                short=1,
                Precision_Int = 50
            );
            Precision_Float(
                const Precision_Int&,
                Precision_Int = 50
            );

            Precision_Float(const Precision_Float&)         =default;
            Precision_Float(Precision_Float&&)              =default;
            Precision_Float& operator=(const Precision_Float&)
                                                            =default;
            Precision_Float& operator=(Precision_Float&&)   =default;
            ~Precision_Float()                              =default;
        protected:
    //Helpers
            void Update_Precision(const Precision_Int&);
        private:
            Precision_Int   m_integer;
        //Unlike Precision_Int, numbers are stored as seen, e.g.
        //   0.00298 will be stored as 298. This opposition is
        //   because the length will vary according to the
        //   rightside instead.
            str             m_decimal;
        //This stores how many digits are after the decimal point.
        // So for example 0.00047 will be stored as:
        //    m_decimal - 47
        //    m_d_count - 5
            Precision_Int
                            m_d_count,
                            m_precision
            ;
            static constexpr short __limit = 10;
    };
    //Other overloaded operators
    Precision_Float operator+
        (const Precision_Float&, const Precision_Float&);
    Precision_Float operator-
        (const Precision_Float&, const Precision_Float&);
    Precision_Float operator*
        (const Precision_Float&, const Precision_Float&);
    Precision_Float operator/
        (const Precision_Float&, const Precision_Float&);
    Precision_Float operator%
        (const Precision_Float&, const Precision_Float&);
    Precision_Float operator-(const Precision_Float&);
    inline bool operator>
        (const Precision_Float&,const Precision_Float&);
    inline bool operator<
        (const Precision_Float&,const Precision_Float&);
    inline bool operator>=
        (const Precision_Float&,const Precision_Float&);
    inline bool operator<=
        (const Precision_Float&,const Precision_Float&);
    inline bool operator==
        (const Precision_Float&,const Precision_Float&);
    inline bool operator!=
        (const Precision_Float&,const Precision_Float&);
    inline bool operator!(const Precision_Float&);
//Other related functions
    short Compare(const Precision_Float&, const Precision_Float&);
    Precision_Float fPow(const Precision_Float&, Precision_Int);
    Precision_Float fPow(const Precision_Float&, const Precision_Float&);
    Precision_Float Remainder
        (const Precision_Float&, const Precision_Float&);
/* Support only after studying mathematical gamma function for factorials
    Precision_Float Factorial(const Precision_Float&);
*/
//Trigonomic functions -- default is radians
    Precision_Float Sin(const Precision_Float&);
    Precision_Float Cos(const Precision_Float&);
    Precision_Float Tan(const Precision_Float&);
    Precision_Float Csc(const Precision_Float&);
    Precision_Float Sec(const Precision_Float&);
    Precision_Float Cot(const Precision_Float&);
    //Note: Consider support for arcFOO functions if
    //   implementation manually calculates values
}
MTool::Precision_Float operator""
    _Precision_Float(char const *const, size_t);
MTool::Precision_Float operator""
    _Precision_Float_E(char const *const, size_t);
MTool::Precision_Float operator""
    _Precision_Float(long double);
#endif
