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
            using UInteger      = UInt;
            using Integer       = Int;
            using str_type      = Float::str_type;
            using ld            = Float::ld;
            using lli           = Float::lli;
            using diglist_type  = Float::diglist_type;
            using size_type     = Float::size_type;
            using sign_type     = Float::sign_type;
    //Arithmetic operators
            UFloat& operator+=(const UFloat& rhs){
                m_base += rhs.m_base;
                if(m_base.sign() < 0)
                    m_base = 0;
                return *this;
            }

            UFloat& operator-=(const UFloat& rhs){
                m_base -= rhs.m_base;
                if(m_base.sign() < 0)
                    m_base = 0;
                return *this;
            }

            UFloat& operator*=(const UFloat& rhs)
                {return m_base *= rhs.m_base, *this;}

            UFloat& operator/=(const UFloat& rhs)
                {return m_base /= rhs.m_base, *this;}

            UFloat& operator%=(const UFloat& rhs)
                {return m_base %= rhs.m_base, *this;}

            UFloat& operator--()
                {return --m_base, *this;}

            UFloat operator--(int)
                {return UFloat(m_base--);}

            UFloat& operator++()
                {return ++m_base, *this;}

            UFloat operator++(int)
                {return UFloat(m_base++);}

                //Returns the power of, not XOR
            UFloat& operator^=(const Integer& rhs)
                {return m_base ^= rhs, *this;}

            UFloat& operator^=(const UFloat& rhs)
                {return m_base ^= rhs.m_base, *this;}

    //Read-only functions
            sign_type sign()const
                {return 1;}

            str_type str(size_type inPrec = 0, bool inShowFull = false)const
                {return m_base.str(inPrec, inShowFull);}

            bool even()const
                {return m_base.even();}

            bool odd()const
                {return m_base.odd();}

        //Set the precision through parameter
            str_type sci_note(
                size_type inPrec = k_display_prec,
                bool inShowFull = false
            )const{return m_base.sci_note(inPrec, inShowFull);}

            str_type sci_note_w_spaces(
                size_type inPrec = k_display_prec,
                bool inShowFull = false
            )const{return m_base.sci_note_w_spaces(inPrec, inShowFull);}

            size_type count_digits()const
                {return m_base.count_digits();}

            size_type count_left_digits()const
                {return m_base.count_left_digits();}

            size_type count_right_digits()const
                {return m_base.count_right_digits();}

            size_type precision()const
                {return m_base.precision();}

            short compare(const UFloat& s)const
                {return m_base.compare(s.m_base);}

            Integer integer()const
                {return m_base.integer();}

            bool show_full()const
                {return m_base.show_full();}

            UFloat remainder(const UFloat& s)const
                {return UFloat(m_base.remainder(s.m_base));}

            Float base()const
                {return m_base;}
            
            Float operator-()const
                {return -m_base;}

            bool is_integer()const
                {return m_base.is_integer();}

            UFloat inverse()const
                {return UFloat(m_base.inverse());}

    //Other modifers
            void sign(sign_type){}

            bool show_full(bool inFlag)
                {return m_base.show_full(inFlag);}

                //Multiplies integer by a power of ten
            void shift(lli tens_exp)
                {m_base.shift(tens_exp);}

            void shift_left(size_type e)
                {m_base.shift_left(e);}

            void shift_right(size_type e)
                {m_base.shift_right(e);}

            UFloat& invert()
                {return m_base.invert(), *this;}

            void swap(UFloat& s)
                {m_base.swap(s.m_base);}

    //Overload cast operators
            explicit operator Integer() const
                {return static_cast<Integer>(m_base);}

            explicit operator UInteger() const
                {return static_cast<Integer>(m_base);}

    //Constructors and destructor
            UFloat(ld inFP = 0.0, size_type inPrec = k_default_prec)
                : m_base(inFP*(inFP>0?1:-1), inPrec)
            {}

            UFloat(
                const str_type& inImage,
                size_type inPrec = k_default_prec
            )
                : m_base(
                    inImage[0] == '-' || inImage[0] == '+'
                        ? inImage.substr(1) : inImage,
                    inPrec
                )
            {}

            explicit UFloat(
                const Integer& inInt,
                size_type inPrec = k_default_prec
            )
                : m_base(inInt, inPrec)
            {m_base.sign(1);}

            explicit UFloat(
                Integer&& inInt,
                size_type inPrec = k_default_prec
            )
                : m_base(std::move(inInt), inPrec)
            {m_base.sign(1);}

            explicit UFloat(
                const UInteger& inInt,
                size_type inPrec = k_default_prec
            )
                : m_base(inInt, inPrec)
            {m_base.sign(1);}

            explicit UFloat(
                UInteger&& inInt,
                size_type inPrec = k_default_prec
            )
                : m_base(std::move(inInt), inPrec)
            {m_base.sign(1);}

            explicit UFloat(const Float& inFP)
                : m_base(inFP)
            {m_base.sign(1);}

            explicit UFloat(Float&& inFP)
                : m_base(std::move(inFP))
            {m_base.sign(1);}

            UFloat(const UFloat&)               =default;
            UFloat(UFloat&&)                    =default;
            UFloat& operator=(const UFloat&)    =default;
            UFloat& operator=(UFloat&&)         =default;
            ~UFloat()                           =default;
        private:
            Float   m_base;
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

inline void swap(Precision::UFloat& a, Precision::UFloat& b)
    {a.swap(b);}

inline Precision::UFloat operator"" _Precision_UFloat(
    char const *const raw,
    size_t
){return Precision::UFloat::str_type(raw);}

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