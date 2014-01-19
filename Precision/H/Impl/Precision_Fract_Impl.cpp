#include "Precision_Fract_Impl.h"

#include "Precision_Math_Shared_Functions.h"

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
    else if(*this == 1)                     return *this = ~rhs;
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

Impl_Fract_ Impl_Fract_::operator^=(const Impl_Fract_& rhs){
    return
        (rhs.m_denom == 1)
        ? this->exponentiate(rhs.m_numer)
        : this->exponentiate(rhs, m_precision)
    ;
}



//Read-only functions
Impl_Fract_::sign_type Impl_Fract_::sign()const
    {return m_numer.sign();}
bool Impl_Fract_::even()const
    {return m_numer.even();}
bool Impl_Fract_::odd()const
    {return m_numer.odd();}
Impl_Fract_::Integer Impl_Fract_::numerator()const
    {return m_numer;}
Impl_Fract_::Integer Impl_Fract_::denominator()const
    {return m_denom;}
Impl_Fract_::str_type Impl_Fract_::str()const{
    str_type temp(m_denom.str().substr(1));
    return m_numer.str() + "/" + temp;
}
Impl_Fract_::str_type Impl_Fract_::mixed()const{
    if(this->whole() == 0) return this->str();
    return
        this
        -> whole()
        . str()
        + " "
        + (m_numer%m_denom)
        . str()
        . substr(1)
        + "/"
        + m_denom
        . str()
        . substr(1)
    ;
}
    //Set the precision through parameter
Impl_Fract_ Impl_Fract_::magnitude()const{
    Impl_Fract_ toreturn(*this);
    toreturn.sign(1);
    return toreturn;
}
Impl_Fract_::size_type Impl_Fract_::precision()const
    {return m_precision;}
short Impl_Fract_::compare(const Impl_Fract_& s)const{
    if(this == &s)                              return 0;
    else if(m_numer.sign() < s.m_numer.sign())  return -1;
    else if(m_numer.sign() > s.m_numer.sign())  return 1;
    Integer gcfactor = Precision::gcf(m_denom, s.m_denom);
    return (m_numer*gcfactor).compare(s.m_numer*gcfactor);
}
    //Following two pairs are merely different names for the same thing
Impl_Fract_::Integer Impl_Fract_::whole()const
    {return m_numer/m_denom;}
Impl_Fract_::Float Impl_Fract_::decimal()const
    {return Float(m_numer)/m_denom;}
Impl_Fract_::Integer Impl_Fract_::integer()const
    {return this->whole();}
Impl_Fract_::Float Impl_Fract_::floating_point()const
    {return this->decimal();}
Impl_Fract_::Integer Impl_Fract_::gcd(const Impl_Fract_& s)const
    {return this->GCD_Helper(m_denom, s.m_denom);}

Impl_Fract_ Impl_Fract_::remainder(const Impl_Fract_& rhs)const
    {return Impl_Fract_(*this) %= rhs;}
Impl_Fract_ Impl_Fract_::inverse()const
    {return ~(*this);}
bool Impl_Fract_::is_integer()const
    {return m_denom == 1;}



//Other modifiers
void Impl_Fract_::precision(size_type inPrec)
    {m_precision = (inPrec ? inPrec : 1);}

Impl_Fract_& Impl_Fract_::invert(){
    std::swap(m_numer, m_denom);
    if(m_denom.sign() < 0)
        m_numer.negate(), m_denom.sign(1);
    return *this;
}

void Impl_Fract_::sign(sign_type newsign)
    {m_numer.sign(newsign);}

void Impl_Fract_::negate()
    {m_numer.negate();}

void Impl_Fract_::swap(Impl_Fract_& s){
    std::swap(m_numer, s.m_numer);
    std::swap(m_denom, s.m_denom);
    std::swap(m_precision, s.m_precision);
}

void Impl_Fract_::shift(lli z){
    if(z < 0)
        this->shift_right(-z);
    else
        this->shift_left(z);
}

void Impl_Fract_::shift_left(size_type e){
    m_numer.shift_left(e);
    this->Simplify();
}

void Impl_Fract_::shift_right(size_type e){
    m_denom.shift_left(e);
    this->Simplify();
}

Impl_Fract_& Impl_Fract_::exponentiate(const Integer& exp){
    m_numer = Precision::exponentiate(m_numer, exp);
    m_denom = Precision::exponentiate(m_denom, exp);
    return *this;
}

