#include "Precision_Int_Impl.h"

#ifndef GENERAL_BASE

#include "Precision_Math_Shared_Functions.h"

#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <utility>

//Overloaded operators
Impl_Int_& Impl_Int_::operator+=(const Impl_Int_& rhs){
    if(rhs == 0) return *this;
    if(*this == 0) return (*this = rhs);

    Impl_Int_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude()) std::swap(big, small);
    while(small.m_number.size() < big.m_number.size())
        small.m_number += k_0bit;

    digit10 carry(0);
    this->m_sign = big.m_sign;
    if(big.m_sign == -1) big.m_sign.make_positive(), small.m_sign.negate();

    auto biter(big.m_number.begin());
    auto siter(small.m_number.begin());
    for(; siter != small.m_number.end(); ++biter, ++siter){
        digit10 catalyst(
            (*biter-k_0bit)
            + (*siter-k_0bit)*small.m_sign
            + carry
        );
    //Carry a number
        if(catalyst >= k_limit)
            catalyst %= k_limit, carry=1;
        else
            carry = 0;
    //Borrow a number
        auto bcopy(biter);
            ++bcopy;
        if(catalyst < 0 && bcopy != big.m_number.end()){
            --(*bcopy), catalyst += k_limit;
            auto bcopy2(bcopy), bcopy3(bcopy);
            while(*bcopy3 < k_0bit && (++bcopy2) != big.m_number.end())
                *(bcopy3++) += k_limit, --(*bcopy2);
//Not the proper way to handle error: -1 for left-most digit_type
//  Still need to find out how this situation even occurs
            if(*bcopy3 < k_0bit)
                *bcopy3 = k_0bit-(*bcopy3 - k_0bit), this->m_sign.negate();
        }

        *biter = (catalyst+k_0bit);
        if(carry > 0 && bcopy == big.m_number.end())
            big.m_number.push_back(carry + k_0bit);
    }

    while(big.m_number.back() == k_0bit) big.m_number.pop_back();
    this->m_number = big.m_number;

    return *this;
}
Impl_Int_& Impl_Int_::operator-=(const Impl_Int_& rhs){
    if(*this == rhs) return (*this = 0);
    return (*this += (-rhs));
}

Impl_Int_& Impl_Int_::operator*=(const Impl_Int_& rhs){
    if(rhs == 0)                      return *this = 0;
    else if(*this == 0 || rhs == 1)   return *this;
    else if(*this == 1)               return *this = rhs;
    else if(rhs == -1)                return m_sign.negate(), *this;
    else if(*this == -1){
        *this = rhs;
        m_sign.negate();
        return *this;
    }
    sign_type sign_hold(m_sign * rhs.m_sign);

    Impl_Int_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude())
        std::swap(big, small);
    size_type z_count(0);
    while(big.m_number.front() == k_0bit)
        big.m_number.erase(0, 1), ++z_count;
    while(small.m_number.front() == k_0bit)
        small.m_number.erase(0, 1), ++z_count;
    std::vector<Impl_Int_> addends;
//Cut down on runtime by reducing number of iterations
    auto iter(small.m_number.begin());
    for(
        size_type i(0);
        i < small.m_number.size();
        ++i, ++iter
    ){
        Impl_Int_ addend(0);
        digit10 operand(*iter-k_0bit);
        while(operand-- > 0)
            addend += big;
        addend.m_number.insert(0, i, k_0bit);
        addends.push_back(addend);
    }
    m_number = diglist_type(1, k_0bit);
    for(
        auto addend(addends.begin());
        addend != addends.end();
        ++addend
    ) *this += *addend;
    m_number.insert(0, z_count, k_0bit);

    this->m_sign = sign_hold;
    return *this;

}

Impl_Int_& Impl_Int_::operator/=(const Impl_Int_& rhs){
    if(*this == rhs) return (*this = 1);
    else if(rhs == 0 || this->magnitude() < rhs.magnitude())
        return (*this = 0);
    else if(rhs == 1) return *this;
    return divide(rhs);
}
Impl_Int_& Impl_Int_::operator%=(const Impl_Int_& rhs){
    if(rhs == *this || rhs == 0 || rhs == 1) return (*this = 0);
    else if(rhs.magnitude() > this->magnitude()) return *this;
    else if(rhs == 2)   return *this = this->odd();
    return divide(rhs, true);
}
Impl_Int_& Impl_Int_::operator--()
    {return (*this += -1);}
Impl_Int_ Impl_Int_::operator--(int)
    {return (*this += -1)+1;}
Impl_Int_& Impl_Int_::operator++()
    {return (*this += 1);}
Impl_Int_ Impl_Int_::operator++(int)
    {return (*this += 1)-1;}

//Bitwise operators
//Use vector<bool> for dynamic sized bitsets
typedef std::vector<bool> BitSet;
Impl_Int_& Impl_Int_::operator&=(const Impl_Int_& rhs){return
    bitwise_operation(rhs, [](bool l, bool r){return (l == r && l == true);});}
