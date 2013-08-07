#include "Precision_Int.h"
#include "Constants.h"

#include <sstream>
#include <utility>

/*********************************************************************
                           Precision_Int
*********************************************************************/
namespace MTool{
//Overloaded operators
    Precision_Int& Precision_Int::operator+=(const Precision_Int& rhs)
    {
        if(rhs == 0) return *this;
        if(*this == 0) return (*this = rhs);
        diglist_s sum;
        Precision_Int big(*this), small(rhs);
        if(big.Magnitude() < small.Magnitude()) std::swap(big, small);
        while(small.__number.size() < big.__number.size())
            small.__number += '0';

        short carry(0);
        this->__sign = big.__sign;
        if(big.__sign == -1) big.__sign = 1, small.__sign *= -1;
        for(size_t i(0); i < small.__number.size(); ++i){
            short catalyst(
                (big.__number[i]-'0')*big.__sign
                + (small.__number[i]-'0')*small.__sign
                + carry
            );
        //Carry a number
            if(catalyst >= __limit) catalyst %= __limit, carry=1;
            else if(catalyst <= -__limit) catalyst += __limit, carry=-1;
            else carry = 0;
        //Borrow a number
            if(catalyst < 0 && i+1 < big.__number.size())
                --big.__number[i+1], catalyst += __limit;

            sum += catalyst+'0';
            if(carry > 0 && i+1 == big.__number.size())
                sum += carry + '0';
        }
        while(sum.back() == '0') sum.pop_back();
        this->__number = sum;
        return *this;
    }
    Precision_Int& Precision_Int::operator-=(const Precision_Int& rhs)
    {
        if(*this == rhs) return (*this = 0);
        return (*this += (-rhs));
    }

    Precision_Int& Precision_Int::operator*=(const Precision_Int& rhs)
    {
        if(rhs == 0) return *this = 0;
        else if(*this == 0 || rhs == 1) return *this;
        else if(*this == 1) return *this = rhs;
        else if(rhs == -1) return __sign *= -1, *this;
        else if(*this == -1){
            *this = rhs;
            __sign *= -1;
            return *this;
        }
        short sign_hold(__sign * rhs.__sign);
        Precision_Int big(*this), small(rhs);
        if(big.Magnitude() < small.Magnitude()) std::swap(big, small);
        size_t z_count(0);
        while(big.__number[0] == '0')
            big.__number.erase(0, 1), ++z_count;
        while(small.__number[0] == '0')
            small.__number.erase(0, 1), ++z_count;
        std::vector<Precision_Int> addends;
    //Cut down on runtime by reducing number of iterations
        for(size_t i(0); i < small.__number.size(); ++i){
            Precision_Int addend(0);
            short operand(small.__number[i]-'0');
            while(operand-- > 0) addend += big;
            addend.__number.insert(0, i, '0');
            addends.push_back(addend);
        }
        *this = 0;
        for(const auto& addend : addends) *this += addend;
        while(z_count-- > 0) __number.insert(0, 1, '0');
        this->__sign = sign_hold;
        return *this;
    }
    Precision_Int& Precision_Int::operator/=(const Precision_Int& rhs)
    {
        if(*this == rhs) return (*this = 1);
        else if(rhs == 0 || this->Magnitude() < rhs.Magnitude())
            return (*this = 0);
        else if(rhs == 1) return *this;
        Precision_Int
            toreturn(0),
            t_abs(this->Magnitude()),
            tens(rhs.Magnitude()),
            t_counter(0)
        ;
    //Cut down on runtime by reducing number of iterations
        while(tens.__number.size() < t_abs.__number.size())
            tens.__number.insert(0, 1, '0'), ++t_counter;
        while(tens >= rhs){
            while(t_abs >= tens)
                toreturn += Pow(__limit, t_counter), t_abs -= tens;
            tens.__number.erase(0, 1), --t_counter;
        }
        toreturn.__sign = this->__sign * rhs.__sign;
        return (*this = toreturn);
    }
    Precision_Int& Precision_Int::operator%=(const Precision_Int& rhs)
    {
        if(rhs == *this || rhs == 0) return (*this = 0);
        else if(rhs.Magnitude() > this->Magnitude()) return *this;
        return *this -= (*this/rhs)*rhs;
    }
    Precision_Int& Precision_Int::operator--()
        {return (*this += -1);}
    Precision_Int Precision_Int::operator--(int)
        {return (*this += -1)+1;}
    Precision_Int& Precision_Int::operator++()
        {return (*this += 1);}
    Precision_Int Precision_Int::operator++(int)
        {return (*this += 1)-1;}
//Bitwise operators
    //Use vector<bool> for dynamic sized bitsets
    typedef std::vector<bool> BitSet;
    void bitwise_helper(
        Precision_Int& f, Precision_Int s,
        std::function<void(BitSet&, BitSet&)> operation
    ){
        BitSet fbits, sbits;
        Precision_Int twos(0);

        twos = Pow(2, Log(2, f));
        for(; twos > 0; twos /= 2){
            if(f >= twos)
                f -= twos, fbits.push_back(true);
            else fbits.push_back(false);
        }
        twos = Pow(2, Log(2, s));
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

        operation(fbits, sbits);
        while(bit_num-- > 0) f += fbits[bit_num]
            ? Pow(Precision_Int(2), bit_num) : 0;
    }
    Precision_Int& Precision_Int::operator&=(const Precision_Int& rhs)
    {
        bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
            for(size_t i(0); i < l.size(); ++i)
                l[i] = (l[i] == r[i] && l[i] == true) ? true : false;}
        );
        return *this;
    }
    Precision_Int& Precision_Int::operator|=(const Precision_Int& rhs)
    {
        bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
            for(size_t i(0); i < l.size(); ++i)
                l[i] = (l[i] == true || r[i] == true) ? true : false;}
        );
        return *this;
    }
    Precision_Int& Precision_Int::operator^=(const Precision_Int& rhs)
    {
        bitwise_helper(*this, rhs, [](BitSet& l, BitSet& r){
            for(size_t i(0); i < l.size(); ++i)
                l[i] = (l[i] != r[i]) ? true : false;}
        );
        return *this;
    }
    Precision_Int&
        Precision_Int::operator<<=(const Precision_Int& rhs)
    {return *this *= Pow(2, rhs);}
    Precision_Int&
        Precision_Int::operator>>=(const Precision_Int& rhs)
    {return *this /= Pow(2, rhs);}
	Precision_Int operator+
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) += s);}
    Precision_Int operator-
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) -= s);}
    Precision_Int operator*
        (const Precision_Int& f, const Precision_Int& s)
    {return Precision_Int(f) *= s;}
    Precision_Int operator/
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) /= s);}
    Precision_Int operator%
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) %= s);}
    Precision_Int operator&
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) &= s);}
    Precision_Int operator|
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) |= s);}
    Precision_Int operator^
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) ^= s);}
    Precision_Int operator<<
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) <<= s);}
    Precision_Int operator>>
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) >>= s);}
    Precision_Int operator-(const Precision_Int& f)
        {return f * -1;}
