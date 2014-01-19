#ifndef __PRECISION_UNSIGNED_INT_IMPL_H
#define __PRECISION_UNSIGNED_INT_IMPL_H

#include "Precision_Int.h"

#include <sstream>
#include <utility>

namespace Precision{
    class UInt{
        public:
    //Type aliases
            using str_type      = Int::str_type;
            using ulli          = unsigned long long int;
            using ld            = Int::ld;
            using lli           = Int::lli;
            using diglist_type  = Int::diglist_type;
            using digit_type    = Int::digit_type;
            using sign_type     = Int::sign_type;
            using size_type     = Int::size_type;
    //Arithmetic operators
            UInt& operator+=(const UInt& rhs){
                m_base += rhs.m_base;
                if(m_base.sign() < 0)
                    m_base = 0;
                return *this;
            }

            UInt& operator-=(const UInt& rhs){
                m_base -= rhs.m_base;
                if(m_base.sign() < 0)
                    m_base = 0;
                return *this;
            }

            UInt& operator*=(const UInt& rhs)
                {return m_base *= rhs.m_base, *this;}

            UInt& operator/=(const UInt& rhs)
                {return m_base /= rhs.m_base, *this;}

            UInt& operator%=(const UInt& rhs)
                {return m_base %= rhs.m_base, *this;}

            UInt& operator--()
                {return --m_base, *this;}

            UInt operator--(int)
                {return m_base--;}

            UInt& operator++()
                {return ++m_base, *this;}

            UInt operator++(int)
                {return m_base++;}

    //Bitwise operators
            UInt& operator&=(const UInt& rhs)
                {return m_base &= rhs.m_base, *this;}

            UInt& operator|=(const UInt& rhs)
                {return m_base |= rhs.m_base, *this;}

            UInt& operator^=(const UInt& rhs)
                {return m_base ^= rhs.m_base, *this;}

            UInt& operator<<=(const UInt& rhs)
                {return m_base <<= rhs.m_base, *this;}

            UInt& operator>>=(const UInt& rhs)
                {return m_base >>= rhs.m_base, *this;}

    //Read-only functions
            bool is_integer()const
                {return true;}

            sign_type sign()const
                {return 1;}

            str_type str()const
                {return m_base.str();}

            bool even()const
                {return m_base.even();}

            bool odd()const
                {return m_base.odd();}

        //Set the precision through parameter
            str_type sci_note(size_type inPrec = k_display_prec)const
                {return m_base.sci_note(inPrec);}

            str_type sci_note_w_spaces(size_type inPrec = k_display_prec)const
                {return m_base.sci_note_w_spaces(inPrec);}

            size_type count_digits()const
                {return m_base.count_digits();}

            short compare(const UInt& s)const
                {return m_base.compare(s.m_base);}

            Int base()const
                {return m_base;}

            Int operator-()const
                {return -m_base;}

                //Does not work for ~0
            Int operator~()const
                {return Int(~m_base);}

    //Other modifiers
            void sign(sign_type){}
                //Multiplies integer by a power of ten
            void shift(lli tens_exp)
                {m_base.shift(tens_exp);}

            void shift_left(size_type e)
                {m_base.shift_left(e);}

            void shift_right(size_type e)
                {m_base.shift_right(e);}

            void swap(UInt& s)
                {m_base.swap(s.m_base);}

    //Conversion operators
            explicit operator Int()
                {return m_base;}

    //Constructors and destructor
            UInt(ulli inInt = 0)
                : m_base(inInt)
            {}

            UInt(const str_type& inImage)
                : m_base(inImage)
            {m_base.sign(1);}

            UInt(const Int& inInt)
                : m_base(inInt)
            {m_base.sign(1);}

            UInt(Int&& inInt)
                : m_base(std::move(inInt))
            {m_base.sign(1);}

            UInt(const UInt&)               =default;
            UInt(UInt&&)                    =default;
            UInt& operator=(const UInt&)    =default;
            UInt& operator=(UInt&&)         =default;
            ~UInt()                         =default;
        private:
            Int   m_base;
    };

    inline UInt operator+(UInt lhs, const UInt& rhs)
        {return lhs += rhs;}
    inline UInt operator-(UInt lhs, const UInt& rhs)
        {return lhs -= rhs;}
    inline UInt operator*(UInt lhs, const UInt& rhs)
        {return lhs *= rhs;}
    inline UInt operator/(UInt lhs, const UInt& rhs)
        {return lhs /= rhs;}
    inline UInt operator%(UInt lhs, const UInt& rhs)
        {return lhs %= rhs;}

    inline UInt operator&(UInt lhs, const UInt& rhs)
        {return lhs &= rhs;}
    inline UInt operator|(UInt lhs, const UInt& rhs)
        {return lhs |= rhs;}
    inline UInt operator^(UInt lhs, const UInt& rhs)
        {return lhs ^= rhs;}
    inline UInt operator>>(UInt lhs, const UInt& rhs)
        {return lhs >>= rhs;}
    inline UInt operator<<(UInt lhs, const UInt& rhs)
        {return lhs <<= rhs;}

    inline bool operator==(const UInt& lhs, const UInt& rhs)
        {return lhs.compare(rhs) == 0;}
    inline bool operator!=(const UInt& lhs, const UInt& rhs)
        {return lhs.compare(rhs) != 0;}
    inline bool operator>=(const UInt& lhs, const UInt& rhs)
        {return lhs.compare(rhs) >= 0;}
    inline bool operator<=(const UInt& lhs, const UInt& rhs)
        {return lhs.compare(rhs) <= 0;}
    inline bool operator>(const UInt& lhs, const UInt& rhs)
        {return lhs.compare(rhs) > 0;}
    inline bool operator<(const UInt& lhs, const UInt& rhs)
        {return lhs.compare(rhs) < 0;}
    inline bool operator!(const UInt& testee)
        {return testee == 0;}
}

inline void swap(Precision::UInt& a, Precision::UInt& b)
    {a.swap(b);}

inline Precision::UInt operator"" _Precision_UInt(
    char const *const raw,
    size_t
){return Precision::UInt::str_type(raw);}

inline Precision::UInt operator"" _Precision_UInt_E(
    char const *const raw,
    size_t
){return operator"" _Precision_Int_E(raw, 0);}

inline Precision::UInt operator"" _Precision_UInt
    (unsigned long long cooked)
{return cooked;}

#endif
