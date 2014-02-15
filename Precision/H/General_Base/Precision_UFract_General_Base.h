#ifndef __PRECISION_UNSIGNED_FRACT_IMPL_H
#define __PRECISION_UNSIGNED_FRACT_IMPL_H

#include "Precision_Fract_General_Base.h"

#include "Precision_Tags.h"
#include "Shared_Constants.h"

#include <vector>

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define UFRACT_TEMPL_           \
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

#define UFRACT_INST_ UFract <INST_PARAMS_, _slash>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0, std::ptrdiff_t Base,
            template <typename...> class Container = std::vector,
            CharT _plus = CharT('+'), CharT _neg = CharT('-'),
            CharT _point = CharT('.'), CharT _exp = CharT('E'),
            CharT _space = CharT(' '), CharT _slash = CharT('/')
        >
        class UFract : Tag::Fraction, Tag::Unsigned {
            public:
                using Signed_Fract  = Fract <INST_PARAMS_>;
                using Integer       = typename Signed_Fract::Integer;
                using Floating      = typename Signed_Fract::Floating;
                using str_type      = typename Signed_Fract::str_type;
                using sign_type     = typename Signed_Fract::sign_type;
                using image_type    = typename Signed_Fract::image_type;
                using diglist_type  = typename Signed_Fract::diglist_type;
                using digit_type    = typename Signed_Fract::digit_type;
                using digit_10_type = typename Signed_Fract::digit_10_type;
                using ld            = typename Signed_Fract::ld;
                using lli           = typename Signed_Fract::lli;
                using ulli          = typename Signed_Fract::ulli;
                using size_type     = typename Signed_Fract::size_type;
        //Arithmetic operators
                UFRACT_INST_& operator+=(const UFRACT_INST_& s)
                    {return m_base += s.m_base, *this;}

                UFRACT_INST_& operator-=(const UFRACT_INST_& s)
                    {return m_base -= s.m_base, *this;}

                UFRACT_INST_& operator*=(const UFRACT_INST_& s)
                    {return m_base *= s.m_base, *this;}

                UFRACT_INST_& operator/=(const UFRACT_INST_& s)
                    {return m_base /= s.m_base, *this;}

                UFRACT_INST_& operator%=(const UFRACT_INST_& s)
                    {return m_base %= s.m_base, *this;}

                UFRACT_INST_& operator--()
                    {return --m_base, *this;}

                UFRACT_INST_ operator--(int)
                    {return m_base--;}

                UFRACT_INST_& operator++()
                    {return ++m_base, *this;}

                UFRACT_INST_ operator++(int)
                    {return m_base++;}

                Signed_Fract operator-()const
                    {return -m_base;}

        //Overloaded operators with new meanings
                    //Invert the fraction
                UFRACT_INST_ operator~()const
                    {return ~m_base;}

                    //Raise the fraction to the power of
                UFRACT_INST_& operator^=(const UFRACT_INST_& e)
                    {return m_base ^= e.m_base, *this;}

        //Read-only functions
                sign_type sign()const
                    {return 1;}

                bool even()const
                    {return m_base.even();}

                bool odd()const
                    {return m_base.odd();}

                bool positive()const
                    {return true;}

                bool negative()const
                    {return false;}

                Integer numerator()const
                    {return m_base.numerator();}

                Integer denominator()const
                    {return m_base.denominator();}

                str_type str()const
                    {return m_base.str();}

                str_type mixed()const
                    {return m_base.mixed();}

            //Set the precision through parameter
                UFRACT_INST_ magnitude()const
                    {return m_base.magnitude();}

                size_type precision()const
                    {return m_base.precision();}

                short compare(const UFRACT_INST_& s)const
                    {return m_base.compare(s.m_base);}

            //Following two pairs are merely different names for the same thing
                Integer whole()const
                    {return m_base.whole();}

                Floating decimal()const
                    {return m_base.decimal();}

                Integer integer()const
                    {return m_base.integer();}

                Floating floating_point()const
                    {return this->decimal();}

                Integer gcd(const UFRACT_INST_& s)const
                    {return m_base.gcd(s.m_base);}

                UFRACT_INST_ inverse()const
                    {return m_base.inverse();}

                UFRACT_INST_ remainder(const UFRACT_INST_& s)const
                    {return m_base.remainder(s.m_base);}

                bool is_integer()const
                    {return m_base.is_integer();}

                const Signed_Fract& get_signed()const
                    {return m_base;}

                static constexpr digit_10_type base()
                    {return Signed_Fract::base();}

        //Other modifiers
                void precision(size_type p)
                    {m_base(p);}

                UFRACT_INST_& invert()
                    {return m_base.invert(), *this;}

                void sign(sign_type){}

                void negate(){}

                void swap(UFRACT_INST_& s)
                    {m_base.swap(s.m_base);}

                void shift(lli e)
                    {m_base.shift(e);}

                void shift_left(size_type e)
                    {m_base.shift_left(e);}

                void shift_right(size_type e)
                    {m_base.shift_right(e);}

                UFRACT_INST_& exponentiate(const Integer& e)
                    {return m_base.exponentiate(e), *this;}
                UFRACT_INST_& exponentiate(
                    const UFRACT_INST_& s,
                    size_type p = 0
                ){return m_base.exponentiate(s, p), *this;}

        //Overload cast operators
                explicit operator Integer() const
                    {return this->integer();}

                explicit operator Floating() const
                    {return this->decimal();}

        //Constructors and destructor
                UFract(ld d = 0.0, size_type p = k_default_prec)
                    : m_base(d, p)
                {}

                UFract(str_type i, size_type p = k_default_prec)
                    : m_base(i, p)
                {}

                UFract(const Integer& i, size_type p = k_default_prec)
                    : m_base(i, p)
                {}

                UFract(const Floating& f)
                    : m_base(f)
                {}

                explicit UFract(
                    const Integer& n,
                    const Integer& d,
                    size_type p = k_default_prec
                )
                    : m_base(n, d, p)
                {}

                UFract(const Signed_Fract& newbase)
                    : m_base(newbase)
                {}

                UFract(Signed_Fract&& newbase)
                    : m_base(std::move(newbase))
                {}

                UFract(const UFRACT_INST_&)                     =default;
                UFract(UFRACT_INST_&&)                          =default;
                UFRACT_INST_& operator=(const UFRACT_INST_&)    =default;
                UFRACT_INST_& operator=(UFRACT_INST_&&)         =default;
                ~UFract()                                       =default;
            private:
                Signed_Fract m_base;
        };

        UFRACT_TEMPL_
        UFRACT_INST_ operator+(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f += s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator-(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f -= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator*(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f *= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator/(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f /= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator%(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f %= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator^(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f ^= s;}

        UFRACT_TEMPL_
        bool operator==(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) == 0;}

        UFRACT_TEMPL_
        bool operator!=(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) != 0;}

        UFRACT_TEMPL_
        bool operator>=(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) >= 0;}

        UFRACT_TEMPL_
        bool operator<=(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) <= 0;}

        UFRACT_TEMPL_
        bool operator>(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) > 0;}

        UFRACT_TEMPL_
        bool operator<(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) < 0;}

        UFRACT_TEMPL_
        bool operator!(const UFRACT_INST_& f)
            {return f.compare(UFRACT_INST_(0)) == 0;}
    }
}

UFRACT_TEMPL_
void swap(
    Precision::General_Base::UFRACT_INST_& a,
    Precision::General_Base::UFRACT_INST_& b
){a.swap(b);}

#undef UFRACT_TEMPL_
#undef UFRACT_INST_
#undef INST_PARAMS_

#endif  //Include guard