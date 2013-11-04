#include "Precision_Float_Impl.h"

#include "Precision_Int.h"
#include "Precision_UInt.h"
#include "Precision_Math.h"

#include <sstream>

//Arithmetic operators
Impl_Float_& Impl_Float_::operator+=(const Impl_Float_& rhs){
    m_whole
        = this->Generate_Operand(rhs.m_precision)
        + rhs.Generate_Operand(this->m_precision)
    ;
    this->Update_Precision(rhs.m_precision);
    return *this;
}
Impl_Float_& Impl_Float_::operator-=(const Impl_Float_& rhs){
    m_whole
        = this->Generate_Operand(rhs.m_precision)
        - rhs.Generate_Operand(this->m_precision)
    ;
    this->Update_Precision(rhs.m_precision);
    return *this;
}
Impl_Float_& Impl_Float_::operator*=(const Impl_Float_& rhs){
    m_whole *= rhs.m_whole;
    m_whole.shift(-static_cast<lli>(rhs.m_precision));
    this->Update_Precision(rhs.m_precision);
    return *this;
}
Impl_Float_& Impl_Float_::operator/=(const Impl_Float_& rhs){
    Integer exp(1);
    exp.shift(rhs.count_right_digits());
    Impl_Float_ operand(rhs * exp);
    (m_whole *= exp) /= static_cast<Integer>(operand);

    this->Update_Precision(rhs.m_precision);
    return *this;
}
Impl_Float_& Impl_Float_::operator%=(const Impl_Float_& rhs){
    if(*this == rhs || rhs == 0) return *this = 0;

    *this /= rhs;
    Impl_Float_ catalyst(*this);
    catalyst.shift(-static_cast<lli>(m_precision));
    return *this -= catalyst;
}
Impl_Float_& Impl_Float_::operator--()
    {return (*this -= 1);}
Impl_Float_ Impl_Float_::operator--(int)
    {return (*this -= 1) + 1;}
Impl_Float_& Impl_Float_::operator++()
    {return (*this += 1);}
Impl_Float_ Impl_Float_::operator++(int)
    {return (*this += 1) - 1;}

Impl_Float_ Impl_Float_::operator-()const{
    Impl_Float_ toreturn(*this);
    toreturn.m_whole.negate();
    return toreturn;
}



//Other operators with different meaning
    //Return the inverse
Impl_Float_ Impl_Float_::operator~()const
    {return (1 / *this);}
    //Raise to the power of
Impl_Float_& Impl_Float_::operator^=(const Impl_Float_& s)
    {return this->exponentiate(s);}



//Read-only functions
Impl_Float_::Sign Impl_Float_::sign()const
    {return m_whole.sign();}

bool Impl_Float_::even()const
    {return m_whole.even();}

bool Impl_Float_::odd()const
    {return m_whole.odd();}

const Impl_Float_::Size_Type minLen(4);

Impl_Float_::Str Impl_Float_::str(
    Size_Type inPrec,
    bool inShowFull
)const{
    if(inPrec > m_precision)
        inPrec = m_precision;
    Str toreturn(m_whole.str());

    if(toreturn == "+0")
        return toreturn += "." + Str(inPrec ? inPrec : 1, '0');
        //If the number is something like 0.009
    if(m_precision > m_whole.count_digits())
        toreturn.insert(1, m_precision - m_whole.count_digits(), '0');
    toreturn.insert(toreturn.size() - m_precision, 1, '.');

    if(m_show_full || inShowFull) return toreturn;
    else if(inPrec == 0){
        while(toreturn.back() == '0' && toreturn.back() != '.')
            toreturn.pop_back();

        if(toreturn.back() == '.' && m_precision > 0)
            toreturn += "0";
        else if(toreturn.back() == '.')
            toreturn.pop_back();

        return toreturn;
    }

    Size_Type min = m_precision - inPrec - 1;
    while(min-- > 0) toreturn.pop_back();
    
    if(toreturn.back() == '.' && m_precision > 0)
        toreturn += "0";
    else toreturn.pop_back();
    
    return toreturn;
}