Impl_Int_& Impl_Int_::operator|=(const Impl_Int_& rhs){return
    bitwise_operation(rhs, [](bool l, bool r){return (l == true || r == true);});}
Impl_Int_& Impl_Int_::operator^=(const Impl_Int_& rhs){return
    bitwise_operation(rhs, [](bool l, bool r){return (l != r);});}
Impl_Int_& Impl_Int_::operator<<=(const Impl_Int_& rhs)
    {return *this *= Precision::exponentiate(Impl_Int_(2), rhs);}
Impl_Int_& Impl_Int_::operator>>=(const Impl_Int_& rhs)
    {return *this /= Precision::exponentiate(Impl_Int_(2), rhs);}

    
//Read-only functions
Impl_Int_::sign_type Impl_Int_::sign()const
    {return m_sign;}
Impl_Int_::str_type Impl_Int_::str()const{
    if(*this == 0)   return "+0";
    str_type toreturn(m_number + (m_sign == 1 ? "+" : "-"));
    std::reverse(toreturn.begin(), toreturn.end());
    return toreturn;
}
Impl_Int_::str_type Impl_Int_::sci_note(size_type prec)const{
    if(*this == 0)
        return "+0";
    else if(m_number.size() < 2)
        return this->str() + "E1";

    str_type toreturn(this->str());
    size_type exp(toreturn.size() - 2);
    toreturn.insert(2, 1, '.');
    if(prec < exp)
        toreturn.erase(3+prec);
    if(toreturn.back() == '.')
        toreturn.pop_back();
    std::stringstream ss;
        ss << exp;
    toreturn += "E" + ss.str();

    return toreturn;
}
Impl_Int_::str_type Impl_Int_::sci_note_w_spaces(size_type prec)const{
    str_type toreturn(this->sci_note(prec));
    if(toreturn == "0") return toreturn;
    toreturn.insert(1, 1, ' ');//Insert space after the sign
    toreturn.insert(toreturn.find('E'), 1, ' ');
    toreturn.insert(toreturn.find('E')+1, 1, ' ');
    return toreturn;
}
Impl_Int_ Impl_Int_::magnitude()const{
    //Seclude from multiplication operators
    Impl_Int_ toreturn(*this);
        toreturn.m_sign = 1;
    return toreturn;
}
Impl_Int_::size_type Impl_Int_::count_digits()const
    {return m_number.size();}
short Impl_Int_::compare(const Impl_Int_& s)const{
    if(this == &s)                                  return 0;
    else if(m_sign < s.m_sign)                      return -1;
    else if(m_sign > s.m_sign)                      return 1;
    else if(m_number == s.m_number)                 return 0;
    else if(m_sign == -1 && m_number.size() > s.m_number.size())
                                                    return -1;
    else if(m_sign == -1 && m_number.size() < s.m_number.size())
                                                    return 1;
    else if(m_number.size() < s.m_number.size())    return -1;
    else if(m_number.size() > s.m_number.size())    return 1;
    else if(m_sign == -1){
        for(size_type i(m_number.size()); i > 0; --i){
            if(m_number[i-1] > s.m_number[i-1])     return -1;
            else if(m_number[i-1] < s.m_number[i-1])return 1;    
        }
    }
    for(size_type i(m_number.size()); i > 0; --i){
        if(m_number[i-1] < s.m_number[i-1])         return -1;
        else if(m_number[i-1] > s.m_number[i-1])    return 1;    
    }
                                                    return 0;
}
Impl_Int_ Impl_Int_::operator-()const{
    Impl_Int_ toreturn(*this);
    toreturn.m_sign.negate();
    return toreturn;
}
Impl_Int_ Impl_Int_::operator~()const{
    if(*this == 0)
        return *this;
    BitSet bits(1, m_sign < 0);

    Impl_Int_ twos(1), f(*this);

    while(twos < f)
        twos *= 2;
    Impl_Int_ twos_complement(twos);
    twos_complement.m_sign = m_sign * -1;
    for(twos /= 2; twos > 0; twos /= 2){
        if(f >= twos)
            f -= twos, bits.push_back(true);
        else bits.push_back(false);
    }

    std::reverse(bits.begin(), bits.end());

    f = twos_complement;
    for(size_type i(0); i < bits.size()-1; ++i)
        f += bits[i] ? 0 : Precision::exponentiate(Impl_Int_(2), Impl_Int_(i));
    return f;
}
bool Impl_Int_::even()const
    {return !(this->odd());}
bool Impl_Int_::odd()const
    {return (m_number.front() - k_0bit) % 2;}

//Other modifiers
void Impl_Int_::shift(lli tens_exp){
    if(tens_exp < 0)
        this->shift_right(-tens_exp);
    else
        this->shift_left(tens_exp);
}

void Impl_Int_::shift_left(size_type e)
    {m_number.insert(0, e, k_0bit);}

void Impl_Int_::shift_right(size_type e)
    {m_number.erase(0, e);}

void Impl_Int_::sign(sign_type newsign)
    {m_sign = newsign;}
void Impl_Int_::negate()
    {m_sign.negate();}
