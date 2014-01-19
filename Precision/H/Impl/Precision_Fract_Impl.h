#ifndef __PRECISION_FRACT_IMPL_H
#define __PRECISION_FRACT_IMPL_H

#include "Precision_Int.h"
#include "Precision_Float.h"

#include <string>

class Impl_Fract_{
    public:
        using Integer   = Precision::Int;
        using Float     = Precision::Float;
        using str_type  = std::string;
        using sign_type = Integer::sign_type;
        using ld        = Float::ld;
        using lli       = Integer::lli;
        using ulli      = unsigned long long int;
        using size_type = Integer::size_type;
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
        Impl_Fract_ operator^=(const Impl_Fract_&);
//Read-only functions
        sign_type sign()const;
        bool even()const;
        bool odd()const;
        Integer numerator()const;
        Integer denominator()const;
        str_type str()const;
        str_type mixed()const;
    //Set the precision through parameter
        Impl_Fract_ magnitude()const;
        size_type precision()const;
        short compare(const Impl_Fract_&)const;
    //Following two pairs are merely different names for the same thing
        Integer whole()const;
        Float decimal()const;
        Integer integer()const;
        Float floating_point()const;
        Integer gcd(const Impl_Fract_&)const;
        Impl_Fract_ inverse()const;

        Impl_Fract_ remainder(const Impl_Fract_&)const;
        bool is_integer()const;
//Other modifiers
        void precision(size_type);
        Impl_Fract_& invert();
        void sign(sign_type);
        void negate();
        void swap(Impl_Fract_& s);
        void shift(lli);
        void shift_left(size_type);
        void shift_right(size_type);
        Impl_Fract_& exponentiate(const Integer&);
        Impl_Fract_& exponentiate(const Impl_Fract_&, size_type = 0);

//Overload cast operators
        explicit operator Integer() const;
        explicit operator Float() const;

//Constructors and destructor
        Impl_Fract_(ld = 0.0, size_type = k_default_prec);
        Impl_Fract_(str_type, size_type = k_default_prec);
        Impl_Fract_(const Integer&, size_type = k_default_prec);
        Impl_Fract_(const Float&);
        explicit Impl_Fract_(
            const Integer&,
            const Integer&,
            size_type = k_default_prec
        );

        Impl_Fract_(const Impl_Fract_&)             =default;
        Impl_Fract_(Impl_Fract_&&)                  =default;
        Impl_Fract_& operator=(const Impl_Fract_&)  =default;
        Impl_Fract_& operator=(Impl_Fract_&&)       =default;
        ~Impl_Fract_()                              =default;
    public:
//Helpers
        void Simplify();
        void Check_Pattern(const str_type&, const Float&);
        Integer GCD_Helper(const Integer&, const Integer&)const;
        Integer GCF_Helper(const Integer&, const Integer&)const;
    private:
        Integer
                m_numer,
                m_denom
        ;
        size_type  m_precision;
        static constexpr size_type k_default_prec = 100;
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

void swap(Impl_Fract_&, Impl_Fract_&);

#endif