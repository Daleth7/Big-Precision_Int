#ifndef __PRECISION_FRACT_H
#define __PRECISION_FRACT_H

#include "Impl/Precision_Fract_Impl.h"
#include "Impl/Shared_Constants.h"

namespace Precision{
    class Fract{
        public:
            using Integer   = Impl_Fract_::Integer;
            using Float     = Impl_Fract_::Float;
            using str_type  = Impl_Fract_::str_type;
            using sign_type = Impl_Fract_::sign_type;
            using ld        = Impl_Fract_::ld;
            using lli       = Impl_Fract_::lli;
            using ulli      = Impl_Fract_::ulli;
            using size_type = Impl_Fract_::size_type;
    //Arithmetic operators
            Fract& operator+=(const Fract& rhs)
                {return m_base += rhs.m_base, *this;}

            Fract& operator-=(const Fract& rhs)
                {return m_base -= rhs.m_base, *this;}

            Fract& operator*=(const Fract& rhs)
                {return m_base *= rhs.m_base, *this;}

            Fract& operator/=(const Fract& rhs)
                {return m_base /= rhs.m_base, *this;}

            Fract& operator%=(const Fract& rhs)
                {return m_base %= rhs.m_base, *this;}

            Fract& operator--()
                {return --m_base, *this;}

            Fract operator--(int)
                {return Fract(m_base--);}

            Fract& operator++()
                {return ++m_base, *this;}

            Fract operator++(int)
                {return Fract(m_base++);}

            Fract operator-()const
                {return Fract(-m_base);}

            bool is_integer()const
                {return m_base.is_integer();}

    //Overloaded operators with new meanings
                //Invert the fraction
            Fract operator~()const
                {return Fract(~m_base);}
                
                //Raise the fraction to the power of
            Fract operator^=(const Integer& rhs)
                {return m_base ^= rhs, *this;}
/***************Function below is currently incomplete*******************/
            Fract operator^=(const Fract& rhs)
                {return m_base ^= rhs.m_base, *this;}
                
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
                
            Integer numerator()const
                {return m_base.numerator();}
                
            Integer denominator()const
                {return m_base.denominator();}
                
            str_type str()const
                {return m_base.str();}
                
            str_type mixed()const
                {return m_base.mixed();}
                
            Fract magnitude()const
                {return Fract(m_base.magnitude());}
                
            size_type precision()const
                {return m_base.precision();}
                
            short compare(const Fract& s)const
                {return m_base.compare(s.m_base);}
                
        //Following two pairs are merely different names for the same thing
            Integer whole()const
                {return static_cast<Integer>(m_base);}
                
            Float decimal()const
                {return static_cast<Float>(m_base);}
                
            Integer integer()const
                {return static_cast<Integer>(m_base);}
                
            Float floating_point()const
                {return static_cast<Float>(m_base);}
                
            Integer gcd(const Fract& s)const
                {return m_base.gcd(s.m_base);}

            Fract remainder(const Fract& s)const
                {return Fract(m_base.remainder(s.m_base));}

            Fract inverse()const
                {return Fract(m_base.inverse());}
                
    //Other modifiers
            void precision(size_type inPrec)
                {m_base.precision(inPrec);}

            Fract& invert()
                {return m_base.invert(), *this;}

            void sign(sign_type newsign)
                {m_base.sign(newsign);}

            void negate()
                {m_base.negate();}

            void swap(Fract& s)
                {m_base.swap(s.m_base);}

            void shift(lli z)
                {m_base.shift(z);}

            void shift_left(size_type e)
                {m_base.shift_left(e);}

            void shift_right(size_type e)
                {m_base.shift_right(e);}
                
    //Overload cast operators
            explicit operator Integer() const
                {return static_cast<Integer>(m_base);}
                
            explicit operator Float() const
                {return static_cast<Float>(m_base);}
                
    //Constructors and destructor
            Fract(ld inFP = 0.0, size_type inPrec = k_default_prec)
                : m_base(inFP, inPrec)
            {}
            
            Fract(
                const str_type& inImage,
                size_type inPrec = k_default_prec
            )
                : m_base(inImage, inPrec)
            {}
            
            explicit Fract(
                const Integer& inWhole,
                size_type inPrec = k_default_prec
            )
                : m_base(inWhole, inPrec)
            {}
            
            explicit Fract(
                Integer&& inWhole,
                size_type inPrec = k_default_prec
            )
                : m_base(std::move(inWhole), inPrec)
            {}
            
            explicit Fract(const Float& inFP)
                : m_base(inFP)
            {}
            
            explicit Fract (Float&& inFP)
                : m_base(std::move(inFP))
            {}
            
            explicit Fract(
                const Integer& inNumer,
                const Integer& inDenom,
                size_type inPrec = k_default_prec
            )
                : m_base(inNumer, inDenom, inPrec)
            {}
            
            explicit Fract(
                Integer&& inNumer,
                Integer&& inDenom,
                size_type inPrec = k_default_prec
            )
                : m_base(
                    std::move(inNumer),
                    std::move(inDenom),
                    inPrec
                )
            {}
            
            explicit Fract(const Impl_Fract_& inFrac)
                : m_base(inFrac)
            {}
            
            explicit Fract(Impl_Fract_&& inFrac)
                : m_base(std::move(inFrac))
            {}

            Fract(const Fract&)             =default;
            Fract(Fract&&)                  =default;
            Fract& operator=(const Fract&)  =default;
            Fract& operator=(Fract&&)       =default;
            ~Fract()                        =default;
        private:
            Impl_Fract_ m_base;
    };

    inline Fract operator+(Fract lhs, const Fract& rhs)
        {return lhs += rhs;}
        
    inline Fract operator-(Fract lhs, const Fract& rhs)
        {return lhs -= rhs;}
        
    inline Fract operator*(Fract lhs, const Fract& rhs)
        {return lhs *= rhs;}
        
    inline Fract operator/(Fract lhs, const Fract& rhs)
        {return lhs /= rhs;}
        
    inline Fract operator%(Fract lhs, const Fract& rhs)
        {return lhs %= rhs;}

    inline Fract operator^(Fract lhs, const Fract::Integer& rhs)
        {return lhs ^= rhs;}

    inline Fract operator^(Fract lhs, const Fract& rhs)
        {return lhs ^= rhs;}

    inline bool operator==(const Fract& lhs, const Fract& rhs)
        {return lhs.compare(rhs) == 0;}
        
    inline bool operator!=(const Fract& lhs, const Fract& rhs)
        {return lhs.compare(rhs) != 0;}
        
    inline bool operator>=(const Fract& lhs, const Fract& rhs)
        {return lhs.compare(rhs) >= 0;}
        
    inline bool operator<=(const Fract& lhs, const Fract& rhs)
        {return lhs.compare(rhs) <= 0;}
        
    inline bool operator>(const Fract& lhs, const Fract& rhs)
        {return lhs.compare(rhs) > 0;}
        
    inline bool operator<(const Fract& lhs, const Fract& rhs)
        {return lhs.compare(rhs) < 0;}
        
    inline bool operator!(const Fract& testee)
        {return testee == 0;}
}

inline void swap(Precision::Fract& a, Precision::Fract& b)
    {a.swap(b);}

#endif