//Set the precision through parameter
Impl_Float_::Str Impl_Float_::sci_note(
    Size_Type inPrec,
    bool inShowFull
)const{
        //First get full image
    Str toreturn(this->str(m_precision, true));

    toreturn.erase(toreturn.find('.'), 1);
    toreturn.insert(2, 1, '.');
    if(toreturn.size() > minLen && !inShowFull)
        toreturn.erase(minLen - 1 + inPrec);
    Size_Type exp(m_whole.count_digits() - m_precision - 1);
    std::stringstream ss;
        ss << exp;
    toreturn += "E" + ss.str();

    return toreturn;
}
Impl_Float_::Str Impl_Float_::sci_note_w_spaces(
    Size_Type inPrec,
    bool inShowFull
)const{
    Str toreturn(this->sci_note(inPrec, inShowFull));
    toreturn.insert(1, 1, ' ');
    toreturn.insert(toreturn.find('E'), 1, ' ');
    toreturn.insert(toreturn.find('E')+1, 1, ' ');
    return toreturn;
}
Impl_Float_ Impl_Float_::magnitude()const{
    Impl_Float_ toreturn(*this);
    toreturn.m_whole = toreturn.m_whole.magnitude();
    return toreturn;
}
Impl_Float_::Size_Type Impl_Float_::count_digits()const
    {return this->count_left_digits() + this->count_right_digits();}
Impl_Float_::Size_Type Impl_Float_::count_left_digits()const
    {return m_whole.count_digits() - m_precision;}
Impl_Float_::Size_Type Impl_Float_::count_right_digits()const{
    if(m_whole == 0) return 1;
    std::string image(m_whole.str().substr(
            //Add 1 to account for sign character
        m_whole.count_digits() + 1 - m_precision
    ));
    while(image.back() == '0') image.pop_back();
    return image.size();
}
Impl_Float_::Size_Type Impl_Float_::precision()const
    {return m_precision;}
short Impl_Float_::compare(const Impl_Float_& s)const{
    if(m_whole.sign() < s.m_whole.sign())       return -1;
    else if(m_whole.sign() > s.m_whole.sign())  return 1;
    Integer epsilon(1);
    epsilon.shift(
        (
            m_precision > s.m_precision
            ? s.m_precision - m_precision
            : m_precision - s.m_precision
        )
        + 1
    );
    Integer
        testee1(Generate_Operand(s.m_precision)),
        testee2(s.Generate_Operand(this->m_precision))
    ;

    if(testee1 < testee2+epsilon && testee1 > testee2-epsilon)
                                                return 0;
    else return testee1.compare(testee2);
}
Impl_Float_::Integer Impl_Float_::integer()const{
    Integer toreturn(m_whole);
    toreturn.shift(-static_cast<lli>(m_precision));
    return toreturn;
}
bool Impl_Float_::show_full()const
    {return m_show_full;}

Impl_Float_ Impl_Float_::remainder(const Impl_Float_& s)const
    {return *this % s;}

//Modifiers
bool Impl_Float_::show_full(bool inFlag){
    bool toreturn(m_show_full);
    m_show_full = inFlag;
    return toreturn;
}
    //Multiplies integer by a power of ten
void Impl_Float_::shift(lli tens_exp)
    {m_whole.shift(tens_exp);}
void Impl_Float_::sign(Sign newsign)
    {m_whole.sign(newsign);}
void Impl_Float_::negate()
    {m_whole.negate();}

Impl_Float_& Impl_Float_::exponentiate(const Impl_Float_& s, Size_Type prec){
    return
        s.count_right_digits()
        ? this->Exponentiate_Hub(s, prec)
        : this->Exponentiate_Hub(s.integer())
    ;
}

//Overload cast operators
Impl_Float_::operator Integer() const
    {return this->integer();}

//Constructors and destructor
Impl_Float_::Impl_Float_(ld inFP, Size_Type inPrec)
    : m_whole(1)
    , m_precision(inPrec ? inPrec : k_default_prec)
    , m_show_full(false)
{
    Sign newsign(inFP < 0 ? -1 : 1);

    std::stringstream catalyst("");
        //Use std::fixed to ensure converting the whole number
        catalyst << std::fixed << (inFP * newsign);
    std::string stage2(catalyst.str());
    m_whole.shift(m_precision - stage2.substr(stage2.find('.')+1).size());

    while(stage2.substr(stage2.find('.')+1).size() > inPrec)
        stage2.pop_back();
    
    if(stage2.find('.') != Str::npos)
        stage2.erase(stage2.find('.'), 1);
    stage2.insert(0, 1, newsign == -1 ? '-' : '+');
    m_whole *= Integer(stage2);
}

Impl_Float_::Impl_Float_(diglist inImage, Size_Type inPrec)
    : m_whole(1)
    , m_precision(inPrec)
    , m_show_full(false)
{
    if(inImage.find('.') == Str::npos)
        m_whole = Integer(inImage + Str(m_precision, '0'));
    else{
        m_whole.shift(
            m_precision
            - (inImage.size() - inImage.find('.'))
            + 1
        );
        while((inImage.size() - inImage.find('.') - 1) > inPrec)
            inImage.pop_back();

        inImage.erase(inImage.find('.'), 1);
        m_whole *= Integer(inImage);
    }
}

