#include "Precision_Math_Shared_Functions.h"

#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <utility>

INT_TEMPL_
constexpr typename INT_INST_::ntodec INT_INST_::m_n10;

INT_TEMPL_
constexpr typename INT_INST_::decton INT_INST_::m_10n;

//Overloaded operators
INT_TEMPL_
INT_INST_& INT_INST_::operator+=(const INT_INST_& rhs){
    if(rhs == INT_INST_(0)) return *this;
    if(*this == INT_INST_(0)) return (*this = rhs);

    INT_INST_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude()) std::swap(big, small);
    while(small.m_number.size() < big.m_number.size())
        small.m_number.push_back(k_0bit);

    digit_10_type carry(0);
    this->m_sign = big.m_sign;
    if(big.m_sign.negative())
        big.m_sign.make_positive(), small.m_sign.negate();

    auto biter(big.m_number.begin());
    auto siter(small.m_number.begin());
    for(; siter != small.m_number.end(); ++biter, ++siter){
        digit_10_type catalyst(
            m_n10(*biter)
            + m_n10(*siter)*small.m_sign
            + carry
        );
    //Carry a number
        if(catalyst >= k_base)
            catalyst %= k_base, carry=1;
        else
            carry = 0;
    //Borrow a number
        auto bcopy(biter);
            ++bcopy;
        if(catalyst < 0 && bcopy != big.m_number.end()){
            --(*bcopy), catalyst += k_base;
            auto bcopy2(bcopy), bcopy3(bcopy);
            while(*bcopy3 < k_0bit && (++bcopy2) != big.m_number.end())
                *(bcopy3++) += k_base, --(*bcopy2);
//Not the proper way to handle error: -1 for left-most digit_type
//  Still need to find out how this situation even occurs
            if(*bcopy3 < k_0bit)
                *bcopy3 = k_0bit-(*bcopy3 - k_0bit), this->m_sign.negate();
        }

        *biter = m_10n(catalyst);
        if(carry > 0 && bcopy == big.m_number.end())
            big.m_number.push_back(m_10n(carry));
    }

    while(big.m_number.back() == k_0bit) big.m_number.pop_back();
    this->m_number = big.m_number;

    return *this;
}

INT_TEMPL_
INT_INST_& INT_INST_::operator-=(const INT_INST_& rhs){
    if(*this == rhs) return (*this = INT_INST_(0));
    return (*this += (-rhs));
}

INT_TEMPL_
INT_INST_& INT_INST_::operator*=(const INT_INST_& rhs){
    if(rhs == INT_INST_(0))                      return *this = INT_INST_(0);
    else if(*this == INT_INST_(0) || rhs == INT_INST_(1))   return *this;
    else if(*this == INT_INST_(1))               return *this = rhs;
    else if(rhs == INT_INST_(-1))                return m_sign.negate(), *this;
    else if(*this == INT_INST_(-1)){
        *this = rhs;
        m_sign.negate();
        return *this;
    }
    sign_type sign_hold(m_sign * rhs.m_sign);

    INT_INST_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude())
        std::swap(big, small);
    size_type z_count(0);
    while(big.m_number.front() == k_0bit)
        big.m_number.erase(0, 1), ++z_count;
    while(small.m_number.front() == k_0bit)
        small.m_number.erase(0, 1), ++z_count;
    std::vector<INT_INST_> addends;
