#include "Precision_Fract_Impl.h"

#include "Precision_Int.h"
#include "Precision_Float.h"

#include "Precision_Math.h"

#include <sstream>

//Arithmetic operators
Impl_Fract_& Impl_Fract_::operator+=(const Impl_Fract_& rhs){
    if(*this == 0)          return *this = rhs;
    else if(rhs == 0)       return *this;
    else if(rhs == *this){
        m_numer *= 2;
        this->Simplify();
        return *this;
    //Guaranteed one of them to be negative if true
    }else if(rhs.magnitude() == this->magnitude())
        return *this = 0;
    else if(m_denom == rhs.m_denom){
        m_numer += rhs.m_numer;
        this->Simplify();
        return *this;
    }

    m_numer = m_numer * rhs.m_denom + rhs.m_numer * m_denom;
    m_denom *= rhs.m_denom;
    this->Simplify();
    return *this;
}
Impl_Fract_& Impl_Fract_::operator-=(const Impl_Fract_& rhs){
    if(*this == rhs) return *this = 0;
    return *this += -rhs;
}
Impl_Fract_& Impl_Fract_::operator*=(const Impl_Fract_& rhs){
    if(*this == 0 || rhs == 0)  return *this = 0;
    else if(*this == 1)         return *this = rhs;
    else if(rhs == 1)           return *this;

    //Make use of the simplify function via constructor
    Impl_Fract_
        operand1(m_numer, rhs.m_denom, m_precision),
        operand2(rhs.m_numer, m_denom, m_precision)
    ;
    m_numer = operand1.m_numer * operand2.m_numer;
    m_denom = operand1.m_denom * operand2.m_denom;
//No need to call simplify because that work was done in construction
    return *this;
}
Impl_Fract_& Impl_Fract_::operator/=(const Impl_Fract_& rhs){
    if(*this == 0 || rhs == 1 || rhs == 0)  return *this;
    else if(*this == 1)                     return *this = rhs;

    return *this *= ~rhs;
}
Impl_Fract_& Impl_Fract_::operator%=(const Impl_Fract_& rhs){
    *this /= rhs;
    *this -= this->whole();
    return *this;
}
Impl_Fract_& Impl_Fract_::operator--()
    {return *this -= 1;}
Impl_Fract_ Impl_Fract_::operator--(int)
    {return (*this -= 1)+1;}
Impl_Fract_& Impl_Fract_::operator++()
    {return *this += 1;}
Impl_Fract_ Impl_Fract_::operator++(int)
    {return (*this += 1)-1;}

Impl_Fract_ Impl_Fract_::operator-()const
    {return Impl_Fract_(m_numer*-1, m_denom, m_precision);}

//Overloaded operators with new meanings
    //Invert the fraction
Impl_Fract_ Impl_Fract_::operator~()const
    {return Impl_Fract_(m_denom, m_numer, m_precision);}
    //Raise the fraction to the power of
Impl_Fract_ Impl_Fract_::operator^=(const Integer& rhs){
    m_numer = Precision::Pow(m_numer, rhs);
    m_denom = Precision::Pow(m_denom, rhs);
    return *this;
}
Impl_Fract_ Impl_Fract_::operator^=(const Impl_Fract_& rhs)
    {return *this = (Float(m_numer)/m_denom) ^ rhs;}



//Read-only functions
Impl_Fract_::Sign Impl_Fract_::sign()const
    {return m_numer.sign();}
Impl_Fract_::Integer Impl_Fract_::numerator()const
    {return m_numer;}
Impl_Fract_::Integer Impl_Fract_::denominator()const
    {return m_denom;}
Impl_Fract_::Str Impl_Fract_::str()const{
    Str temp(m_denom.str());
    temp.erase(0, 1); //Get rid of sign
    return m_numer.str() + "/" + temp;
}
Impl_Fract_::Str Impl_Fract_::mixed()const{
    Str temp((*this - this->whole()).str());
    temp.erase(0, 1);//Get rid of sign
    return this->whole().str() + " " + temp;
}
    //Set the precision through parameter
Impl_Fract_ Impl_Fract_::magnitude()const
    {return Impl_Fract_(m_numer.magnitude(), m_denom, m_precision);}
size_t Impl_Fract_::precision()const
    {return m_precision;}
short Impl_Fract_::compare(const Impl_Fract_& s)const{
    if(m_numer.sign() < s.m_numer.sign()) return -1;
    if(m_numer.sign() > s.m_numer.sign()) return 1;

    return (Float(m_numer)/m_denom).compare(Float(s.m_numer)/s.m_denom);
}
    //Following two pairs are merely different names for the same thing
Impl_Fract_::Integer Impl_Fract_::whole()const
    {return (Float(m_numer)/m_denom).integer();}
Impl_Fract_::Float Impl_Fract_::decimal()const
    {return Float(m_numer)/m_denom;}
Impl_Fract_::Integer Impl_Fract_::integer()const
    {return this->whole();}
Impl_Fract_::Float Impl_Fract_::floating_point()const
    {return this->decimal();}
Impl_Fract_::Integer Impl_Fract_::gcd(const Impl_Fract_& s)const
    {return Precision::GCF(m_denom, s.m_denom);}

