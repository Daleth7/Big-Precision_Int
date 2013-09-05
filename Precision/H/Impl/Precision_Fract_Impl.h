#ifndef __PRECISION_FRACT_IMPL_H
#define __PRECISION_FRACT_IMPL_H

#include "Precision_Int.h"
#include "Precision_Float.h"

#include <string>

class Impl_Fract_{
    public:
        using Integer   = Precision::Int;
        using Float     = Precision::Float;
        using Str       = std::string;
        using Sign      = Precision::Int::Sign;
        using ld        = Precision::Float::ld;
        using lli       = Precision::Int::lli;
        using ulli      = unsigned long long int;
//Arithmetic operators
        Impl_Fract_& operator+=(const Impl_Fract_&);
        Impl_Fract_& operator-=(const Impl_Fract_&);
        Impl_Fract_& operator*=(const Impl_Fract_&);
        Impl_Fract_& operator/=(const Impl_Fract_&);
        Impl_Fract_& operator%=(const Impl_Fract_&);
        Impl_Fract_& operator--();
        Impl_Fract_ operator--(int);
        Impl_Fract_& operator++();
        Impl_Fract_ operator++(int);

        Impl_Fract_ operator-()const;

//Overloaded operators with new meanings
            //Invert the fraction
        Impl_Fract_ operator~()const;
            //Raise the fraction to the power of
        Impl_Fract_ operator^=(const Integer&);
        Impl_Fract_ operator^=(const Impl_Fract_&);
//Read-only functions
        Sign sign()const;
        Integer numerator()const;
        Integer denominator()const;
        Str str()const;
        Str mixed()const;
    //Set the precision through parameter
        Impl_Fract_ magnitude()const;
        size_t precision()const;
        short compare(const Impl_Fract_&)const;
    //Following two pairs are merely different names for the same thing
        Integer whole()const;
        Float decimal()const;
        Integer integer()const;
        Float floating_point()const;
        Integer gcd(const Impl_Fract_&)const;

        Impl_Fract_ remainder(const Impl_Fract_&)const;
//Other modifiers
        void precision(size_t);
//Overload cast operators
        explicit operator Integer() const;
        explicit operator Float() const;
//Constructors and destructor
        Impl_Fract_(ld = 0.0, size_t = k_default_prec);
        Impl_Fract_(Str, size_t = k_default_prec);
        Impl_Fract_(const Integer&, size_t = k_default_prec);
        Impl_Fract_(const Float&);
        Impl_Fract_(
            const Integer&,
            const Integer&,
            size_t = k_default_prec
        );

        Impl_Fract_(const Impl_Fract_&)             =default;
        Impl_Fract_(Impl_Fract_&&)                  =default;
        Impl_Fract_& operator=(const Impl_Fract_&)  =default;
        Impl_Fract_& operator=(Impl_Fract_&&)       =default;
        ~Impl_Fract_()                              =default;
    public:
//Helpers
        void Simplify();
    private:
        Integer
                m_numer,
                m_denom
        ;
        size_t  m_precision;
        static constexpr size_t k_default_prec = 100;
};

Impl_Fract_ operator+(Impl_Fract_, const Impl_Fract_&);
Impl_Fract_ operator-(Impl_Fract_, const Impl_Fract_&);
Impl_Fract_ operator*(Impl_Fract_, const Impl_Fract_&);
Impl_Fract_ operator/(Impl_Fract_, const Impl_Fract_&);
Impl_Fract_ operator%(Impl_Fract_, const Impl_Fract_&);

Impl_Fract_ operator^(Impl_Fract_, const Impl_Fract_&);

bool operator==(const Impl_Fract_&, const Impl_Fract_&);
bool operator!=(const Impl_Fract_&, const Impl_Fract_&);
bool operator>=(const Impl_Fract_&, const Impl_Fract_&);
bool operator<=(const Impl_Fract_&, const Impl_Fract_&);
bool operator>(const Impl_Fract_&, const Impl_Fract_&);
bool operator<(const Impl_Fract_&, const Impl_Fract_&);
bool operator!(const Impl_Fract_&);

#endif