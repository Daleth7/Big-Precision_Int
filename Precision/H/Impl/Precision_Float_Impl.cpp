#include "Precision_Float_Impl.h"

#include "Precision_Int.h"
#include "Precision_UInt.h"
#include "Precision_Math_Shared_Functions.h"

#include <sstream>
#include <utility>

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
    m_whole.shift_right(rhs.m_precision);
    this->Update_Precision(rhs.m_precision);
    return *this;
}
Impl_Float_& Impl_Float_::operator/=(const Impl_Float_& rhs){
    Integer exp(1);
    exp.shift_left(rhs.count_right_digits());
    Impl_Float_ operand(rhs * exp);
    (m_whole *= exp) /= operand.integer();

    this->Update_Precision(rhs.m_precision);
    return *this;
}
Impl_Float_& Impl_Float_::operator%=(const Impl_Float_& rhs){
    if(*this == rhs || rhs == 0) return *this = 0;

    *this /= rhs;
    Impl_Float_ catalyst(*this);
    catalyst.shift_right(m_precision);
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
Impl_Float_& Impl_Float_::operator^=(const Impl_Float_& s){
    return (
        (s.count_right_digits() > 0)
        ? this->exponentiate(s, m_precision)
        : this->exponentiate(s.integer())
    );
}



//Read-only functions
Impl_Float_::sign_type Impl_Float_::sign()const
    {return m_whole.sign();}

bool Impl_Float_::even()const
    {return m_whole.even();}

bool Impl_Float_::odd()const
    {return m_whole.odd();}

Impl_Float_::str_type Impl_Float_::str(size_type inPrec, bool inShowFull)const{
    if(inPrec > m_precision)
        inPrec = m_precision;
    str_type toreturn(m_whole.str());

    if(toreturn == "+0")
        return toreturn += "." + str_type(inPrec ? inPrec : 1, '0');
        //If the number is something like 0.009
    if(m_precision > m_whole.count_digits())
        toreturn.insert(1, m_precision - m_whole.count_digits(), '0');
    toreturn.insert(toreturn.size() - m_precision, 1, '.');

    if(m_precision >= m_whole.count_digits())
        toreturn.insert(1, 1, '0');
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

    size_type min = m_precision - inPrec - 1;
    while(min-- > 0) toreturn.pop_back();
    
    if(toreturn.back() == '.' && m_precision > 0)
        toreturn += "0";
    else
        toreturn.pop_back();
    
    return toreturn;
}

//Set the precision through parameter
Impl_Float_::str_type Impl_Float_::sci_note(size_type inPrec, bool inShowFull)const{
    if(inPrec == 0)
        inPrec = m_precision;
    str_type toreturn(m_whole.sci_note((m_show_full || inShowFull)
        ? m_precision : inPrec));
    toreturn.erase(toreturn.find('E')+1);

    std::stringstream ss;
    if(m_whole.count_digits() < m_precision)
        toreturn + "-", ss << (m_precision - m_whole.count_digits() + 1);
    else
        ss << (m_whole.count_digits() - m_precision - 1);
    toreturn += ss.str();

    return toreturn;
}

Impl_Float_::str_type Impl_Float_::sci_note_w_spaces(
    size_type inPrec,
    bool inShowFull
)const{
    str_type toreturn(this->sci_note(inPrec, inShowFull));
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

Impl_Float_::size_type Impl_Float_::count_digits()const
    {return this->count_left_digits() + this->count_right_digits();}

Impl_Float_::size_type Impl_Float_::count_left_digits()const
    {return m_whole.count_digits() - m_precision;}

Impl_Float_::size_type Impl_Float_::count_right_digits()const{
    if(m_whole == 0) return 1;
    std::string image(m_whole.str().substr(
            //Add 1 to account for sign character
        m_whole.count_digits() + 1 - m_precision
    ));
    while(image.back() == '0') image.pop_back();
    return image.size();
}

Impl_Float_::size_type Impl_Float_::precision()const
    {return m_precision;}

short Impl_Float_::compare(const Impl_Float_& s)const{
    if(m_whole.sign() < s.m_whole.sign())       return -1;
    else if(m_whole.sign() > s.m_whole.sign())  return 1;

    else if(m_whole == 0 && s.m_whole != 0)     return -1;
    else if(m_whole != 0 && s.m_whole == 0)     return 1;
    Integer a(m_whole), b(s.m_whole);

    if(m_precision > s.m_precision)
        a.shift_right(m_precision - s.m_precision);
    else
        b.shift_right(s.m_precision - m_precision);

    return a.compare(b);
}

Impl_Float_::Integer Impl_Float_::integer()const{
    Integer toreturn(m_whole);
    toreturn.shift_right(m_precision);
    return toreturn;
}

bool Impl_Float_::show_full()const
    {return m_show_full;}

Impl_Float_ Impl_Float_::remainder(const Impl_Float_& s)const
    {return *this % s;}

Impl_Float_ Impl_Float_::inverse()const
    {return ~(*this);}

bool Impl_Float_::is_integer()const
    {return this->count_right_digits() == 0;}

//Modifiers
bool Impl_Float_::show_full(bool inFlag){
    bool toreturn(m_show_full);
    m_show_full = inFlag;
    return toreturn;
}
    //Multiplies integer by a power of ten
void Impl_Float_::shift(lli tens_exp)
    {m_whole.shift(tens_exp);}
void Impl_Float_::shift_left(size_type e)
    {m_whole.shift_left(e);}
void Impl_Float_::shift_right(size_type e)
    {m_whole.shift_right(e);}
void Impl_Float_::sign(sign_type newsign)
    {m_whole.sign(newsign);}
void Impl_Float_::negate()
    {m_whole.negate();}

Impl_Float_& Impl_Float_::exponentiate(const Integer& exp)
    {return *this = Precision::exponentiate(*this, exp);}

Impl_Float_& Impl_Float_::exponentiate(const Impl_Float_& s, size_type prec){
    if(this->sign() < 0 && m_whole % 4 != 0)   return *this = 0;
    return *this = Precision::exponentiate(*this, s, prec ? prec : m_precision);
}

Impl_Float_& Impl_Float_::invert()
    {return *this = 1 / *this;}

void Impl_Float_::swap(Impl_Float_& s){
    std::swap(m_whole, s.m_whole);
    std::swap(m_precision, s.m_precision);
    std::swap(m_show_full, s.m_show_full);
}

//Overload cast operators
Impl_Float_::operator Integer() const
    {return this->integer();}

//Constructors and destructor
Impl_Float_::Impl_Float_(ld inFP, size_type inPrec)
    : m_whole(1)
    , m_precision(inPrec ? inPrec : k_default_prec)
    , m_show_full(false)
{
    sign_type newsign(inFP < 0 ? -1 : 1);

    std::stringstream catalyst("");
        //Use std::fixed to ensure converting the whole number
        catalyst << std::fixed << (inFP * newsign);
    std::string stage2(catalyst.str());
    m_whole.shift_left(m_precision
        - stage2.substr(stage2.find('.')+1).size());

    while(stage2.substr(stage2.find('.')+1).size() > inPrec)
        stage2.pop_back();
    
    if(stage2.find('.') != str_type::npos)
        stage2.erase(stage2.find('.'), 1);
    stage2.insert(0, 1, newsign == -1 ? '-' : '+');
    m_whole *= Integer(stage2);
}

Impl_Float_::Impl_Float_(str_type inImage, size_type inPrec)
    : m_whole(1)
    , m_precision(inPrec)
    , m_show_full(false)
{
    if(inImage.find('.') == str_type::npos)
        m_whole = Integer(inImage + str_type(m_precision, '0'));
    else{
        m_whole.shift_left(
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

Impl_Float_::Impl_Float_(const Integer& inInt, size_type inPrec)
    : m_whole(inInt)
    , m_precision(inPrec)
    , m_show_full(false)
{m_whole.shift_left(inPrec);}

Impl_Float_::Impl_Float_(const UInteger& inInt, size_type inPrec)
    : m_whole(inInt.base())
    , m_precision(inPrec)
    , m_show_full(false)
{m_whole.shift_left(inPrec);}

//Helpers
void Impl_Float_::Update_Precision(size_type newPrec){
    if(newPrec >= m_precision) return;
    m_whole.shift_right(m_precision - newPrec);
    m_precision = newPrec;
}

Impl_Float_::Integer Impl_Float_::Generate_Operand(size_type inPrec)const{
    if(inPrec <= m_precision) return m_whole;
    Integer toreturn(m_whole);
    toreturn.shift_left(inPrec - m_precision);
    return toreturn;
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

Impl_Float_ operator^(Impl_Float_ lhs, const Impl_Float_& rhs)
    {return lhs ^= rhs;}

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

void swap(Impl_Float_& a, Impl_Float_& b)
    {a.swap(b);}