Impl_Float_::Impl_Float_(const Integer& inInt, Size_Type inPrec)
    : m_whole(inInt)
    , m_precision(inPrec)
    , m_show_full(false)
{m_whole.shift(inPrec);}

Impl_Float_::Impl_Float_(const UInteger& inInt, Size_Type inPrec)
    : m_whole(inInt.base())
    , m_precision(inPrec)
    , m_show_full(false)
{m_whole.shift(inPrec);}

//Helpers
void Impl_Float_::Update_Precision(Size_Type newPrec){
    if(newPrec >= m_precision) return;
    m_whole.shift(-static_cast<lli>(m_precision - newPrec));
    m_precision = newPrec;
}
Impl_Float_::Integer Impl_Float_::Generate_Operand(Size_Type inPrec)const{
    if(inPrec <= m_precision) return m_whole;
    Integer toreturn(m_whole);
    toreturn.shift(inPrec - m_precision);
    return toreturn;
}
Impl_Float_& Impl_Float_::Exponentiate_Hub(Integer counter){
    if(counter == 0)        return *this = 1;
    else if(counter == 1)   return *this;
    else if(counter == -1)  return *this = 1 / *this;

    bool neg(counter.sign() == -1);
    counter = counter.magnitude();
    Impl_Float_ operand(*this);
        //Exponentiation by squaring
    if(counter.even())
        *this = ( (operand * operand) ^ (counter/2) );
    else
        *this = operand * ( operand ^ (counter - 1) );    

    if(neg)
        return *this = 1 / *this;
    return *this;
}
Impl_Float_& Impl_Float_::Exponentiate_Hub(
    const Impl_Float_& s,
    Size_Type prec
){
    if(s == 0)        return *this = 1;
    else if(s == 1)   return *this;
    else if(s == -1)  return *this = 1 / *this;

    /*
        a^b [not XOR]
        = e^(ln(a^b))
        = e^(b*ln(a))
        
        ln(a) = SUM[n:1->INFINITY](
            ((-1^(n+1))
            * (a-1)^n
            * (a - int(a))^n
            / n
        )
        e^C = SUM[i:1->INFINITY]( C^i/i! )
    */
    
    const Impl_Float_ exponent(s.magnitude());
    const bool inverted(this->magnitude() > 1);
    Impl_Float_
        nlogged(0),
        _x(inverted ? (1 / *this) : *this)
    ;
    for(Size_Type i(1); i < (prec ? prec : m_precision); ++i){
        nlogged
            += (i % 2 == 1 ? 1 : -1)
            * ( (_x - 1) ^ i )
            / i
        ;
    }

    if(inverted)
        nlogged.negate();
    nlogged *= exponent;
    *this = 0;
    for(Size_Type i(0); i < (prec ? prec : (m_precision*2)/5); ++i)
        *this += (nlogged ^ i) / Precision::Factorial(i);
    if(s.sign() < 0)
        *this = 1 / *this;

    return *this;
}


Impl_Float_ operator+(Impl_Float_ lhs, const Impl_Float_& rhs)
    {return lhs += rhs;}
Impl_Float_ operator-(Impl_Float_ lhs, const Impl_Float_& rhs)
    {return lhs -= rhs;}
Impl_Float_ operator*(Impl_Float_ lhs, const Impl_Float_& rhs)
    {return lhs *= rhs;}
Impl_Float_ operator/(Impl_Float_ lhs, const Impl_Float_& rhs)
    {return lhs /= rhs;}
Impl_Float_ operator%(Impl_Float_ lhs, const Impl_Float_& rhs)
    {return lhs %= rhs;}

Impl_Float_ operator^(Impl_Float_ lhs, const Impl_Float_& rhs){
    if(rhs.count_right_digits() > 0)    return lhs ^= rhs;
    else                                return lhs ^= rhs.integer();
}

bool operator==(const Impl_Float_& lhs, const Impl_Float_& rhs)
    {return lhs.compare(rhs) == 0;}
bool operator!=(const Impl_Float_& lhs, const Impl_Float_& rhs)
    {return lhs.compare(rhs) != 0;}
bool operator>=(const Impl_Float_& lhs, const Impl_Float_& rhs)
    {return lhs.compare(rhs) >= 0;}
bool operator<=(const Impl_Float_& lhs, const Impl_Float_& rhs)
    {return lhs.compare(rhs) <= 0;}
bool operator>(const Impl_Float_& lhs, const Impl_Float_& rhs)
    {return lhs.compare(rhs) > 0;}
bool operator<(const Impl_Float_& lhs, const Impl_Float_& rhs)
    {return lhs.compare(rhs) < 0;}
bool operator!(const Impl_Float_& lhs)
    {return lhs == 0;}