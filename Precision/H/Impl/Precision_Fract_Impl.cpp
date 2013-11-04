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
    return (*this -= this->whole());
}
Impl_Fract_& Impl_Fract_::operator--()
    {return *this -= 1;}
Impl_Fract_ Impl_Fract_::operator--(int)
    {return (*this -= 1)+1;}
Impl_Fract_& Impl_Fract_::operator++()
    {return *this += 1;}
Impl_Fract_ Impl_Fract_::operator++(int)
    {return (*this += 1)-1;}

Impl_Fract_ Impl_Fract_::operator-()const{
    Impl_Fract_ toreturn(*this);
    toreturn.m_numer.negate();
    return toreturn;
}

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
    {return *this = (Float(m_numer)/m_denom) ^ Float(rhs);}



//Read-only functions
Impl_Fract_::Sign Impl_Fract_::sign()const
    {return m_numer.sign();}
bool Impl_Fract_::even()const
    {return m_numer.even();}
bool Impl_Fract_::odd()const
    {return m_numer.odd();}
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
    if(this->whole() == 0) return this->str();
    return
        this
        -> whole()
        . str()
        + " "
        + (Impl_Fract_(m_numer)%Impl_Fract_(m_denom))
        . str()
        . substr(1)
    ;
}
    //Set the precision through parameter
Impl_Fract_ Impl_Fract_::magnitude()const
    {return Impl_Fract_(m_numer.magnitude(), m_denom, m_precision);}
Impl_Fract_::Size_Type Impl_Fract_::precision()const
    {return m_precision;}