void Impl_Int_::swap(Impl_Int_& s){
    std::swap(m_number, s.m_number);
    std::swap(m_sign, s.m_sign);
}

//Constructors and destructor
Impl_Int_::Impl_Int_(lli newnumber)
    : m_number({})
    , m_sign(newnumber < 0 ? -1 : 1)
{
    newnumber *= m_sign;
    while(newnumber > 0){
        m_number.push_back(newnumber%k_limit + k_0bit);
        newnumber/=k_limit;
    }
    if(m_number.size() == 0)
        m_number = diglist_type(1, k_0bit);
}

Impl_Int_::Impl_Int_(const diglist_type& newnumber)
    : m_number(newnumber.substr(
        (newnumber[0] == '-' || newnumber[0] == '+')
        ? 1 : 0
    ))
    , m_sign(newnumber[0] == '-' ? -1 : 1)
{
    std::reverse(m_number.begin(), m_number.end());
    for(size_type i(0); i < m_number.size(); ++i)
        if(!isdigit(m_number[i])) m_number[i] = k_0bit;
    while(m_number.back() == k_0bit && m_number.size() > 1)
        m_number.pop_back();
}

Impl_Int_& Impl_Int_::divide(const Impl_Int_& rhs, bool get_modulus){
    if(*this == rhs) return (*this = 1);
    else if(rhs == 0 || this->magnitude() < rhs.magnitude())
        return (*this = 0);
    else if(rhs == 1) return *this;

    Impl_Int_
        quotient(0),
        remainder(this->magnitude()),
        tens(rhs.magnitude())
    ;
    size_type t_counter(remainder.m_number.size() - tens.m_number.size());

    tens.m_number.insert(0, t_counter, k_0bit);

    while(tens >= rhs.magnitude()){
        Impl_Int_ addend("1" + str_type(t_counter, k_0bit));
        while(remainder >= tens){
            quotient += addend;
            remainder -= tens;
        }
        tens.m_number.erase(0, 1), --t_counter;
    }
    if(!get_modulus){
        quotient.m_sign = this->m_sign * rhs.m_sign;
        return (*this = quotient);
    }else
        return (*this = remainder);
}

Impl_Int_& Impl_Int_::bitwise_operation(
    Impl_Int_ s,
    const std::function<bool(bool, bool)>& operation
){
    BitSet fbits(1, this->sign() < 0), sbits(1, s.sign() < 0);

    Impl_Int_ twos(1);
    while(twos < *this)
        twos *= 2;
    for(twos /= 2; twos > 0; twos /= 2){
        if(*this >= twos)
            *this -= twos, fbits.push_back(true);
        else fbits.push_back(false);
    }

    twos = 1;
    while(twos < s)
        twos *= 2;
    for(twos /= 2; twos > 0; twos /= 2){
        if(s >= twos)
            s -= twos, sbits.push_back(true);
        else sbits.push_back(false);
    }

    std::reverse(fbits.begin(), fbits.end());
    std::reverse(sbits.begin(), sbits.end());

    size_type bit_num(fbits.size());
        if(bit_num < sbits.size()) bit_num = sbits.size();
    fbits.resize(bit_num, false);
    sbits.resize(bit_num, false);

    --bit_num;
    for(size_t i(0); i < fbits.size(); ++i)
        fbits[i] = operation(fbits[i], sbits[i]);

    while(bit_num-- > 0)
        *this += fbits[bit_num]
            ? Precision::exponentiate(Impl_Int_(2), Impl_Int_(bit_num))
            : 0;
    if(fbits.back())
        this->sign(-1);

    return *this;
}

Impl_Int_ operator+(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs += rhs;}
Impl_Int_ operator-(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs -= rhs;}
Impl_Int_ operator*(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs *= rhs;}
Impl_Int_ operator/(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs /= rhs;}
Impl_Int_ operator%(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs %= rhs;}

Impl_Int_ operator&(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs &= rhs;}
Impl_Int_ operator|(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs |= rhs;}
Impl_Int_ operator^(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs ^= rhs;}
Impl_Int_ operator>>(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs >>= rhs;}
Impl_Int_ operator<<(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return lhs <<= rhs;}

bool operator==(const Impl_Int_& lhs, const Impl_Int_& rhs)
    {return lhs.compare(rhs) == 0;}
bool operator!=(const Impl_Int_& lhs, const Impl_Int_& rhs)
    {return lhs.compare(rhs) != 0;}
bool operator>=(const Impl_Int_& lhs, const Impl_Int_& rhs)
    {return lhs.compare(rhs) >= 0;}
bool operator<=(const Impl_Int_& lhs, const Impl_Int_& rhs)
    {return lhs.compare(rhs) <= 0;}
bool operator>(const Impl_Int_& lhs, const Impl_Int_& rhs)
    {return lhs.compare(rhs) > 0;}
bool operator<(const Impl_Int_& lhs, const Impl_Int_& rhs)
    {return lhs.compare(rhs) < 0;}
bool operator!(const Impl_Int_& lhs)
    {return lhs == 0;}

void swap(Impl_Int_& a, Impl_Int_& b)
    {a.swap(b);}

#endif