Impl_Fract_ Impl_Fract_::remainder(const Impl_Fract_& rhs)const
    {return Impl_Fract_(*this) %= rhs;}



//Other modifiers
void Impl_Fract_::precision(size_t inPrec)
    {m_precision = (inPrec ? inPrec : 1);}



//Overload cast operators
Impl_Fract_::operator Integer() const
    {return this->whole();}
Impl_Fract_::operator Float() const
    {return Float(m_numer) / m_denom;}



//Constructors and destructor
Impl_Fract_::Impl_Fract_(ld inFP, size_t inPrec)
    : m_numer(0)
    , m_denom(1)
    , m_precision(inPrec)
{
    if(inFP < -1e-14 || inFP > 1e-14){
        std::stringstream catalyst;
            catalyst << inFP;
        std::string convert(catalyst.str());
        size_t tens_exp(convert.substr(convert.find('.')+1).size());
        convert.erase(convert.find('.'), 1);
        m_numer = Integer(convert);
        m_denom = Precision::Pow(10, tens_exp ? tens_exp : 1);
        this->Simplify();
    }
}
Impl_Fract_::Impl_Fract_(
    Str inImage,
    size_t inPrec
)
    : m_numer(0)
    , m_denom(0)
    , m_precision(inPrec)
{
    size_t tens_exp(inImage.substr(inImage.find('.')+1).size());
    inImage.erase(inImage.find('.'), 1);
    m_numer = Integer(inImage);
    m_denom = Precision::Pow(10, tens_exp ? tens_exp : 1);
    this->Simplify();
}
Impl_Fract_::Impl_Fract_(const Integer& inWhole, size_t inPrec)
    : m_numer(inWhole)
    , m_denom(1)
    , m_precision(inPrec)
{}
Impl_Fract_::Impl_Fract_(const Float& inFP)
    : m_numer(0)
    , m_denom(0)
    , m_precision(inFP.precision())
{
    Float::Str catalyst(inFP.str(0, true));
    size_t tens_exp(catalyst.substr(catalyst.find('.')+1).size());
    catalyst.erase(catalyst.find('.'), 1);
    m_numer = Integer(catalyst);
    m_denom = Precision::Pow(10, tens_exp ? tens_exp : 1);
    this->Simplify();
}
Impl_Fract_::Impl_Fract_(
    const Integer& inNumerator,
    const Integer& inDenominator,
    size_t inPrecision
)
    : m_numer(inNumerator)
    , m_denom(inDenominator)
    , m_precision(inPrecision)
{this->Simplify();}



#include <list>
#include <iterator>
#include <limits>

//Helpers
void Impl_Fract_::Simplify(){
    std::list<Integer> primes(0);
    const Integer& Imax(m_numer < m_denom ? m_denom : m_numer);
    std::string catalyst(Imax.str());
    if(catalyst[0] == '+') catalyst.erase(0, 1);
    std::stringstream ss(catalyst.substr(
        (catalyst[0] == '+' ? 1 : 0)
    ));
    ulli topass(0);
    catalyst >> topass;
    auto max(std::numeric_limits<ulli>::max());
    Precision::Erato_Sieve(
        (topass > max ? max : topass),
        std::back_inserter(primes)
    );
    for(const auto& i : primes)
        while((m_numer % i == 0) && (m_denom % i == 0))
            m_numer /= i, m_denom /= i;
}



Impl_Fract_ operator+(Impl_Fract_ lhs, const Impl_Fract_& rhs)
    {return Impl_Fract_(lhs) += rhs;}
Impl_Fract_ operator-(Impl_Fract_ lhs, const Impl_Fract_& rhs)
    {return Impl_Fract_(lhs) -= rhs;}
Impl_Fract_ operator*(Impl_Fract_ lhs, const Impl_Fract_& rhs)
    {return Impl_Fract_(lhs) *= rhs;}
Impl_Fract_ operator/(Impl_Fract_ lhs, const Impl_Fract_& rhs)
    {return Impl_Fract_(lhs) /= rhs;}
Impl_Fract_ operator%(Impl_Fract_ lhs, const Impl_Fract_& rhs)
    {return Impl_Fract_(lhs) %= rhs;}

Impl_Fract_ operator^(Impl_Fract_ lhs, const Impl_Fract_& rhs)
    {return Impl_Fract_(lhs) ^= rhs;}

bool operator==(const Impl_Fract_& lhs, const Impl_Fract_& rhs)
    {return lhs.compare(rhs) == 0;}
bool operator!=(const Impl_Fract_& lhs, const Impl_Fract_& rhs)
    {return lhs.compare(rhs) != 0;}
bool operator>=(const Impl_Fract_& lhs, const Impl_Fract_& rhs)
    {return lhs.compare(rhs) >= 0;}
bool operator<=(const Impl_Fract_& lhs, const Impl_Fract_& rhs)
    {return lhs.compare(rhs) <= 0;}
bool operator>(const Impl_Fract_& lhs, const Impl_Fract_& rhs)
    {return lhs.compare(rhs) > 0;}
bool operator<(const Impl_Fract_& lhs, const Impl_Fract_& rhs)
    {return lhs.compare(rhs) < 0;}
bool operator!(const Impl_Fract_& lhs)
    {return lhs == 0;}