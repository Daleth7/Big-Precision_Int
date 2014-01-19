#ifndef __PRECISION_FLOAT_H
#define __PRECISION_FLOAT_H

#include "Impl/Precision_Float_Impl.h"
#include "Impl/Shared_Constants.h"

#include <utility>

/*********************************************************************
                           Float
*********************************************************************/
namespace Precision{
    class Float{
        public:
    //Type aliases
            using Integer       = Impl_Float_::Integer;
            using UInteger      = Impl_Float_::UInteger;
            using str_type      = Impl_Float_::str_type;
            using sign_type     = Impl_Float_::sign_type;
            using diglist_type  = Impl_Float_::diglist_type;
            using lli           = Impl_Float_::lli;
            using ld            = Impl_Float_::ld;
            using size_type     = Impl_Float_::size_type;
    //Arithmetic operators
            Float& operator+=(const Float& rhs)
                {return m_base += rhs.m_base, *this;}

            Float& operator-=(const Float& rhs)
                {return m_base -= rhs.m_base, *this;}

            Float& operator*=(const Float& rhs)
                {return m_base *= rhs.m_base, *this;}

            Float& operator/=(const Float& rhs)
                {return m_base /= rhs.m_base, *this;}

        //Returns the remainder, not the modulus
            Float& operator%=(const Float& rhs)
                {return m_base %= rhs.m_base, *this;}

        //Returns the power of, not the XOR
            Float& operator^=(const Float& rhs)
                {return m_base ^= rhs.m_base, *this;}

            Float& operator--()
                {return (--m_base, *this);}

            Float operator--(int)
                {return Float(m_base++);}

            Float& operator++()
                {return ++m_base, *this;}

            Float operator++(int)
                {return Float(m_base++);}

            Float operator-()const
                {return Float(-m_base);}

    //Read-only functions
            sign_type sign()const
                {return m_base.sign();}

            bool negative()const
                {return m_base.sign()<0;}

            bool positive()const
                {return m_base.sign()>0;}

            bool even()const
                {return m_base.even();}

            bool odd()const
                {return m_base.odd();}

            str_type str(
                size_type inPrec = 0,
                bool inShowFull = false
            )const{return m_base.str(inPrec, inShowFull);}

        //Set the precision through parameter
            str_type sci_note(
                size_type inPrec = k_display_prec,
                bool inShowFull = false
            )const{return m_base.sci_note(inPrec, inShowFull);}

            str_type sci_note_w_spaces(
                size_type inPrec = k_display_prec,
                bool inShowFull = false
            )const{return m_base.sci_note_w_spaces(inPrec, inShowFull);}

            Float magnitude()const
                {return Float(m_base.magnitude());}

            size_type count_digits()const
                {return m_base.count_digits();}

            size_type count_left_digits()const
                {return m_base.count_left_digits();}

            size_type count_right_digits()const
                {return m_base.count_right_digits();}

            size_type precision()const
                {return m_base.precision();}

            short compare(const Float& s)const
                {return m_base.compare(s.m_base);}

            Integer integer()const
                {return m_base.integer();}

            bool show_full()const
                {return m_base.show_full();}

            Float remainder(const Float& s)const
                {return Float(m_base.remainder(s.m_base));}

            bool is_integer()const
                {return m_base.is_integer();}

            Float inverse()const
                {return Float(m_base.inverse());}

    //Other modifers
            bool show_full(bool inFlag)
                {return m_base.show_full(inFlag);}

                //Multiplies integer by a power of ten
            void shift(lli tens_exp)
                {m_base.shift(tens_exp);}

            void shift_left(size_type e)
                {m_base.shift_left(e);}

            void shift_right(size_type e)
                {m_base.shift_right(e);}

            void sign(sign_type newsign)
                {m_base.sign(newsign);}

            void negate()
                {m_base.negate();}

            Float& exponentiate(const Float& e, size_type prec = 0)
                {return m_base.exponentiate(e.m_base, prec), *this;}

            Float& exp(const Integer& exponent)
                {return m_base.exponentiate(exponent), *this;}

            Float& exp(const Float& e, size_type prec)
                {return m_base.exponentiate(e.m_base, prec), *this;}

            Float& invert()
                {return m_base.invert(), *this;}

            void swap(Float& s)
                {m_base.swap(s.m_base);}

    //Overload cast operators
            explicit operator Integer() const
                {return static_cast<Integer>(m_base);}

    //Constructors and destructor
            Float(ld inFP = 0.0, size_type inPrec = k_default_prec)
                : m_base(inFP, inPrec)
            {}

            Float(
                const str_type& inImage,
                size_type inPrec = k_default_prec
            )
                : m_base(inImage, inPrec)
            {}

            Float(const Integer& inInt, size_type inPrec = k_default_prec)
                : m_base(inInt, inPrec)
            {}

            Float(Integer&& inInt, size_type inPrec = k_default_prec)
                : m_base(std::move(inInt), inPrec)
            {}

            Float(const UInteger& inInt, size_type inPrec = k_default_prec)
                : m_base(inInt, inPrec)
            {}

            Float(UInteger&& inInt, size_type inPrec = k_default_prec)
                : m_base(std::move(inInt), inPrec)
            {}

            explicit Float(const Impl_Float_& inFP)
                : m_base(inFP)
            {}

            explicit Float(Impl_Float_&& inFP)
                : m_base(std::move(inFP))
            {}

            Float(const Float&)             =default;
            Float(Float&&)                  =default;
            Float& operator=(const Float&)  =default;
            Float& operator=(Float&&)       =default;
            ~Float()                        =default;
        private:
            Impl_Float_ m_base;
    };
//Other overloaded operators
    inline Float operator+(const Float& f, const Float& s)
        {return Float(f) += s;}

    inline Float operator-(const Float& f, const Float& s)
        {return Float(f) -= s;}

    inline Float operator*(const Float& f, const Float& s)
        {return Float(f) *= s;}

    inline Float operator/(const Float& f, const Float& s)
        {return Float(f) /= s;}

    inline Float operator%(const Float& f, const Float& s)
        {return Float(f) %= s;}

    inline Float operator^(const Float& f, const Float& s)
        {return Float(f) ^= s;}

    inline bool operator>(const Float& f, const Float& s)
        {return (f.compare(s) > 0);}

    inline bool operator<(const Float& f, const Float& s)
        {return (f.compare(s) < 0);}

    inline bool operator>=(const Float& f, const Float& s)
        {return (f.compare(s) >= 0);}

    inline bool operator<=(const Float& f, const Float& s)
        {return (f.compare(s) <= 0);}

    inline bool operator==(const Float& f, const Float& s)
        {return (f.compare(s) == 0);}

    inline bool operator!=(const Float& f, const Float& s)
        {return (f.compare(s) != 0);}

    inline bool operator!(const Float& testee)
        {return testee == 0;}

//Other related functions
    inline short Compare(const Float& f, const Float& s)
        {return f.compare(s);}
}

inline void swap(Precision::Float& a, Precision::Float& b)
    {a.swap(b);}

Precision::Float operator"" _Precision_Float(char const *const, size_t);
Precision::Float operator"" _Precision_Float_E(char const *const, size_t);
Precision::Float operator"" _Precision_Float(long double);
Precision::Float operator"" _Precision_Float(unsigned long long);

#endif