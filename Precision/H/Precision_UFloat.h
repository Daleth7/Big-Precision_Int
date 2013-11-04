#ifndef __PRECISION_UNSIGNED_FLOAT_IMPL_H
#define __PRECISION_UNSIGNED_FLOAT_IMPL_H

#include "Precision_Float.h"
#include "Precision_UInt.h"
#include "Impl/Shared_Constants.h"

#include <utility>

namespace Precision{
    class UFloat{
        public:
    //Type aliases
            using UInteger  = UInt;
            using Integer   = Int;
            using Str       = Float::Str;
            using ld        = Float::ld;
            using lli       = Float::lli;
            using diglist   = Float::diglist;
            using Size_Type = Float::Size_Type;
    //Arithmetic operators
            UFloat& operator+=(const UFloat& rhs){
                m_fbase += rhs.m_fbase;
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
                return *this;
            }

            UFloat& operator-=(const UFloat& rhs){
                m_fbase -= rhs.m_fbase;
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
                return *this;
            }

            UFloat& operator*=(const UFloat& rhs)
                {return m_fbase *= rhs.m_fbase, *this;}

            UFloat& operator/=(const UFloat& rhs)
                {return m_fbase /= rhs.m_fbase, *this;}

            UFloat& operator%=(const UFloat& rhs)
                {return m_fbase %= rhs.m_fbase, *this;}

            UFloat& operator--()
                {return --m_fbase, *this;}

            UFloat operator--(int)
                {return UFloat(m_fbase--);}

            UFloat& operator++()
                {return ++m_fbase, *this;}

            UFloat operator++(int)
                {return UFloat(m_fbase++);}

                //Returns the power of, not XOR
            UFloat& operator^=(const Integer& rhs)
                {return m_fbase ^= rhs, *this;}

            UFloat& operator^=(const UFloat& rhs)
                {return m_fbase ^= rhs.m_fbase, *this;}

    //Read-only functions
            Str str(
                Size_Type inPrec = 0,
                bool inShowFull = false
            )const{return m_fbase.str(inPrec, inShowFull);}

            bool even()const
                {return m_fbase.even();}

            bool odd()const
                {return m_fbase.odd();}

        //Set the precision through parameter
            Str sci_note(
                Size_Type inPrec = 0,
                bool inShowFull = false
            )const{return m_fbase.sci_note(inPrec, inShowFull);}

            Str sci_note_w_spaces(
                Size_Type inPrec = 0,
                bool inShowFull = false
            )const{return m_fbase.sci_note_w_spaces(inPrec, inShowFull);}

            Size_Type count_digits()const
                {return m_fbase.count_digits();}

            Size_Type count_left_digits()const
                {return m_fbase.count_left_digits();}

            Size_Type count_right_digits()const
                {return m_fbase.count_right_digits();}

            Size_Type precision()const
                {return m_fbase.precision();}

            short compare(const UFloat& s)const
                {return m_fbase.compare(s.m_fbase);}

            Integer integer()const
                {return m_fbase.integer();}

            bool show_full()const
                {return m_fbase.show_full();}

            UFloat remainder(const UFloat& s)const
                {return UFloat(m_fbase.remainder(s.m_fbase));}

            Float base()const
                {return m_fbase;}
            
            Float operator-()const
                {return -m_fbase;}

    //Other modifers
            bool show_full(bool inFlag)
                {return m_fbase.show_full(inFlag);}

                //Multiplies integer by a power of ten
            void shift(lli tens_exp)
                {m_fbase.shift(tens_exp);}

    //Overload cast operators
            explicit operator Integer() const
                {return static_cast<Integer>(m_fbase);}

            explicit operator UInteger() const
                {return static_cast<Integer>(m_fbase);}

    //Constructors and destructor
            UFloat(ld inFP = 0.0, Size_Type inPrec = k_default_prec)
                : m_fbase(inFP, inPrec)
            {}

            UFloat(
                const diglist& inImage,
                Size_Type inPrec = k_default_prec
            )
                : m_fbase(
                    inImage[0] == '-' || inImage[0] == '+'
                        ? inImage.substr(1) : inImage,
                    inPrec
                )
            {}

            explicit UFloat(
                const Integer& inInt,
                Size_Type inPrec = k_default_prec
            )
                : m_fbase(inInt, inPrec)
            {
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
            }

            explicit UFloat(
                Integer&& inInt,
                Size_Type inPrec = k_default_prec
            )
                : m_fbase(std::move(inInt), inPrec)
            {
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
            }

            explicit UFloat(
                const UInteger& inInt,
                Size_Type inPrec = k_default_prec
            )
                : m_fbase(inInt, inPrec)
            {
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
            }

            explicit UFloat(
                UInteger&& inInt,
                Size_Type inPrec = k_default_prec
            )
                : m_fbase(std::move(inInt), inPrec)
            {
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
            }

            explicit UFloat(const Float& inFP)
                : m_fbase(inFP)
            {
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
            }

            explicit UFloat(Float&& inFP)
                : m_fbase(std::move(inFP))
            {
                if(m_fbase.sign() < 0)
                    m_fbase = 0;
            }

            UFloat(const UFloat&)               =default;
            UFloat(UFloat&&)                    =default;
            UFloat& operator=(const UFloat&)    =default;
            UFloat& operator=(UFloat&&)         =default;
            ~UFloat()                           =default;
        private:
            Float   m_fbase;
    };

    inline UFloat operator+(UFloat lhs, const UFloat& rhs)
        {return lhs += rhs;}

    inline UFloat operator-(UFloat lhs, const UFloat& rhs)
        {return lhs -= rhs;}

    inline UFloat operator*(UFloat lhs, const UFloat& rhs)
        {return lhs *= rhs;}

    inline UFloat operator/(UFloat lhs, const UFloat& rhs)
        {return lhs /= rhs;}

    inline UFloat operator%(UFloat lhs, const UFloat& rhs)
        {return lhs %= rhs;}

    inline UFloat operator^(UFloat lhs, const UFloat::Integer& rhs)
        {return lhs ^= rhs;}

    inline UFloat operator^(UFloat lhs, const UFloat& rhs)
        {return lhs ^= rhs;}

    inline bool operator==(const UFloat& lhs, const UFloat& rhs)
        {return lhs.compare(rhs) == 0;}

    inline bool operator!=(const UFloat& lhs, const UFloat& rhs)
        {return lhs.compare(rhs) != 0;}

    inline bool operator>=(const UFloat& lhs, const UFloat& rhs)
        {return lhs.compare(rhs) >= 0;}

    inline bool operator<=(const UFloat& lhs, const UFloat& rhs)
        {return lhs.compare(rhs) <= 0;}

    inline bool operator>(const UFloat& lhs, const UFloat& rhs)
        {return lhs.compare(rhs) >= 0;}

    inline bool operator<(const UFloat& lhs, const UFloat& rhs)
        {return lhs.compare(rhs) <= 0;}

    inline bool operator!(const UFloat& testee)
        {return testee == 0;}
}

inline Precision::UFloat operator"" _Precision_UFloat(
    char const *const raw,
    size_t
){return Precision::UFloat::Str(raw);}

inline Precision::UFloat operator"" _Precision_UFloat_E(
    char const *const raw,
    size_t
){return Precision::UFloat(operator"" _Precision_Float_E(raw, 0));}

inline Precision::UFloat operator"" _Precision_UFloat
    (unsigned long long cooked)
{return Precision::UFloat(cooked);}

inline Precision::UFloat operator"" _Precision_UFloat
    (long double cooked)
{return Precision::UFloat(cooked);}

#endif