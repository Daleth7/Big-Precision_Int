#ifndef __PRECISION_UNSIGNED_INT_IMPL_H
#define __PRECISION_UNSIGNED_INT_IMPL_H

#include "Precision_Int.h"

#include <sstream>
#include <utility>

namespace Precision{
    class UInt{
        public:
    //Type aliases
            using Str       = Int::Str;
            using ulli      = unsigned long long int;
            using ld        = Int::ld;
            using lli       = Int::lli;
            using diglist   = Int::diglist;
            using digit     = Int::digit;
            using Sign      = Int::Sign;
            using Size_Type = Int::Size_Type;
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
            Str str()const
                {return m_base.str();}

            bool even()const
                {return m_base.even();}

            bool odd()const
                {return m_base.odd();}
                
        //Set the precision through parameter
            Str sci_note(Size_Type inPrec = k_display_prec)const
                {return m_base.sci_note(inPrec);}
                
            Str sci_note_w_spaces(Size_Type inPrec = k_display_prec)const
                {return m_base.sci_note_w_spaces(inPrec);}
                
            Size_Type count_digits()const
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
                //Multiplies integer by a power of ten
            void shift(lli tens_exp)
                {m_base.shift(tens_exp);}
                
    //Conversion operators
            explicit operator Int()
                {return m_base;}
                
    //Constructors and destructor
            UInt(ulli inInt = 0);
            
            UInt(const diglist& inImage);

            UInt(const Int& inInt);
            
            UInt(Int&& inInt);

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
inline Precision::UInt operator"" _Precision_UInt(
    char const *const raw,
    size_t
){return Precision::UInt::Str(raw);}

inline Precision::UInt operator"" _Precision_UInt_E(
    char const *const raw,
    size_t
){return operator"" _Precision_Int_E(raw, 0);}

inline Precision::UInt operator"" _Precision_UInt
    (unsigned long long cooked)
{return cooked;}

#endif