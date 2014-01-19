#ifndef __PRECISION_INT_H
#define __PRECISION_INT_H

#include "Impl/Precision_Int_Impl.h"

#include <utility>

namespace Precision{
    class Int{
        public:
    //Type aliases
            using str_type       = Impl_Int_::str_type;
            using lli       = Impl_Int_::lli;
            using ld        = Impl_Int_::ld;
            using diglist_type   = Impl_Int_::diglist_type;
            using digit_type     = Impl_Int_::digit_type;
            using sign_type = Impl_Int_::sign_type;
            using size_type = Impl_Int_::size_type;
    //Arithmetic operators
            Int& operator+=(const Int& rhs)
                {return m_base += rhs.m_base, *this;}

            Int& operator-=(const Int& rhs)
                {return m_base -= rhs.m_base, *this;}

            Int& operator*=(const Int& rhs)
                {return m_base *= rhs.m_base, *this;}

            Int& operator/=(const Int& rhs)
                {return m_base /= rhs.m_base, *this;}

            Int& operator%=(const Int& rhs)
                {return m_base %= rhs.m_base, *this;}

            Int& operator--()
                {return --m_base, *this;}

            Int operator--(int)
                {return Int(m_base--);}

            Int& operator++()
                {return ++m_base, *this;}

            Int operator++(int)
                {return Int(m_base++);}
    //Bitwise operators
            Int& operator&=(const Int& rhs)
                {return m_base &= rhs.m_base, *this;}

            Int& operator|=(const Int& rhs)
                {return m_base |= rhs.m_base, *this;}

            Int& operator^=(const Int& rhs)
                {return m_base ^= rhs.m_base, *this;}

            Int& operator<<=(const Int& rhs)
                {return m_base <<= rhs.m_base, *this;}

            Int& operator>>=(const Int& rhs)
                {return m_base >>= rhs.m_base, *this;}

    //Read-only functions
            bool is_integer()const
                {return true;}

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

            str_type str()const
                {return m_base.str();}

            //Set the precision through parameter
            str_type sci_note(size_type precision=k_display_prec)const
                {return m_base.sci_note(precision);}

            str_type sci_note_w_spaces(size_type precision=k_display_prec)const
                {return m_base.sci_note_w_spaces(precision);}

            Int magnitude()const
                {return Int(m_base.magnitude());}

            size_type count_digits()const
                {return m_base.count_digits();}

            short compare(const Int& s)const
                {return m_base.compare(s.m_base);}

            Int operator-()const
                {return Int(-m_base);}

                //Since there is no limit on the number of bytes,
                //  ~Int(0) will return 0.
            Int operator~()const
                {return Int(~m_base);}

    //Other modifiers
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

            void swap(Int& s)
                {m_base.swap(s.m_base);}

    //Constructors and destructor
            Int(lli inInt = 0)
                : m_base(inInt)
            {}

            Int(const str_type& inImage)
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

inline void swap(Precision::Int& a, Precision::Int& b)
    {a.swap(b);}

Precision::Int operator"" _Precision_Int(char const *const, size_t);
Precision::Int operator"" _Precision_Int_E(char const *const, size_t);
Precision::Int operator"" _Precision_Int(unsigned long long);

#endif