Impl_Fract_& Impl_Fract_::exponentiate(const Impl_Fract_& exp, size_type prec){
    if(m_numer.negative() && exp.m_denom.even())   return *this = 0;
    return *this = Precision::exponentiate(*this, exp, prec ? prec : m_precision);
}

//Overload cast operators
Impl_Fract_::operator Integer() const
    {return this->whole();}
Impl_Fract_::operator Float() const
    {return Float(m_numer) / m_denom;}

//Constructors and destructor
Impl_Fract_::Impl_Fract_(ld inFP, size_type inPrec)
    : m_numer(0)
    , m_denom(1)
    , m_precision(inPrec)
{
    if(inFP > 1e-15 || inFP < -1e-15){
        Precision::Float catalyst(inFP);
        this->Check_Pattern(
            catalyst
            . str()
            . substr(catalyst.str().find('.') + 1)
            , catalyst
        );

        if(m_denom == 1){
            m_denom.shift_left(catalyst.count_right_digits());
            catalyst.shift_left(catalyst.count_right_digits());
            m_numer = catalyst.integer();
        }

        this->Simplify();
    }
}
Impl_Fract_::Impl_Fract_(str_type inImage, size_type inPrec)
    : m_numer(0)
    , m_denom(1)
    , m_precision(inPrec)
{
    this->Check_Pattern(
        inImage.substr(inImage.find('.')+1)
        , Float(inImage)
    );
    if(m_denom == 1){
        size_type tens_exp(
            inImage.find('.') == str_type::npos
            ? 0
            : inImage.substr(inImage.find('.')+1).size()
        );
        inImage.erase(inImage.find('.'), 1);
        m_numer = Integer(inImage);
        m_denom.shift_left(tens_exp);
    }
    this->Simplify();
}
Impl_Fract_::Impl_Fract_(const Integer& inWhole, size_type inPrec)
    : m_numer(inWhole)
    , m_denom(1)
    , m_precision(inPrec)
{}
Impl_Fract_::Impl_Fract_(const Float& inFP)
    : m_numer(0)
    , m_denom(1)
    , m_precision(inFP.precision())
{
    const str_type topass(inFP.str(0, true));
    this->Check_Pattern(topass.substr(topass.find('.')+1), inFP);

    if(m_denom == 1){
        m_denom.shift_left(inFP.count_right_digits());
        Float catalyst(inFP);
        catalyst.shift_left(catalyst.count_right_digits());
        m_numer = catalyst.integer();
    }

    this->Simplify();
}
Impl_Fract_::Impl_Fract_(
    const Integer& inNumerator,
    const Integer& inDenominator,
    size_type inPrecision
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
    }

    const Integer GCD(this->GCD_Helper(m_denom, m_numer.magnitude()));

    m_numer /= GCD;
    m_denom /= GCD;
}

void Impl_Fract_::Check_Pattern(const str_type& image, const Float& catalyst){
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

    if(
        (mu > 1 && image.substr(0, mu+1).find_last_of('0') > 0) ||
        lambda == image.size()
    )   return;
    const str_type pattern(image.substr(0, mu+lambda));
    if(pattern.find(image.substr(image.size()-lambda)) == str_type::npos)
        return;
    Integer nonpat(pattern.substr(0, mu));
        nonpat.sign(catalyst.sign());
    m_numer = pattern.substr(mu);
        m_numer.sign(catalyst.sign());
    m_denom = str_type(lambda, '9');
    m_numer += m_denom*nonpat;
        m_denom.shift_left(mu);
    m_numer += m_denom*catalyst.integer();
}

Impl_Fract_::Integer Impl_Fract_::GCD_Helper(
    const Integer& a,
    const Integer& b
)const{
//Euclid's Algorithm:
//http://en.wikipedia.org/wiki/Greatest_common_divisor#Using_Euclid.27s_algorithm

    Integer toreturn(a), prev(b);
    while(prev != 0){
        toreturn %= prev;
        std::swap(toreturn, prev);
    }
    return toreturn;
}

Impl_Fract_::Integer Impl_Fract_::GCF_Helper(
    const Integer& a,
    const Integer& b
)const{return (a*b)/GCD_Helper(a, b);}

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

void swap(Impl_Fract_& a, Impl_Fract_& b)
    {a.swap(b);}