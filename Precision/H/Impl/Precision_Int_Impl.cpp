#include "Precision_Int_Impl.h"

#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>

Impl_Int_ IPow(const Impl_Int_&, const Impl_Int_&);
Impl_Int_ ILog(const Impl_Int_&, const Impl_Int_&);

//Overloaded operators
Impl_Int_& Impl_Int_::operator+=(const Impl_Int_& rhs){
    if(rhs == 0) return *this;
    if(*this == 0) return (*this = rhs);
    diglist sum;
    Impl_Int_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude()) std::swap(big, small);
    while(small.m_number.size() < big.m_number.size())
        small.m_number += '0';

    digit carry(0);
    this->m_sign = big.m_sign;
    if(big.m_sign == -1) big.m_sign = 1, small.m_sign *= -1;
    for(size_t i(0); i < small.m_number.size(); ++i){
        digit catalyst(
            (big.m_number[i]-'0')*big.m_sign
            + (small.m_number[i]-'0')*small.m_sign
            + carry
        );
    //Carry a number
        if(catalyst >= k_limit) catalyst %= k_limit, carry=1;
        else if(catalyst <= -k_limit) catalyst += k_limit, carry=-1;
        else carry = 0;
    //Borrow a number
        if(catalyst < 0 && i+1 < big.m_number.size())
            --big.m_number[i+1], catalyst += k_limit;

        sum += catalyst+'0';
        if(carry > 0 && i+1 == big.m_number.size())
            sum += carry + '0';
    }
    while(sum.back() == '0') sum.pop_back();
    this->m_number = sum;
    return *this;
}
Impl_Int_& Impl_Int_::operator-=(const Impl_Int_& rhs){
    if(*this == rhs) return (*this = 0);
    return (*this += (-rhs));
}

Impl_Int_& Impl_Int_::operator*=(const Impl_Int_& rhs){
    if(rhs == 0) return *this = 0;
    else if(*this == 0 || rhs == 1) return *this;
    else if(*this == 1) return *this = rhs;
    else if(rhs == -1) return m_sign *= -1, *this;
    else if(*this == -1){
        *this = rhs;
        m_sign *= -1;
        return *this;
    }
    Sign sign_hold(m_sign * rhs.m_sign);
    Impl_Int_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude()) std::swap(big, small);
    size_t z_count(0);
    while(big.m_number[0] == '0')
        big.m_number.erase(0, 1), ++z_count;
    while(small.m_number[0] == '0')
        small.m_number.erase(0, 1), ++z_count;
    std::vector<Impl_Int_> addends;
//Cut down on runtime by reducing number of iterations
    for(size_t i(0); i < small.m_number.size(); ++i){
        Impl_Int_ addend(0);
        short operand(small.m_number[i]-'0');
        while(operand-- > 0) addend += big;
        addend.m_number.insert(0, i, '0');
        addends.push_back(addend);
    }
    *this = 0;
    for(
        auto addend(addends.begin());
        addend != addends.end();
        ++addend
    ) *this += *addend;
    m_number.insert(0, z_count, '0');
    this->m_sign = sign_hold;
    return *this;
}
Impl_Int_& Impl_Int_::operator/=(const Impl_Int_& rhs){
    if(*this == rhs) return (*this = 1);
    else if(rhs == 0 || this->magnitude() < rhs.magnitude())
        return (*this = 0);
    else if(rhs == 1) return *this;

    Impl_Int_
        toreturn(0),
        t_abs(this->magnitude()),
        tens(rhs.magnitude())
    ;
    size_t t_counter(t_abs.m_number.size() - tens.m_number.size());
//Cut down on runtime by reducing number of iterations
    tens.m_number.insert(0, t_counter, '0');

    while(tens >= rhs.magnitude()){
        while(t_abs >= tens){
            Impl_Int_ addend("1" + Str(t_counter, '0'));
            toreturn += addend;
            t_abs -= tens;
        }
        tens.m_number.erase(0, 1), --t_counter;
    }
    toreturn.m_sign = this->m_sign * rhs.m_sign;
    return (*this = toreturn);
}
Impl_Int_& Impl_Int_::operator%=(const Impl_Int_& rhs){
    if(rhs == *this || rhs == 0) return (*this = 0);
    else if(rhs.magnitude() > this->magnitude()) return *this;
    return *this -= (*this/rhs)*rhs;
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
void bitwise_helper(
    Impl_Int_& f, Impl_Int_ s,
    std::function<void(BitSet&, BitSet&)> operation
){
    BitSet fbits(1, f.sign() < 0), sbits(1, s.sign() < 0);
    Impl_Int_ twos(0);

    twos = IPow(2, ILog(2, f));
    for(; twos > 0; twos /= 2){
        if(f >= twos)
            f -= twos, fbits.push_back(true);
        else fbits.push_back(false);
    }
    twos = IPow(2, ILog(2, s));
    for(; twos > 0; twos /= 2){
        if(s >= twos)
            s -= twos, sbits.push_back(true);
        else sbits.push_back(false);
    }

    std::reverse(fbits.begin(), fbits.end());
    std::reverse(sbits.begin(), sbits.end());

    size_t bit_num(fbits.size());
        if(bit_num < sbits.size()) bit_num = sbits.size();
    fbits.resize(bit_num, false);
    sbits.resize(bit_num, false);

    --bit_num;
    operation(fbits, sbits);
    f = f.magnitude();
    while(bit_num-- > 0) f += fbits[bit_num]
        ? IPow(Impl_Int_(2), bit_num) : 0;
    if(fbits.back())
        f *= -1;
}
Impl_Int_& Impl_Int_::operator&=(const Impl_Int_& rhs){
    bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
        for(size_t i(0); i < l.size(); ++i)
            l[i] = (l[i] == r[i] && l[i] == true) ? true : false;}
    );
    return *this;
}
Impl_Int_& Impl_Int_::operator|=(const Impl_Int_& rhs){
    bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
        for(size_t i(0); i < l.size(); ++i)
            l[i] = (l[i] == true || r[i] == true) ? true : false;}
    );
    return *this;
}
Impl_Int_& Impl_Int_::operator^=(const Impl_Int_& rhs){
    bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
        for(size_t i(0); i < l.size(); ++i)
            l[i] = (l[i] != r[i]) ? true : false;}
    );
    return *this;
}
Impl_Int_& Impl_Int_::operator<<=(const Impl_Int_& rhs)
    {return *this *= IPow(2, rhs);}
