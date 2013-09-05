#ifndef __PRECISION_FRACT_H
#define __PRECISION_FRACT_H

#include "Impl/Precision_Fract_Impl.h"
#include "Impl/Shared_Constants.h"

namespace Precision{
    class Fract{
        public:
            using Integer   = Impl_Fract_::Integer;
            using Float     = Impl_Fract_::Float;
            using Str       = Impl_Fract_::Str;
            using Sign      = Impl_Fract_::Sign;
            using ld        = Impl_Fract_::ld;
            using lli       = Impl_Fract_::lli;
            using ulli      = Impl_Fract_::ulli;
    //Arithmetic operators
            inline Fract& operator+=(const Fract& rhs)
                {return m_base += rhs.m_base, *this;}

            inline Fract& operator-=(const Fract& rhs)
                {return m_base -= rhs.m_base, *this;}

            inline Fract& operator*=(const Fract& rhs)
                {return m_base *= rhs.m_base, *this;}

            inline Fract& operator/=(const Fract& rhs)
                {return m_base /= rhs.m_base, *this;}

            inline Fract& operator%=(const Fract& rhs)
                {return m_base %= rhs.m_base, *this;}

            inline Fract& operator--()
                {return --m_base, *this;}

            inline Fract operator--(int)
                {return m_base--;}

            inline Fract& operator++()
                {return ++m_base, *this;}

            inline Fract operator++(int)
                {return m_base++;}

            inline Fract operator-()const
                {return -m_base;}

    //Overloaded operators with new meanings
                //Invert the fraction
            inline Fract operator~()const
                {return ~m_base;}
                
                //Raise the fraction to the power of
            inline Fract operator^=(const Integer& rhs)
                {return m_base ^= rhs, *this;}
                
            inline Fract operator^=(const Fract& rhs)
                {return m_base ^= rhs.m_base, *this;}
                
    //Read-only functions
            inline Sign sign()const
                {return m_base.sign();}
                
            inline Integer numerator()const
                {return m_base.numerator();}
                
            inline Integer denominator()const
                {return m_base.denominator();}
                
            inline Str str()const
                {return m_base.str();}
                
            inline Str mixed()const
                {return m_base.mixed();}
                
        //Set the precision through parameter
            inline Fract magnitude()const
                {return m_base.magnitude();}
                
            inline size_t precision()const
                {return m_base.precision();}
                
            inline short compare(const Fract& s)const
                {return m_base.compare(s.m_base);}
                
        //Following two pairs are merely different names for the same thing
            inline Integer whole()const
                {return static_cast<Integer>(m_base);}
                
            inline Float decimal()const
                {return static_cast<Float>(m_base);}
                
            inline Integer integer()const
                {return static_cast<Integer>(m_base);}
                
            inline Float floating_point()const
                {return static_cast<Float>(m_base);}
                
            inline Integer gcd(const Fract& s)const
                {return m_base.gcd(s.m_base);}

            inline Fract remainder(const Fract& s)const
                {return m_base.remainder(s.m_base);}
                
    //Other modifiers
            inline void precision(size_t inPrec)
                {m_base.precision(inPrec);}
                
    //Overload cast operators
            inline explicit operator Integer() const
                {return static_cast<Integer>(m_base);}
                
            inline explicit operator Float() const
                {return static_cast<Float>(m_base);}
                
    //Constructors and destructor
            Fract(ld inFP = 0.0, size_t inPrec = k_default_prec)
                : m_base(inFP, inPrec)
            {}
            
            Fract(
                const Str& inImage,
                Sign inSign = 1,
                size_t inPrec = k_default_prec
            )
                : m_base(inImage, inSign, inPrec)
            {}
            
            Fract(const Integer& inWhole, size_t inPrec = k_default_prec)
                : m_base(inWhole, inPrec)
            {}
            
            Fract(Integer&& inWhole, size_t inPrec = k_default_prec)
                : m_base(std::move(inWhole), inPrec)
            {}
            
            Fract(const Float& inFP)
                : m_base(inFP)
            {}
            
            Fract (Float&& inFP)
                : m_base(std::move(inFP))
            {}
            
            Fract(
                const Integer& inNumer,
                const Integer& inDenom,
                size_t inPrec = k_default_prec
            )
                : m_base(inNumer, inDenom, inPrec)
            {}
            
            Fract(
                Integer&& inNumer,
                Integer&& inDenom,
                size_t inPrec = k_default_prec
            )
                : m_base(std::move(inNumer), std::move(inDenom), inPrec)
            {}
            
            Fract(const Impl_Fract_& inFrac)
                : m_base(inFrac)
            {}
            
            Fract(Impl_Fract_&& inFrac)
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

#endif