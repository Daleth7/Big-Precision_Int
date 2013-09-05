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
            using Integer   = Impl_Float_::Integer;
            using UInteger  = Impl_Float_::UInteger;
            using Str       = Impl_Float_::Str;
            using Sign      = Impl_Float_::Sign;
            using diglist   = Impl_Float_::diglist;
            using lli       = Impl_Float_::lli;
            using ld        = Impl_Float_::ld;
    //Arithmetic operators
            inline Float& operator+=(const Float& rhs)
                {return m_base += rhs.m_base, *this;}

            inline Float& operator-=(const Float& rhs)
                {return m_base -= rhs.m_base, *this;}

            inline Float& operator*=(const Float& rhs)
                {return m_base *= rhs.m_base, *this;}

            inline Float& operator/=(const Float& rhs)
                {return m_base /= rhs.m_base, *this;}

        //Returns the remainder, not the modulus
            inline Float& operator%=(const Float& rhs)
                {return m_base %= rhs.m_base, *this;}

        //Returns the power of, not the XOR
            inline Float& operator^=(const Integer& rhs)
                {return m_base ^= rhs, *this;}
/**********************Currently Not Completed************************/
            inline Float& operator^=(const Float& rhs)
                {return m_base ^= rhs.m_base, *this;}

            inline Float& operator--()
                {return (--m_base, *this);}

            inline Float operator--(int)
                {return Float(m_base++);}

            inline Float& operator++()
                {return ++m_base, *this;}

            inline Float operator++(int)
                {return Float(m_base++);}

            inline Float operator-()const
                {return Float(-m_base);}

    //Read-only functions
            inline Sign sign()const
                {return m_base.sign();}

            inline Str str(
                size_t inPrec = 0,
                bool inShowFull = false
            )const{return m_base.str(inPrec, inShowFull);}

        //Set the precision through parameter
            inline Str sci_note(
                size_t inPrec = k_display_prec,
                bool inShowFull = false
            )const{return m_base.sci_note(inPrec, inShowFull);}

            inline Str sci_note_w_spaces(
                size_t inPrec = k_display_prec,
                bool inShowFull = false
            )const{return m_base.sci_note_w_spaces(inPrec, inShowFull);}

            inline Float magnitude()const
                {return Float(m_base.magnitude());}

            inline size_t count_digits()const
                {return m_base.count_digits();}

            inline size_t count_left_digits()const
                {return m_base.count_left_digits();}

            inline size_t count_right_digits()const
                {return m_base.count_right_digits();}

            inline size_t precision()const
                {return m_base.precision();}

            inline short compare(const Float& s)const
                {return m_base.compare(s.m_base);}

            inline Integer integer()const
                {return m_base.integer();}

            inline bool show_full()const
                {return m_base.show_full();}

            inline Float remainder(const Float& s)const
                {return Float(m_base.remainder(s.m_base));}

    //Other modifers
            inline bool show_full(bool inFlag)
                {return m_base.show_full(inFlag);}

                //Multiplies integer by a power of ten
            inline void shift(lli tens_exp)
                {m_base.shift(tens_exp);}

    //Overload cast operators
            inline explicit operator Integer() const
                {return static_cast<Integer>(m_base);}

    //Constructors and destructor
            Float(ld inFP = 0.0, size_t inPrec = k_default_prec)
                : m_base(inFP, inPrec)
            {}

            Float(
                const diglist& inImage,
                size_t inPrec = k_default_prec
            )
                : m_base(inImage, inPrec)
            {}

            Float(const Integer& inInt, size_t inPrec = k_default_prec)
                : m_base(inInt, inPrec)
            {}

            Float(Integer&& inInt, size_t inPrec = k_default_prec)
                : m_base(std::move(inInt), inPrec)
            {}

            Float(const UInteger& inInt, size_t inPrec = k_default_prec)
                : m_base(inInt, inPrec)
            {}

            Float(UInteger&& inInt, size_t inPrec = k_default_prec)
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

    inline Float operator^(const Float& f, const Float::Integer& s)
        {return Float(f) ^= s;}

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
Precision::Float operator"" _Precision_Float(char const *const, size_t);
Precision::Float operator"" _Precision_Float_E(char const *const, size_t);
Precision::Float operator"" _Precision_Float(long double);
Precision::Float operator"" _Precision_Float(unsigned long long);

#endif