//Read-only functions
    short Precision_Int::sign()const
        {return __sign;}
    str Precision_Int::string()const{
        if(*this == 0)   return "0";
        str toreturn(__sign == 1 ? "+" : "-");
        for(auto iter(__number.size()); iter > 0; --iter)
            toreturn += __number[iter-1];
        return toreturn;
    }
    str Precision_Int::scientific_notation(size_t prec)const{
        if(*this == 0)   return "0";
        str toreturn(__sign == 1 ? "+" : "-");
        toreturn += __number.back(); toreturn += ".";
        for(size_t i(2); i <= prec && i < __number.size(); ++i)
            toreturn += __number[__number.size()-i];
        while(toreturn.size() < 5) toreturn += '0';
        toreturn += 'E';
        std::stringstream ss;
            ss << __number.size() - 1;
        toreturn += ss.str();
        return toreturn;
    }
    str Precision_Int::scientific_notation_with_spaces(size_t prec)
    const{
        str toreturn(this->scientific_notation(prec));
        if(toreturn == "0") return toreturn;
        toreturn.insert(1, 1, ' ');
        toreturn.insert(toreturn.find('E'), 1, ' ');
        toreturn.insert(toreturn.find_last_of('E')+1, 1, ' ');
        return toreturn;
    }
    Precision_Int Precision_Int::Magnitude()const{
        //Seclude from multiplication operators
        Precision_Int toreturn(*this);
            toreturn.__sign = 1;
        return toreturn;
    }
    size_t Precision_Int::count_digits()const
        {return Precision_Int::string().size();}
    short Precision_Int::compare(const Precision_Int& s)const{
        if(this == &s)                                  return 0;
        else if(__sign < s.__sign)                      return -1;
        else if(__sign > s.__sign)                      return 1;
        else if(__sign == -1 && __number.size() > s.__number.size())
                                                        return -1;
        else if(__sign == -1 && __number.size() < s.__number.size())
                                                        return 1;
        else if(__number.size() < s.__number.size())    return -1;
        else if(__number.size() > s.__number.size())    return 1;
        for(size_t i(__number.size()); i > 0; --i){
            if(__number[i-1] < s.__number[i-1])         return -1;
            else if(__number[i-1] > s.__number[i-1])    return 1;    
        }
                                                        return 0;
    }