short Impl_Fract_::compare(const Impl_Fract_& s)const{
    if(this == &s)                              return 0;
    if(m_numer.sign() < s.m_numer.sign())       return -1;
    else if(m_numer.sign() > s.m_numer.sign())  return 1;

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
    {return this->GCF_Helper(m_denom, s.m_denom);}

Impl_Fract_ Impl_Fract_::remainder(const Impl_Fract_& rhs)const
    {return Impl_Fract_(*this) %= rhs;}
Impl_Fract_ Impl_Fract_::inverse()const
    {return ~(*this);}



//Other modifiers
void Impl_Fract_::precision(Size_Type inPrec)
    {m_precision = (inPrec ? inPrec : 1);}
Impl_Fract_& Impl_Fract_::invert(){
    std::swap(m_numer, m_denom);
    if(m_denom.sign() < 0)
        m_numer.negate(), m_denom.sign(1);
    return *this;
}
void Impl_Fract_::sign(Sign newsign)
    {m_numer.sign(newsign);}
void Impl_Fract_::negate()
    {m_numer.negate();}


//Overload cast operators
Impl_Fract_::operator Integer() const
    {return this->whole();}
Impl_Fract_::operator Float() const
    {return Float(m_numer) / m_denom;}

//Constructors and destructor
Impl_Fract_::Impl_Fract_(ld inFP, Size_Type inPrec)
    : m_numer(0)
    , m_denom(1)
    , m_precision(inPrec)
{
    Precision::Float catalyst(inFP);
    this->Check_Pattern(
        catalyst
        . str()
        . substr(catalyst.str().find('.') + 1)
        , catalyst
    );

    if(m_denom == 1){
        m_denom.shift(catalyst.count_right_digits());
        catalyst.shift(catalyst.count_right_digits());
        m_numer = catalyst.integer();
    }

    this->Simplify();
}
Impl_Fract_::Impl_Fract_(
    Str inImage,
    Size_Type inPrec
)
    : m_numer(0)
    , m_denom(1)
    , m_precision(inPrec)
{
    this->Check_Pattern(
        inImage.substr(inImage.find('.')+1)
        , Float(inImage)
    );
    if(m_denom == 1){
        Size_Type tens_exp(
            inImage.find('.') == Str::npos
            ? 0
            : inImage.substr(inImage.find('.')+1).size()
        );
        inImage.erase(inImage.find('.'), 1);
        m_numer = Integer(inImage);
        m_denom.shift(tens_exp);
    }
    this->Simplify();
}
Impl_Fract_::Impl_Fract_(const Integer& inWhole, Size_Type inPrec)
    : m_numer(inWhole)
    , m_denom(1)
    , m_precision(inPrec)
{}
Impl_Fract_::Impl_Fract_(const Float& inFP)
    : m_numer(0)
    , m_denom(1)
    , m_precision(inFP.precision())
{
    const Str topass(inFP.str(0, true));
    this->Check_Pattern(topass.substr(topass.find('.')+1), inFP);

    if(m_denom == 1){
        m_denom.shift(inFP.count_right_digits());
        Float catalyst(inFP);
        catalyst.shift(catalyst.count_right_digits());
        m_numer = catalyst.integer();
    }

    this->Simplify();
}
Impl_Fract_::Impl_Fract_(
    const Integer& inNumerator,
    const Integer& inDenominator,
    Size_Type inPrecision
)
    : m_numer(inNumerator)
    , m_denom(inDenominator)
    , m_precision(inPrecision)
{this->Simplify();}

//Helpers
void Impl_Fract_::Simplify(){
    if(m_numer == 0){
        m_denom = 1;
        return;
    }else if(m_denom == 0){
        m_numer = 0;
        m_denom = 1;
        return;
    }else if(m_denom.sign() < 0){
        m_numer.negate();
        m_denom.sign(1);
        return;
    }

    const Integer GCF(this->GCF_Helper(m_denom, m_numer.magnitude()));

    m_numer /= GCF;
    m_denom /= GCF;
}

void Impl_Fract_::Check_Pattern(
    const Str& image,
    const Float& catalyst
){
/*
        Derivation of Brent's derivation of
    the tortoise and hare algorithm
*/
//First check if a pattern exists
    if(image.size() < 3)    //Arbitrary
        return;
    unsigned
        pow(1),
        lambda(1)    //Length of pattern
    ;
    const char
        *tortoise(image.c_str()),
        *hare(image.c_str()+1)
    ;
    while(tortoise[0] != hare[0]){
        if(pow == lambda){
            tortoise = hare;
            pow <<= 1;
            lambda = 0;
        }
        ++hare;
        if(hare[0] == '\0')
            return;
        ++lambda;
    }
    unsigned mu(0); //Position where pattern starts
    tortoise = image.c_str();
    hare = image.c_str() + lambda;
    while(tortoise[0] != hare[0]){
        ++tortoise;
        ++hare;
        ++mu;
    }

    if(mu > 1 && image.substr(0, mu+1).find_last_of('0') > 0)
        return;
//Now use mu and lambda to compare against known patterns
    const Str pattern(image.substr(0, mu+lambda+2));
    auto match_against = [&](
        Str&& tomatch, 
        unsigned D,
        unsigned N,
        bool special = false
    ){
        if(mu > 0 && image[image.rfind('0')+1] != tomatch[0])
            return;
        else if(pattern == tomatch){
            Integer offset(1);
            offset.shift(special ? mu-1 : mu);
            m_denom = D * offset;
            m_numer = catalyst.integer()*D + N;
        }
    };

    match_against("333", 3, 1);
    match_against("666", 3, 2);
    match_against("1666", 6, 1, true);
    match_against("8333", 6, 5, true);
    match_against("14285714", 7, 1);
    match_against("28571428", 7, 2);
    match_against("42857142", 7, 3);
    match_against("57142857", 7, 4);
    match_against("71428571", 7, 5);
    match_against("85714285", 7, 6);
    match_against("111", 9, 1);
    match_against("222", 9, 2);
    match_against("444", 9, 4);
    match_against("555", 9, 5);
    match_against("777", 9, 7);
    match_against("888", 9, 8);
    match_against("999", 9, 9);
    match_against("0909", 11, 1);
    match_against("1818", 11, 2);
    match_against("2727", 11, 3);
    match_against("3636", 11, 4);
    match_against("4545", 11, 5);
    match_against("5454", 11, 6);
    match_against("6363", 11, 7);
    match_against("7272", 11, 8);
    match_against("8181", 11, 9);
    match_against("9090", 11, 10);
    match_against("08333", 12, 1, true);
}

Impl_Fract_::Integer Impl_Fract_::GCF_Helper(
    Integer toreturn,
    Integer quotient
)const{
//Euclid's Algorithm:
//  http://en.wikipedia.org/wiki/
//  Greatest_common_divisor
//  #Using_Euclid.27s_algorithm
    while(true){
        if(quotient % toreturn == 0) break;
        Integer hold(toreturn);
        toreturn = quotient % toreturn;
        quotient = hold;
    }
    return toreturn;
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
