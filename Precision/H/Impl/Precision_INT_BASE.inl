#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>

#define _INT0_(x) INT_TEMPLATE_(x)

//A couple of internal helpers
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ IPow(const INT_TEMPLATE_&, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ ILog(const INT_TEMPLATE_&, const INT_TEMPLATE_&);


//Overloaded operators
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator+=(const INT_TEMPLATE_& rhs){
    if(rhs == _INT0_(0))    return *this;
    if(*this == _INT0_(0))  return (*this = rhs);
    diglist sum;
    INT_TEMPLATE_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude()) std::swap(big, small);
    while(small.m_number.size() < big.m_number.size())
        small.m_number.push_back(k_0bit);

    digit10 carry(0);
    this->m_sign = big.m_sign;
    if(big.m_sign == -1) big.m_sign = 1, small.m_sign *= -1;

    auto biter(big.m_number.begin());
    auto siter(small.m_number.begin());
    for(; siter != small.m_number.end(); ++biter, ++siter){
        digit10 catalyst(
            NtoDec(*biter)*big.m_sign
            + NtoDec(*siter)*small.m_sign
            + carry
        );
    //Carry a number
        if(catalyst >= k_limit)
            catalyst %= k_limit, carry=1;
        else if(catalyst <= -k_limit)
            catalyst += k_limit, carry=-1;
        else
            carry = 0;
    //Borrow a number
        auto bcopy(biter);
            ++bcopy;
        if(catalyst < 0 && bcopy != big.m_number.end())
            --(*bcopy), catalyst += k_limit;

        sum.push_back(DectoN(catalyst));
        if(carry > 0 && bcopy == big.m_number.end())
            sum.push_back(DectoN(carry));
    }

    while(sum.back() == k_0bit) sum.pop_back();
    this->m_number = sum;
    return *this;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator-=(const INT_TEMPLATE_& rhs){
    if(*this == rhs)    return (*this = 0);
    return (*this += (-rhs));
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator*=(const INT_TEMPLATE_& rhs){
    if(rhs == _INT0_(0))                            return *this = 0;
    else if(*this == _INT0_(0) || rhs == _INT0_(1)) return *this;
    else if(*this == _INT0_(1))                     return *this = rhs;
    else if(rhs == _INT0_(-1))                      return m_sign *= -1, *this;
    else if(*this == _INT0_(-1)){
        *this = rhs;
        m_sign *= -1;
        return *this;
    }
    Sign sign_hold(m_sign * rhs.m_sign);

    INT_TEMPLATE_ big(*this), small(rhs);
    if(big.magnitude() < small.magnitude())
        std::swap(big, small);
    Size_Type z_count(0);
    while(big.m_number.front() == k_0bit)
        big.m_number.erase(0, 1), ++z_count;
    while(small.m_number.front() == k_0bit)
        small.m_number.erase(0, 1), ++z_count;
    std::vector<INT_TEMPLATE_> addends;
//Cut down on runtime by reducing number of iterations
    auto iter(small.m_number.begin());
    for(
        Size_Type i(0);
        i < small.m_number.size();
        ++i, ++iter
    ){
        INT_TEMPLATE_ addend(0);
        digit10 operand(NtoDec(*iter));
        while(operand-- > 0)
            addend += big;
        addend.m_number.insert(0, i, k_0bit);
        addends.push_back(addend);
    }
    m_number = diglist(1, k_0bit);
    for(
        auto addend(addends.begin());
        addend != addends.end();
        ++addend
    ) *this += *addend;
    m_number.insert(0, z_count, k_0bit);

    this->m_sign = sign_hold;
    return *this;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator/=(const INT_TEMPLATE_& rhs){
    if(*this == rhs)            return (*this = 1);
    else if(rhs == _INT0_(0) || this->magnitude() < rhs.magnitude())
                                return (*this = 0);
    else if(rhs == _INT0_(1))   return *this;

    INT_TEMPLATE_
        toreturn(0),
        t_abs(this->magnitude()),
        tens(rhs.magnitude())
    ;
    Size_Type t_counter(t_abs.m_number.size() - tens.m_number.size());
//Cut down on runtime by reducing number of iterations
    tens.m_number.insert(0, t_counter, k_0bit);

    while(tens >= rhs.magnitude()){
        while(t_abs >= tens){
            INT_TEMPLATE_ addend("1" + Str(t_counter, k_0bit));
            toreturn += addend;
            t_abs -= tens;
        }
        tens.m_number.erase(0, 1), --t_counter;
    }
    toreturn.m_sign = this->m_sign * rhs.m_sign;
    return (*this = toreturn);
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator%=(const INT_TEMPLATE_& rhs){
    if(rhs == *this || rhs == _INT0_(0))            return (*this = 0);
    else if(rhs.magnitude() > this->magnitude())    return *this;
    return *this -= (*this/rhs)*rhs;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator--()
    {return (*this += -1);}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ INT_TEMPLATE_::operator--(int)
    {return (*this += -1)+1;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator++()
    {return (*this += 1);}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ INT_TEMPLATE_::operator++(int)
    {return (*this += 1)-1;}


//Bitwise operators
//Use vector<bool> for dynamic sized bitsets
typedef std::vector<bool> BitSet;
__INT__TEMPLATE__HEADER_
void bitwise_helper(
    INT_TEMPLATE_& f, INT_TEMPLATE_ s,
    std::function<void(BitSet&, BitSet&)> operation
){
    BitSet fbits(1, f.sign() < 0), sbits(1, s.sign() < 0);
    INT_TEMPLATE_ twos(0);

    twos = IPow(_INT0_(2), ILog(_INT0_(2), f));
    for(; twos > 0; twos /= 2){
        if(f >= twos)
            f -= twos, fbits.push_back(true);
        else fbits.push_back(false);
    }
    twos = IPow(_INT0_(2), ILog(_INT0_(2), s));
    for(; twos > 0; twos /= 2){
        if(s >= twos)
            s -= twos, sbits.push_back(true);
        else sbits.push_back(false);
    }

    std::reverse(fbits.begin(), fbits.end());
    std::reverse(sbits.begin(), sbits.end());

    typename INT_TEMPLATE_::Size_Type bit_num(fbits.size());
        if(bit_num < sbits.size()) bit_num = sbits.size();
    fbits.resize(bit_num, false);
    sbits.resize(bit_num, false);

    --bit_num;
    operation(fbits, sbits);
    f = f.magnitude();
    while(bit_num-- > 0) f += fbits[bit_num]
        ? IPow(_INT0_(2), _INT0_(bit_num)) : 0;
    if(fbits.back())
        f.sign(-1);
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator&=(const INT_TEMPLATE_& rhs){
    bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
        for(Size_Type i(0); i < l.size(); ++i)
            l[i] = (l[i] == r[i] && l[i] == true) ? true : false;}
    );
    return *this;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator|=(const INT_TEMPLATE_& rhs){
    bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
        for(Size_Type i(0); i < l.size(); ++i)
            l[i] = (l[i] == true || r[i] == true) ? true : false;}
    );
    return *this;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator^=(const INT_TEMPLATE_& rhs){
    bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
        for(Size_Type i(0); i < l.size(); ++i)
            l[i] = (l[i] != r[i]) ? true : false;}
    );
    return *this;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator<<=(const INT_TEMPLATE_& rhs)
    {return *this *= IPow(_INT0_(2), rhs);}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_& INT_TEMPLATE_::operator>>=(const INT_TEMPLATE_& rhs)
    {return *this /= IPow(_INT0_(2), rhs);}


//Read-only functions
__INT__TEMPLATE__HEADER_
typename INT_TEMPLATE_::Sign INT_TEMPLATE_::sign()const
    {return m_sign;}

__INT__TEMPLATE__HEADER_
typename INT_TEMPLATE_::Str INT_TEMPLATE_::str()const{
    if(*this == _INT0_(0))   return "+0";
    Str toreturn(m_sign == 1 ? "+" : "-");
    std::stringstream catalyst;
        catalyst << k_limit;
    const size_t cap(
        catalyst.str().size()
        - (catalyst.str().find_last_of('1') == 0 ? 1 : 0)
    );
    for(auto iter(m_number.rbegin()); iter != m_number.rend(); ++iter){
        std::stringstream ss("");
            ss << *iter;
        toreturn
            += (ss.str().size() < cap
                && iter != m_number.rbegin()
                ? Str(cap-ss.str().size(), '0')
                :  ""
            )
            + ss.str()
        ;
    }
    return toreturn;
}

__INT__TEMPLATE__HEADER_
typename INT_TEMPLATE_::Str INT_TEMPLATE_::sci_note(Size_Type prec)const{
    if(*this == _INT0_(0))
        return "+0";
    else if(m_number.size() < 2)
        return this->str() + "E1";

    Str toreturn(this->str());
    Size_Type exp(toreturn.size() - 2);
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

__INT__TEMPLATE__HEADER_
typename INT_TEMPLATE_::Str
    INT_TEMPLATE_::sci_note_w_spaces(Size_Type prec)
const{
    Str toreturn(this->sci_note(prec));
    if(toreturn == "0") return toreturn;
    toreturn.insert(1, 1, ' ');//Insert space after the sign
    toreturn.insert(toreturn.find('E'), 1, ' ');
    toreturn.insert(toreturn.find('E')+1, 1, ' ');
    return toreturn;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ INT_TEMPLATE_::magnitude()const{
    //Seclude from multiplication operators
    INT_TEMPLATE_ toreturn(*this);
        toreturn.m_sign = 1;
    return toreturn;
}

__INT__TEMPLATE__HEADER_
typename INT_TEMPLATE_::Size_Type INT_TEMPLATE_::count_digits()const
    {return m_number.size();}

__INT__TEMPLATE__HEADER_
short INT_TEMPLATE_::compare(const INT_TEMPLATE_& s)const{
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
        auto titer(m_number.rbegin());
        auto siter(s.m_number.rbegin());
        for(; titer != m_number.rend(); --titer, --siter){
            if(*titer > *siter)     return -1;
            else if(*titer < *siter)return 1;
        }
    }
    auto titer(m_number.rbegin());
    auto siter(s.m_number.rbegin());
    for(; titer != m_number.rend(); --titer, --siter){
        if(*titer < *siter)     return -1;
        else if(*titer > *siter)return 1;
    }
                                                    return 0;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ INT_TEMPLATE_::operator-()const{
    INT_TEMPLATE_ toreturn(*this);
    toreturn.m_sign *= -1;
    return toreturn;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ INT_TEMPLATE_::operator~()const{
    BitSet bits(1, m_sign < 0);
    INT_TEMPLATE_ twos(1), f(*this);

    while(twos < f)
        twos *= 2;
    INT_TEMPLATE_ twos_complement(twos);
    twos_complement.m_sign = m_sign * -1;
    twos /= 2;
    for(; twos > _INT0_(0); twos /= 2){
        if(f >= twos)
            f -= twos, bits.push_back(true);
        else bits.push_back(false);
    }

    std::reverse(bits.begin(), bits.end());

    f = f.magnitude();
    for(Size_Type i(0); i < bits.size()-1; ++i)
        f += bits[i] ? 0 : IPow(_INT0_(2), _INT0_(i));
    f += twos_complement;
    return f;
}

__INT__TEMPLATE__HEADER_
bool INT_TEMPLATE_::even()const
    {return !(this->odd());}

__INT__TEMPLATE__HEADER_
bool INT_TEMPLATE_::odd()const
    {return (m_number.front() - k_0bit) % 2;}


//Other modifiers
__INT__TEMPLATE__HEADER_
void INT_TEMPLATE_::shift(lli tens_exp){
    if(tens_exp == 0) return;
    else if(tens_exp > 0)
        m_number.insert(0, tens_exp, k_0bit);
    else if(tens_exp < 0 && -tens_exp < lli(m_number.size()))
        m_number.erase(0, -tens_exp);
    else *this = 0;
}

__INT__TEMPLATE__HEADER_
void INT_TEMPLATE_::sign(Sign newsign)
    {m_sign = (newsign == -1 ? -1 : 1);}

__INT__TEMPLATE__HEADER_
void INT_TEMPLATE_::negate()
    {m_sign *= -1;}


//Constructors and destructor
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_::INT_BASE_(lli newnumber)
    : m_number({})
    , m_sign(newnumber < 0 ? -1 : 1)
{
    newnumber *= m_sign;
    while(newnumber > 0){
        m_number.push_back(DectoN(newnumber%k_limit));
        newnumber/=k_limit;
    }
    if(m_number.size() == 0)
        m_number = diglist(1, k_0bit);
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_::INT_BASE_(diglist newnumber, Sign newsign)
    : m_number(newnumber)
    , m_sign(newsign)
{
    std::reverse(m_number.begin(), m_number.end());
    digit cap(DectoN(k_limit));
    for(
        auto iter(m_number.begin());
        iter != m_number.end();
        ++iter
    ){
        if(*iter <= k_0bit || *iter >= cap)
            *iter = k_0bit;
    }
    while(m_number.back() == k_0bit && m_number.size() > 1)
        m_number.pop_back();
}

#include <cmath>
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_::INT_BASE_(Str newnumber)
    : m_number(newnumber.size() > 0 ? 0 : 1, k_0bit)
    , m_sign(newnumber[0] == '-' ? -1 : 1)
{
    if(newnumber.size() > 0){
        if(newnumber[0] == '+' || newnumber[0] == '-')
            newnumber.erase(0, 1);
        std::stringstream ss;
            ss << k_limit;
        Str lim(ss.str());
        if(lim.find_last_of('1') == 0)
            lim.pop_back();
        while(newnumber.size() > lim.size()){
            ss.str(newnumber.substr(newnumber.size()-lim.size()));
            digit catalyst(k_0bit);
            ss >> catalyst;
            m_number.push_back(catalyst);
            newnumber.erase(newnumber.size()-lim.size());
        }
        ss.clear();
        if(newnumber.size() > 0){
            ss.str(newnumber);
            digit catalyst(k_0bit);
            ss >> catalyst;
            m_number.push_back(catalyst);
        }
        while(m_number.back() == k_0bit && m_number.size() > 1)
            m_number.pop_back();
    }
}


__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator+(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs += rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator-(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs -= rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator*(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs *= rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator/(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs /= rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator%(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs %= rhs;}


__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator&(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs &= rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator|(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs |= rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator^(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs ^= rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator>>(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs >>= rhs;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator<<(INT_TEMPLATE_ lhs, const INT_TEMPLATE_& rhs)
    {return lhs <<= rhs;}


__INT__TEMPLATE__HEADER_
bool operator==(const INT_TEMPLATE_& lhs, const INT_TEMPLATE_& rhs)
    {return lhs.compare(rhs) == 0;}

__INT__TEMPLATE__HEADER_
bool operator!=(const INT_TEMPLATE_& lhs, const INT_TEMPLATE_& rhs)
    {return lhs.compare(rhs) != 0;}

__INT__TEMPLATE__HEADER_
bool operator>=(const INT_TEMPLATE_& lhs, const INT_TEMPLATE_& rhs)
    {return lhs.compare(rhs) >= 0;}

__INT__TEMPLATE__HEADER_
bool operator<=(const INT_TEMPLATE_& lhs, const INT_TEMPLATE_& rhs)
    {return lhs.compare(rhs) <= 0;}

__INT__TEMPLATE__HEADER_
bool operator>(const INT_TEMPLATE_& lhs, const INT_TEMPLATE_& rhs)
    {return lhs.compare(rhs) > 0;}

__INT__TEMPLATE__HEADER_
bool operator<(const INT_TEMPLATE_& lhs, const INT_TEMPLATE_& rhs)
    {return lhs.compare(rhs) < 0;}

__INT__TEMPLATE__HEADER_
bool operator!(const INT_TEMPLATE_& lhs)
    {return lhs == 0;}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ IPow(
    const INT_TEMPLATE_& f,
    const INT_TEMPLATE_& s
){
    if(s == 0)          return 1;
    else if(s == 1)     return f;
    else if(s < 0)      return 0;

    INT_TEMPLATE_ toreturn(f);
        //Exponentiation by squaring
    if(s.even())
        toreturn = IPow( f * f, s/2 );
    else
        toreturn = f * IPow( f, s - 1 );

    return toreturn;
}

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ ILog(
    const INT_TEMPLATE_& base,
    const INT_TEMPLATE_& result
){
        if(base == result) return 1;
        else if(base > result) return 0;
        INT_TEMPLATE_ toreturn(1), testee(base);
        while(testee < result)
            ++toreturn, testee *= base;
        return toreturn;
}