//Constructors and destructor
    Precision_Int::Precision_Int(longI newnumber):
        __number({}),
        __sign(newnumber < 0 ? -1 : 1)
    {
        newnumber *= __sign;
        while(newnumber > 0){
            __number.push_back(newnumber%__limit + '0');
            newnumber/=__limit;
        }
    }
    Precision_Int::Precision_Int(diglist_s newnumber, short newsign):
        __number(newnumber),
        __sign(newsign == 1 ? 1 : -1)
    {
        std::reverse(__number.begin(), __number.end());
        for(size_t i(0); i < __number.size(); ++i)
            if(!isdigit(__number[i])) __number[i] = '0';
    }

    bool operator>=(const Precision_Int& f,const Precision_Int& s)
        {return !(f < s);}
    bool operator<=(const Precision_Int& f,const Precision_Int& s)
        {return !(f > s);}
    bool operator==(const Precision_Int& f,const Precision_Int& s)
        {return (f.compare(s) == 0);}
    bool operator>(const Precision_Int& f,const Precision_Int& s)
        {return (f.compare(s) == 1);}
    bool operator<(const Precision_Int& f,const Precision_Int& s)
        {return (f.compare(s) == -1);}
    bool operator!=(const Precision_Int& f,const Precision_Int& s)
        {return !(f == s);}
    bool operator!(const Precision_Int& f)
        {return f == 0;}
//Other related functions
    short Compare(const Precision_Int& f, const Precision_Int& s)
        {return f.compare(s);}
    Precision_Int Pow(
        const Precision_Int& b, const Precision_Int& exp
    ){
        if(exp == 1) return b;
        else if(exp == 0) return 1;
        else if(exp < 0) return 0;
        Precision_Int toreturn(b);
        for(auto e(exp); e > 1; --e)
            toreturn *= b;
        return toreturn;
    }
    Precision_Int Factorial(const Precision_Int& start)
        {return (start > 1 ? start*Factorial(start-1) : 1);}
    Precision_Int Log(
        const Precision_Int& base,
        const Precision_Int& result
    ){
        if(base == result) return 1;
        else if(base > result) return 0;
        Precision_Int toreturn(1), testee(base);
        while(testee < result)
            ++toreturn, testee *= base;
        return toreturn;
    }
    //sin needs to make an internal copy anyway, so pass by value
    double Sin(Precision_Int angle){
        double buildup(0.0);
        while(angle.Magnitude() > 2*PI__){
            angle -= 2*PI__*angle.sign();
            buildup += 2*PI__ - static_cast<unsigned>(2*PI__);
            if(buildup > 1) --buildup, angle -= angle.sign();
        }
        str copy(angle.string());
        copy.erase(0);
        std::stringstream ss(copy);
        lli topass(0);
        ss >> topass;
        return ::sin(topass*angle.sign());
    }
    double Cos(const Precision_Int& angle)
        {return Sin(angle + PI__/2 + 1);}
    double Tan(const Precision_Int& angle)
        {return Sin(angle)/Cos(angle);}
    double Csc(const Precision_Int& angle)
        {return pow(Sin(angle), -1);}
    double Sec(const Precision_Int& angle)
        {return pow(Cos(angle), -1);}
    double Cot(const Precision_Int& angle)
        {return pow(Tan(angle), -1);}
}
MTool::Precision_Int operator""
    _Precision_Int(char const *const raw, size_t)
{
    size_t i(0);
    if(raw[0] == '-' || raw[0] == '+') ++i;
    return MTool::Precision_Int(
        std::string(raw).substr(i), (raw[0] == '-') ? -1 : 1
    );
}
MTool::Precision_Int operator""
    _Precision_Int_E(char const *const raw, size_t)
{
    std::string convert(raw);
    size_t e_pos(convert.find('E'));
    if(e_pos == std::string::npos) e_pos = convert.find('e');
    if(e_pos == std::string::npos) e_pos = convert.size();
    
    if(convert[e_pos+1] == '-') return 0;

    MTool::str base(convert.substr(
        (raw[0] == '-' || raw[0] == '+' ? 1 : 0), e_pos
    ));
    size_t rhs_dig_gap(0);
    for(size_t i(0); i < base.size(); ++i){
        if(base[i] == '.'){
            base.erase(i, 1), rhs_dig_gap = e_pos - i-1;
            break;
        }
    }
    size_t exp(0);
    std::stringstream catalyst;
        catalyst << convert.substr(e_pos+1);
        catalyst >> exp;
    exp -= (rhs_dig_gap < exp ? rhs_dig_gap : exp);
    while(exp-- > 0) base += '0';
    return MTool::Precision_Int(base, raw[0] == '-' ? -1 : 1);
}
MTool::Precision_Int operator""
    _Precision_Int(unsigned long long cooked)
{return MTool::Precision_Int(cooked);}