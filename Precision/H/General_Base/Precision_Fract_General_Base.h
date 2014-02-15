#ifndef __PRECISION_FRACT_IMPL_H
#define __PRECISION_FRACT_IMPL_H

#include "Precision_Int_General_Base.h"
#include "Precision_Float_General_Base.h"

#include "Precision_Tags.h"
#include "Shared_Constants.h"

#include <vector>

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.
//Specifically for this fraction class, there is an additional parameter
//  used to represent the slash character as in "N/D". Defaulted to
//  CharT('/').

#define FRACT_TEMPL_            \
    template <                  \
        typename CharT,         \
        CharT const *const _0,  \
        std::ptrdiff_t Base,    \
        template <typename...>  \
            class Container,    \
        CharT _plus,            \
        CharT _neg,             \
        CharT _point,           \
        CharT _exp,             \
        CharT _space,           \
        CharT _slash            \
    >

#define INST_PARAMS_ CharT, _0, Base, Container,    \
        _plus, _neg, _point, _exp, _space

#define FRACT_INST_ Fract <INST_PARAMS_, _slash>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0, std::ptrdiff_t Base,
            template <typename...> class Container = std::vector,
            CharT _plus = CharT('+'), CharT _neg = CharT('-'),
            CharT _point = CharT('.'), CharT _exp = CharT('E'),
            CharT _space = CharT(' '), CharT _slash = CharT('/')
        >
        class Fract : Tag::Fraction, Tag::Signed {
            public:
                using Integer       = Int<INST_PARAMS_>;
                using Floating      = Float<INST_PARAMS_>;
                using str_type      = typename Integer::str_type;
                using sign_type     = typename Integer::sign_type;
                using image_type    = typename Integer::image_type;
                using diglist_type  = typename Integer::diglist_type;
                using digit_type    = typename Integer::digit_type;
                using digit_10_type = typename Integer::digit_10_type;
                using ld            = typename Floating::ld;
                using lli           = typename Integer::lli;
                using ulli          = unsigned long long int;
                using size_type     = typename Integer::size_type;
        //Arithmetic operators
                FRACT_INST_& operator+=(const FRACT_INST_&);
                FRACT_INST_& operator-=(const FRACT_INST_&);
                FRACT_INST_& operator*=(const FRACT_INST_&);
                FRACT_INST_& operator/=(const FRACT_INST_&);
                FRACT_INST_& operator%=(const FRACT_INST_&);
                FRACT_INST_& operator--();
                FRACT_INST_ operator--(int);
                FRACT_INST_& operator++();
                FRACT_INST_ operator++(int);

                FRACT_INST_ operator-()const;

        //Overloaded operators with new meanings
                    //Invert the fraction
                FRACT_INST_ operator~()const;
                    //Raise the fraction to the power of
                FRACT_INST_& operator^=(const FRACT_INST_&);
        //Read-only functions
                sign_type sign()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
                Integer numerator()const;
                Integer denominator()const;
                str_type str()const;
                str_type mixed()const;
            //Set the precision through parameter
                FRACT_INST_ magnitude()const;
                size_type precision()const;
                short compare(const FRACT_INST_&)const;
            //Following two pairs are merely different names for the same thing
                Integer whole()const;
                Floating decimal()const;
                Integer integer()const;
                Floating floating_point()const;
                Integer gcd(const FRACT_INST_&)const;
                FRACT_INST_ inverse()const;

                FRACT_INST_ remainder(const FRACT_INST_&)const;
                bool is_integer()const;
                image_type digit(size_type)const;
                digit_10_type digit_10(size_type)const;

                static constexpr digit_10_type base();
        //Other modifiers
                void precision(size_type);
                FRACT_INST_& invert();
                void sign(sign_type);
                void negate();
                void swap(FRACT_INST_& s);
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                FRACT_INST_& exponentiate(const Integer&);
                FRACT_INST_& exponentiate(const FRACT_INST_&, size_type = 0);

        //Overload cast operators
                explicit operator Integer() const;
                explicit operator Floating() const;

        //Constructors and destructor
                Fract(ld = 0.0, size_type = k_default_prec);
                Fract(const str_type&, size_type = k_default_prec);
                Fract(const Integer&, size_type = k_default_prec);
                Fract(const Floating&);
                explicit Fract(
                    const Integer&,
                    const Integer&,
                    size_type = k_default_prec
                );

                Fract(const FRACT_INST_&)                   =default;
                Fract(FRACT_INST_&&)                        =default;
                FRACT_INST_& operator=(const FRACT_INST_&)  =default;
                FRACT_INST_& operator=(FRACT_INST_&&)       =default;
                ~Fract()                                    =default;
            protected:
        //Helpers
                void Simplify();
                void Check_Pattern(const str_type&, const Floating&);
                Integer GCD_Helper(const Integer&, const Integer&)const;
                Integer GCF_Helper(const Integer&, const Integer&)const;
            private:
                Integer     m_numer, m_denom;
                size_type   m_precision;
                static constexpr size_type k_default_prec = 100;
        };

        FRACT_TEMPL_
        FRACT_INST_ operator+(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator-(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator*(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator/(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator%(FRACT_INST_, const FRACT_INST_&);

        FRACT_TEMPL_
        FRACT_INST_ operator^(FRACT_INST_, const FRACT_INST_&);

        FRACT_TEMPL_
        bool operator==(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator!=(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator>=(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator<=(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator>(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator<(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator!(const FRACT_INST_&);
    }
}

FRACT_TEMPL_
void swap(
    Precision::General_Base::FRACT_INST_&,
    Precision::General_Base::FRACT_INST_&
);

#include "Precision_Fract_General_Base.inl"

#undef FRACT_TEMPL_
#undef FRACT_INST_
#undef INST_PARAMS_

#endif  //Include guard