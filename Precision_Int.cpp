#include "Precision_Int.h"

#include "Constants.h"

#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace MTool{
/*********************************************************************
                           Precision_Int
*********************************************************************/
//Overloaded operators
    Precision_Int& Precision_Int::operator+=(const Precision_Int& rhs)
    {
        Precision_Int
            big (rhs.Magnitude() > this->Magnitude() ? rhs : *this),
            small (rhs.Magnitude() > this->Magnitude() ? *this : rhs)
        ;
        short sign_holder(big.__sign);
        //Ensure small number is always the negative one
        if(big.__sign < 0) big.__sign *= -1, small.__sign *= -1;
        short __carry(0);
        for(size_t iter(0); iter < small.__number.size(); ++iter){
        //Actual "addition"
            short catalyst(
                (big.__number[iter]-'0') + __carry
                + (small.__number[iter]-'0')*small.__sign
            );
        //"Borrow" a number if needed
            if(
                catalyst < 0 &&
                iter+1 < big.__number.size() &&
                big.__number.back() != '0'
            ){
                catalyst += __limit;
                --big.__number[iter+1];
            }
        //"Carry over" a number if needed
            if(catalyst >= __limit || catalyst <= -__limit)
                __carry = catalyst/__limit;
            else __carry = 0;
        //If we reach the end of small.__number but not big.__number
            if(
                iter+1 == small.__number.size() &&
                iter < big.__number.size()
            ) small.__number.push_back('0');
        //If we reach the end of big.__number;
        //   switch to negative number
            if(
                catalyst < 0 &&
                iter+1 == big.__number.size()
            ){
                big.__sign = -1;
                catalyst *= -1;
            }
        //Replace old number with sum without carry included
            big.__number[iter] = catalyst-__carry*__limit + '0';
        //If we reach the end of big.__number but there
        //   is still a carry
            if(iter+1 == big.__number.size()){
                big.__number += __carry + '0';
                break;
            }
        }
        //Because we are working with std::string, make sure there are
        //   no '0' characters as in "0099".
        while(big.__number.back() == '0') big.__number.pop_back();
        big.__sign = sign_holder;
        return (*this = big);
    }
    Precision_Int& Precision_Int::operator-=(const Precision_Int& rhs)
        {return (*this += (-rhs));}

    Precision_Int& Precision_Int::operator*=(const Precision_Int& rhs)
    {
        if(rhs == 0 || *this == 0) return *this = 0;
        else if(rhs == 1) return *this;
        else if(*this == rhs) return *this = rhs;

        short sign_hold(__sign * rhs.__sign);
        Precision_Int
            big = (this->Magnitude() > rhs.Magnitude())
                ? this->Magnitude() : rhs.Magnitude(),
            small = (this->Magnitude() > rhs.Magnitude())
                ? rhs.Magnitude() : this->Magnitude()
        ;
        std::vector<Precision_Int> addends;
        for(size_t i(0); i < small.__number.size(); ++i){
            Precision_Int addend(0);
            short operand(small.__number[i]-'0');
            while(operand-- > 0) addend += big;
            addend.__number.insert(0, i, '0');
            addends.push_back(addend);
        }
        *this = 0;
        for(const auto addend : addends) *this += addend;
        this->__sign = sign_hold;
        return *this;
    }
    Precision_Int& Precision_Int::operator/=(const Precision_Int& rhs)
    {
        if(*this == rhs) return (*this = 1);
        else if(rhs == 0 || this->Magnitude() < rhs.Magnitude())
            return (*this = 0);
        else if(rhs == 1) return *this;
        
        Precision_Int toreturn(0);
        while(*this >= rhs) *this -= rhs, ++toreturn;
        
        toreturn.__sign = this->__sign * rhs.__sign;
        return (*this = toreturn);
    }
    Precision_Int& Precision_Int::operator%=(const Precision_Int& rhs)
    {
        if(rhs == *this || rhs == 0) return (*this = 0);
        else if(rhs > *this) return *this;
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
/*    Precision_Int& operator&=(const Precision_Int& rhs){
        const bool longer(__number.size() < rhs.__number.size());
        size_t bit_num(
            (longer ? __number.size() ? rhs.__number.siz)/2
        );
        if(longer ? (rhs.__number.size()%2) : (__number.size()%2))
            ++bit_num;
        std::bitset<bit_num> fbits, sbits;
        for(; bit_num > 0; --bit_num)
    }
    Precision_Int& Precision_Int::operator|=(const Precision_Int& rhs)
    Precision_Int& Precision_Int::operator^=(const Precision_Int& rhs)
    Precision_Int& Precision_Int::operator<<=(const Precision_Int& rhs
        ){return *this *= 2;}
    Precision_Int& Precision_Int::operator>>=(const Precision_Int& rhs
        ){return *this/2;}
*/
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
        for(size_t i(2); i <= prec; ++i)
            toreturn += __number[__number.size()-i];
        while(toreturn.size() < 5) toreturn += '0';
        toreturn += 'E';
        std::stringstream ss;
            ss << __number.size() - 1;
        toreturn += ss.str();
        return toreturn;
    }
    str Precision_Int::scientific_notation_with_spaces(size_t prec
    )const{
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
        {return Precision_Int::string().size() - 1;}
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

    bool operator>=(const Precision_Int& f,const Precision_Int& s){
        if(f.__sign < s.__sign) return false;
        else if(f.__sign > s.__sign ) return true;
        else if(
            f.__sign == -1 &&
            f.__number.size() > s.__number.size()
        ) return false;
        else if(
            f.__sign == -1 &&
            f.__number.size() < s.__number.size()
        ) return true;
        else if(f.__number.size() < s.__number.size()) return false;
        else if(f.__number.size() > s.__number.size()) return true;
        else{
            for(size_t i(f.__number.size()-1); i > 0; --i)
                if(f.__number[i] > s.__number[i-1]) return true;
            return (f == s);
        }
    }
    bool operator<=(const Precision_Int& f,const Precision_Int& s)
        {return (f < s || f == s);}
    bool operator==(const Precision_Int& f,const Precision_Int& s)
        {return f.__sign==s.__sign && f.__number==s.__number;}
    
    bool operator>(const Precision_Int& f,const Precision_Int& s)
        {return !(f <= s);}
    bool operator<(const Precision_Int& f,const Precision_Int& s)
        {return !(f >= s);}
    bool operator!=(const Precision_Int& f,const Precision_Int& s)
        {return !(f == s);}
    bool operator!(const Precision_Int& f)
        {return f == 0;}
    
    Precision_Int Pow(const Precision_Int& b, const Precision_Int& exp
    ){
        Precision_Int toreturn(b);
        for(auto e(exp); e > 1; --e)
            toreturn *= toreturn;
        return toreturn;
    }
    Precision_Int Factorial(const Precision_Int& start)
        {return (start > 1 ? start*Factorial(start-1) : 1);}
    //sin needs to make an internal copy anyway, so make non-const
    double sin(Precision_Int angle){
        double buildup(0.0);
        while(angle.Magnitude() > 2*PI__){
            angle -= 2*PI__*angle.__sign;
            buildup += 2*PI__ - static_cast<unsigned>(2*PI__);
            if(buildup > 1){
                buildup -= 1;
                angle -= angle.__sign;
            }
        }
        std::stringstream ss(angle.__number);
        lli topass(0);
        ss >> topass;
        return sin(topass*angle.__sign);
    }
    double cos(const Precision_Int& angle)
        {return sin(angle + PI__/2 + 1);}
    double tan(const Precision_Int& angle)
        {return sin(angle)/cos(angle);}
    double csc(const Precision_Int& angle)
        {return pow(sin(angle), -1);}
    double sec(const Precision_Int& angle)
        {return pow(cos(angle), -1);}
    double cotan(const Precision_Int& angle)
        {return pow(tan(angle), -1);}
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
    size_t pos(convert.find('E'));
    if(pos == std::string::npos) pos = convert.find('e');
    if(pos == std::string::npos) pos = convert.size();
    size_t exp(0);
    MTool::str part(convert.substr(
        raw[0] == '-' || raw[0] == '+' ? 1 : 0,
        pos
    ));
    for(size_t i(0); i < part.size(); ++i)
        if(part[i] == '.') part.erase(i),
            exp += part.substr(i-1).size();
    MTool::Precision_Int toreturn(part, (raw[0] == '-') ? -1 : 1);
    if(pos == convert.size()) return toreturn;
//Temporarily use this method until mingw supports
//   stoul or atoul
    std::stringstream ss(convert.substr(pos+1));
    ss >> pos;
    exp += pos;
    toreturn *= pow(10, exp);
    return toreturn;
}
MTool::Precision_Int operator""
    _Precision_Int(unsigned long long cooked)
{return MTool::Precision_Int(cooked);}
/*********************************************
             End MTool Namespace
*********************************************/
