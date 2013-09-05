#ifndef __PRECISION_INT_H
#define __PRECISION_INT_H

#include "Impl/Precision_Int_Impl.h"

#include <utility>

namespace Precision{
    class Int{
        public:
    //Type aliases
            using Str       = Impl_Int_::Str;
            using lli       = Impl_Int_::lli;
            using ld        = Impl_Int_::ld;
            using diglist   = Impl_Int_::diglist;
            using digit     = Impl_Int_::digit;
            using Sign      = Impl_Int_::Sign;
    //Arithmetic operators
            inline Int& operator+=(const Int& rhs)
                {return m_base += rhs.m_base, *this;}

            inline Int& operator-=(const Int& rhs)
                {return m_base -= rhs.m_base, *this;}

            inline Int& operator*=(const Int& rhs)
                {return m_base *= rhs.m_base, *this;}

            inline Int& operator/=(const Int& rhs)
                {return m_base /= rhs.m_base, *this;}

            inline Int& operator%=(const Int& rhs)
                {return m_base %= rhs.m_base, *this;}

            inline Int& operator--()
                {return --m_base, *this;}
                
            inline Int operator--(int)
                {return Int(m_base--);}
                
            inline Int& operator++()
                {return ++m_base, *this;}
                
            inline Int operator++(int)
                {return Int(m_base++);}
    //Bitwise operators
            inline Int& operator&=(const Int& rhs)
                {return m_base &= rhs.m_base, *this;}
            
            inline Int& operator|=(const Int& rhs)
                {return m_base |= rhs.m_base, *this;}
            
            inline Int& operator^=(const Int& rhs)
                {return m_base ^= rhs.m_base, *this;}

            inline Int& operator<<=(const Int& rhs)
                {return m_base <<= rhs.m_base, *this;}

            inline Int& operator>>=(const Int& rhs)
                {return m_base >>= rhs.m_base, *this;}

    //Read-only functions
            inline Sign sign()const
                {return m_base.sign();}

            inline Str str()const
                {return m_base.str();}

            //Set the precision through parameter
            inline Str sci_note(size_t precision=k_display_prec)const
                {return m_base.sci_note(precision);}

            inline Str sci_note_w_spaces(size_t precision=k_display_prec)const
                {return m_base.sci_note_w_spaces(precision);}

            inline Int magnitude()const
                {return Int(m_base.magnitude());}

            inline size_t count_digits()const
                {return m_base.count_digits();}

            inline short compare(const Int& s)const
                {return m_base.compare(s.m_base);}

            inline Int operator-()const
                {return Int(m_base*-1);}
                
                //Does not work for ~0
            inline Int operator~()const
                {return Int(~m_base);}
    
    //Other modifiers
                //Multiplies integer by a power of ten
            inline void shift(lli tens_exp)
                {m_base.shift(tens_exp);}
    
    //Constructors and destructor
            Int(lli inInt = 0)
                : m_base(inInt)
            {}
            
            Int(const diglist& inImage)
                : m_base(inImage)
            {}
            
            explicit Int(const Impl_Int_& inInt)
                : m_base(inInt)
            {}
            
            explicit Int(Impl_Int_&& inInt)
                : m_base(std::move(inInt))
            {}

            Int(const Int&)             =default;
            Int(Int&&)                  =default;
            Int& operator=(const Int&)  =default;
            Int& operator=(Int&&)       =default;
            ~Int()                      =default;
        private:
            Impl_Int_ m_base;
    };
//Comparison operators
    inline bool operator==(const Int& f,const Int& s)
        {return (f.compare(s) == 0);}

    inline bool operator!=(const Int& f,const Int& s)
        {return !(f == s);}

    inline bool operator!(const Int& f)
        {return f == 0;}

    inline bool operator>(const Int& f,const Int& s)
        {return (f.compare(s) == 1);}

    inline bool operator<(const Int& f,const Int& s)
        {return (f.compare(s) == -1);}

    inline bool operator>=(const Int& f,const Int& s)
        {return !(f < s);}

    inline bool operator<=(const Int& f,const Int& s)
        {return !(f > s);}

//Other related functions
	inline Int operator+(const Int& f, const Int& s)
        {return (Int(f) += s);}

    inline Int operator-(const Int& f, const Int& s)
        {return (Int(f) -= s);}

    inline Int operator*(const Int& f, const Int& s)
        {return Int(f) *= s;}

    inline Int operator/(const Int& f, const Int& s)
        {return (Int(f) /= s);}

    inline Int operator%(const Int& f, const Int& s)
        {return (Int(f) %= s);}

    inline Int operator&(const Int& f, const Int& s)
        {return (Int(f) &= s);}

    inline Int operator|(const Int& f, const Int& s)
        {return (Int(f) |= s);}

    inline Int operator^(const Int& f, const Int& s)
        {return (Int(f) ^= s);}

    inline Int operator<<(const Int& f, const Int& s)
        {return (Int(f) <<= s);}

    inline Int operator>>(const Int& f, const Int& s)
        {return (Int(f) >>= s);}

    inline short Compare(const Int& f, const Int& s)
        {return f.compare(s);}
}
Precision::Int operator"" _Precision_Int(char const *const, size_t);
Precision::Int operator"" _Precision_Int_E(char const *const, size_t);
Precision::Int operator"" _Precision_Int(unsigned long long);

#endif