//Cut down on runtime by reducing number of iterations
    auto iter(small.m_number.begin());
    for(size_type i(0); i < small.m_number.size(); ++i, ++iter){
        INT_INST_ addend(0);
        digit_10_type operand(m_n10(*iter));
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

INT_TEMPL_
INT_INST_& INT_INST_::operator/=(const INT_INST_& rhs){
    if(*this == rhs) return (*this = 1);
    else if(rhs == INT_INST_(0) || this->magnitude() < rhs.magnitude())
        return (*this = INT_INST_(0));
    else if(rhs == INT_INST_(1)) return *this;
    return divide(rhs);
}

INT_TEMPL_
INT_INST_& INT_INST_::operator%=(const INT_INST_& rhs){
    if(rhs == *this || rhs == INT_INST_(0) || rhs == INT_INST_(1))
        return (*this = INT_INST_(0));
    else if(rhs.magnitude() > this->magnitude()) return *this;
    else if(rhs == INT_INST_(2))   return *this = this->odd();
    return divide(rhs, true);
}

INT_TEMPL_
INT_INST_& INT_INST_::operator--()
    {return (*this += -1);}

INT_TEMPL_
INT_INST_ INT_INST_::operator--(int)
    {return (*this += INT_INST_(-1))+INT_INST_(1);}

INT_TEMPL_
INT_INST_& INT_INST_::operator++()
    {return (*this += 1);}

INT_TEMPL_
INT_INST_ INT_INST_::operator++(int)
    {return (*this += INT_INST_(1))+INT_INST_(-1);}

//Bitwise operators
//Use vector<bool> for dynamic sized bitsets
typedef std::vector<bool> BitSet;
INT_TEMPL_
INT_INST_& INT_INST_::operator&=(const INT_INST_& rhs){return
    bitwise_operation(rhs, [](bool l, bool r){return (l == r && l == true);});}

INT_TEMPL_
INT_INST_& INT_INST_::operator|=(const INT_INST_& rhs){return
    bitwise_operation(rhs, [](bool l, bool r){return (l == true || r == true);});}

INT_TEMPL_
INT_INST_& INT_INST_::operator^=(const INT_INST_& rhs){return
    bitwise_operation(rhs, [](bool l, bool r){return (l != r);});}

INT_TEMPL_
INT_INST_& INT_INST_::operator<<=(const INT_INST_& rhs)
    {return *this *= Precision::exponentiate(INT_INST_(2), rhs);}

INT_TEMPL_
INT_INST_& INT_INST_::operator>>=(const INT_INST_& rhs)
    {return *this /= Precision::exponentiate(INT_INST_(2), rhs);}

    
//Read-only functions
INT_TEMPL_
const typename INT_INST_::ntodec& INT_INST_::converter_Nto10()const
    {return m_n10;}

INT_TEMPL_
const typename INT_INST_::decton& INT_INST_::converter_10toN()const
    {return m_10n;}

INT_TEMPL_
typename INT_INST_::sign_type INT_INST_::sign()const
    {return m_sign;}

INT_TEMPL_
typename INT_INST_::str_type INT_INST_::str()const{
    if(*this == INT_INST_(0))   return "+0";
    std::stringstream ss;
    for(auto iter(m_number.begin()); iter != m_number.end(); ++iter)
        ss << *iter;
    str_type toreturn(ss.str() + (m_sign.positive() ? "+" : "-"));
    std::reverse(toreturn.begin(), toreturn.end());
    return toreturn;
}

INT_TEMPL_
typename INT_INST_::str_type INT_INST_::sci_note(size_type prec)const{
    if(*this == INT_INST_(0))
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

INT_TEMPL_
typename INT_INST_::str_type INT_INST_::sci_note_w_spaces(size_type prec)const{
    str_type toreturn(this->sci_note(prec));
    if(toreturn == "0") return toreturn;
    toreturn.insert(1, 1, ' ');//Insert space after the sign
    toreturn.insert(toreturn.find('E'), 1, ' ');
    toreturn.insert(toreturn.find('E')+1, 1, ' ');
    return toreturn;
}

INT_TEMPL_
INT_INST_ INT_INST_::magnitude()const{
    //Seclude from multiplication operators
    INT_INST_ toreturn(*this);
        toreturn.m_sign = 1;
    return toreturn;
}

INT_TEMPL_
typename INT_INST_::size_type INT_INST_::count_digits()const
    {return m_number.size();}

INT_TEMPL_
short INT_INST_::compare(const INT_INST_& s)const{
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
        for(
            auto titer(m_number.rbegin()), siter(s.m_number.rbegin());
            titer != m_number.rend();
            ++titer, ++siter
        ){
            if(*titer > *siter)     return -1;
            else if(*titer < *siter)return 1;    
        }
    }
    for(
        auto titer(m_number.rbegin()), siter(s.m_number.rbegin());
        titer != m_number.rend();
        ++titer, ++siter
    ){
        if(*titer < *siter)         return -1;
        else if(*titer > *siter)    return 1;    
    }
                                                    return 0;
}

INT_TEMPL_
INT_INST_ INT_INST_::operator-()const{
    INT_INST_ toreturn(*this);
    toreturn.m_sign.negate();
    return toreturn;
}

INT_TEMPL_
INT_INST_ INT_INST_::operator~()const{
    if(*this == INT_INST_(0))
        return *this;
    BitSet bits(1, m_sign.negative());

    INT_INST_ twos(1), f(*this);

    while(twos < f)
        twos *= 2;
    INT_INST_ twos_complement(twos);
    twos_complement.m_sign = m_sign * -1;
    for(twos /= 2; twos > INT_INST_(0); twos /= 2){
        if(f >= twos)
            f -= twos, bits.push_back(true);
        else bits.push_back(false);
    }

    std::reverse(bits.begin(), bits.end());

    f = twos_complement;
    for(size_type i(0); i < bits.size()-1; ++i)
        f += bits[i] ? 0 : Precision::exponentiate(INT_INST_(2), INT_INST_(i));
    return f;
}

INT_TEMPL_
bool INT_INST_::even()const
    {return !(this->odd());}

INT_TEMPL_
bool INT_INST_::odd()const
    {return m_n10(m_number.front()) % 2;}

//Other modifiers
INT_TEMPL_
void INT_INST_::shift(lli tens_exp){
    if(tens_exp < 0)
        this->shift_right(-tens_exp);
    else
        this->shift_left(tens_exp);
}

INT_TEMPL_
void INT_INST_::shift_left(size_type e)
    {m_number.insert(0, e, k_0bit);}

INT_TEMPL_
void INT_INST_::shift_right(size_type e)
    {m_number.erase(0, e);}

INT_TEMPL_
void INT_INST_::sign(sign_type newsign)
    {m_sign = newsign;}

INT_TEMPL_
void INT_INST_::negate()
    {m_sign.negate();}

INT_TEMPL_
void INT_INST_::swap(INT_INST_& s){
    std::swap(m_number, s.m_number);
    std::swap(m_sign, s.m_sign);
}

//Constructors and destructor
INT_TEMPL_
INT_INST_::Int_General_Base(lli newnumber)
    : m_number(0, k_0bit)
    , m_sign(newnumber < 0 ? -1 : 1)
{
    newnumber *= m_sign;
    while(newnumber > 0){
        m_number.push_back(m_10n(newnumber%k_base));
        newnumber/=k_base;
    }
    if(m_number.size() == 0)
        m_number = diglist_type(1, k_0bit);
}

INT_TEMPL_
INT_INST_::Int_General_Base(const str_type& newnumber)
    : m_number(0, k_0bit)
    , m_sign(newnumber[0] == '-' ? -1 : 1)
{
    for(
        size_type i((newnumber[0] == '-' || newnumber[0] == '+') ? 1 : 0);
        i < newnumber.size();
        ++i
    )   m_number.push_back(m_10n(newnumber[i]-'0'));

    std::reverse(m_number.begin(), m_number.end());

    const digit_type lim = m_10n(k_base);
    for(auto iter(m_number.begin()); iter != m_number.end(); ++iter)
        if(*iter < k_0bit || *iter >= lim)  *iter = k_0bit;

    while(m_number.back() == k_0bit && m_number.size() > 1)
        m_number.pop_back();

    if(m_number.front() == k_0bit && m_number.size() == 1)
        m_sign.make_positive();
}

INT_TEMPL_
INT_INST_::Int_General_Base(const diglist_type& n, sign_type s)
    : m_number(n)
    , m_sign(s)
{
    std::reverse(m_number.begin(), m_number.end());
    const digit_type lim = m_10n(k_base);
    for(auto iter(m_number.begin()); iter != m_number.end(); ++iter)
        if(*iter < k_0bit || *iter >= lim)  *iter = k_0bit;
}

INT_TEMPL_
INT_INST_& INT_INST_::divide(const INT_INST_& rhs, bool get_modulus){
    if(*this == rhs) return (*this = 1);
    else if(rhs == INT_INST_(0) || this->magnitude() < rhs.magnitude())
        return (*this = INT_INST_(0));
    else if(rhs == INT_INST_(1)) return *this;

    INT_INST_
        quotient(0),
        remainder(this->magnitude()),
        tens(rhs.magnitude())
    ;
    size_type t_counter(remainder.m_number.size() - tens.m_number.size());

    tens.m_number.insert(0, t_counter, k_0bit);

    while(tens >= rhs.magnitude()){
        INT_INST_ addend("1" + str_type(t_counter, k_0bit));
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

INT_TEMPL_
INT_INST_& INT_INST_::bitwise_operation(
    INT_INST_ s,
    const std::function<bool(bool, bool)>& condition
){
    BitSet fbits(1, this->sign() < 0), sbits(1, s.sign() < 0);

    INT_INST_ twos(1);
    while(twos < *this)
        twos *= 2;
    for(twos /= 2; twos > INT_INST_(0); twos /= 2){
        if(*this >= twos)
            *this -= twos, fbits.push_back(true);
        else fbits.push_back(false);
    }

    twos = 1;
    while(twos < s)
        twos *= 2;
    for(twos /= 2; twos > INT_INST_(0); twos /= 2){
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
        fbits[i] = condition(fbits[i], sbits[i]);

    while(bit_num-- > 0)
        *this += fbits[bit_num]
            ? Precision::exponentiate(INT_INST_(2), INT_INST_(bit_num))
            : 0;
    if(fbits.back())
        this->sign(-1);

    return *this;
}

INT_TEMPL_
INT_INST_ operator+(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs += rhs;}

INT_TEMPL_
INT_INST_ operator-(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs -= rhs;}

INT_TEMPL_
INT_INST_ operator*(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs *= rhs;}

INT_TEMPL_
INT_INST_ operator/(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs /= rhs;}

INT_TEMPL_
INT_INST_ operator%(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs %= rhs;}

INT_TEMPL_
INT_INST_ operator&(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs &= rhs;}

INT_TEMPL_
INT_INST_ operator|(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs |= rhs;}

INT_TEMPL_
INT_INST_ operator^(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs ^= rhs;}

INT_TEMPL_
INT_INST_ operator>>(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs >>= rhs;}

INT_TEMPL_
INT_INST_ operator<<(INT_INST_ lhs, const INT_INST_& rhs)
    {return lhs <<= rhs;}

INT_TEMPL_
bool operator==(const INT_INST_& lhs, const INT_INST_& rhs)
    {return lhs.compare(rhs) == 0;}

INT_TEMPL_
bool operator!=(const INT_INST_& lhs, const INT_INST_& rhs)
    {return lhs.compare(rhs) != 0;}

INT_TEMPL_
bool operator>=(const INT_INST_& lhs, const INT_INST_& rhs)
    {return lhs.compare(rhs) >= 0;}

INT_TEMPL_
bool operator<=(const INT_INST_& lhs, const INT_INST_& rhs)
    {return lhs.compare(rhs) <= 0;}

INT_TEMPL_
bool operator>(const INT_INST_& lhs, const INT_INST_& rhs)
    {return lhs.compare(rhs) > 0;}

INT_TEMPL_
bool operator<(const INT_INST_& lhs, const INT_INST_& rhs)
    {return lhs.compare(rhs) < 0;}

INT_TEMPL_
bool operator!(const INT_INST_& lhs)
    {return lhs == INT_INST_(0);}

INT_TEMPL_
void swap(INT_INST_& a, INT_INST_& b)
    {a.swap(b);}