Impl_Int_& Impl_Int_::operator>>=(const Impl_Int_& rhs)
    {return *this /= IPow(2, rhs);}

    
//Read-only functions
Impl_Int_::Sign Impl_Int_::sign()const
    {return m_sign;}
Impl_Int_::Str Impl_Int_::str()const{
    if(*this == 0)   return "+0";
    Str toreturn(m_sign == 1 ? "+" : "-");
    for(auto iter(m_number.size()); iter > 0; --iter)
        toreturn += m_number[iter-1];
    return toreturn;
}
Impl_Int_::Str Impl_Int_::sci_note(size_t prec)const{
    if(*this == 0)   return "+0";

    Str toreturn(m_sign == 1 ? "+" : "-");
    toreturn += m_number.back(); toreturn += ".";
    for(size_t i(2); i <= prec+1 && i <= m_number.size(); ++i)
        toreturn += m_number[m_number.size()-i];
    while(toreturn.size() < k_display_prec) toreturn += '0';
    toreturn += 'E';
    std::stringstream ss;
        ss << m_number.size() - 1;
    toreturn += ss.str();
    return toreturn;
}
Impl_Int_::Str Impl_Int_::sci_note_w_spaces(size_t prec)const{
    Str toreturn(this->sci_note(prec));
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
size_t Impl_Int_::count_digits()const
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
    for(size_t i(m_number.size()); i > 0; --i){
        if(m_number[i-1] < s.m_number[i-1])         return -1;
        else if(m_number[i-1] > s.m_number[i-1])    return 1;    
    }
                                                    return 0;
}
Impl_Int_ Impl_Int_::operator-()const{
    Impl_Int_ toreturn(*this);
    toreturn.m_sign *= -1;
    return toreturn;
}
Impl_Int_ Impl_Int_::operator~()const{
    BitSet bits(1, m_sign < 0);
    Impl_Int_ twos(1), f(*this);

    while(twos < f)
        twos *= 2;
    Impl_Int_ twos_complement(twos);
    twos_complement.m_sign = m_sign * -1;
    twos /= 2;
    for(; twos > 0; twos /= 2){
        if(f >= twos)
            f -= twos, bits.push_back(true);
        else bits.push_back(false);
    }
    
    std::reverse(bits.begin(), bits.end());

    f = f.magnitude();
    for(size_t i(0); i < bits.size()-1; ++i)
        f += bits[i] ? 0 : IPow(2, i);
    f += twos_complement;
    return f;
}

//Other modifiers
void Impl_Int_::shift(lli tens_exp){
    if(tens_exp == 0) return;
    else if(tens_exp > 0)
        m_number.insert(0, tens_exp, '0');
    else if(tens_exp < 0 && -tens_exp < m_number.size())
        m_number.erase(0, -tens_exp);
    else *this = 0;
}


//Constructors and destructor
Impl_Int_::Impl_Int_(lli newnumber)
    : m_number({})
    , m_sign(newnumber < 0 ? -1 : 1)
{
    newnumber *= m_sign;
    while(newnumber > 0){
        m_number.push_back(newnumber%k_limit + '0');
        newnumber/=k_limit;
    }
    if(m_number.size() == 0) m_number = "0";
}

Impl_Int_::Impl_Int_(diglist newnumber)
    : m_number(newnumber.substr(
        (newnumber[0] == '-' || newnumber[0] == '+')
        ? 1 : 0
    ))
    , m_sign(newnumber[0] == '-' ? -1 : 1)
{
    std::reverse(m_number.begin(), m_number.end());
    for(size_t i(0); i < m_number.size(); ++i)
        if(!isdigit(m_number[i])) m_number[i] = '0';
    while(m_number.back() == '0' && m_number.size() > 1)
        m_number.pop_back();
}


Impl_Int_ operator+(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) += rhs;}
Impl_Int_ operator-(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) -= rhs;}
Impl_Int_ operator*(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) *= rhs;}
Impl_Int_ operator/(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) /= rhs;}
Impl_Int_ operator%(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) %= rhs;}

Impl_Int_ operator&(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) &= rhs;}
Impl_Int_ operator|(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) |= rhs;}
Impl_Int_ operator^(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) ^= rhs;}
Impl_Int_ operator>>(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) >>= rhs;}
Impl_Int_ operator<<(Impl_Int_ lhs, const Impl_Int_& rhs)
    {return Impl_Int_(lhs) <<= rhs;}

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

Impl_Int_ IPow(
    const Impl_Int_& f,
    const Impl_Int_& s
){
    if(s == 0)          return 1;
    else if(s == 1)     return f;
    else if(s < 0)      return 0;

    Impl_Int_ toreturn(f);
    for(auto e(s); e > 1; --e)
        toreturn *= f;

    return toreturn;
}
Impl_Int_ ILog(const Impl_Int_& base, const Impl_Int_& result){
        if(base == result) return 1;
        else if(base > result) return 0;
        Impl_Int_ toreturn(1), testee(base);
        while(testee < result)
            ++toreturn, testee *= base;
        return toreturn;
}