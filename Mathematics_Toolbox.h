#include "Mathematics_Toolbox.h"

#include <sstream>
#include <iomanip>

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
        longI __carry(0);
        auto biter(big.__number.begin());
        auto siter(small.__number.begin());
        for(; siter != small.__number.end(); ++biter, ++siter){
        //Actual "addition"
            longI catalyst =
                (*biter)*big.__sign
                + (*siter)*small.__sign
                + __carry
            ;
        //"Borrow" a number if needed
            if(
                catalyst < 0 &&
                biter+1 != big.__number.end() &&
                __number.back() != 0
            ){
                catalyst = __limit - catalyst;
                --(*(biter+1));
            }else if(
                (*biter)*big.__sign < (*siter)*small.__sign &&
                biter+1 == big.__number.end()
            ){
                big.__sign = -1;
                catalyst *= -1;
            }
        //If we reach the end of small.__number but not big.__number
            if(
                siter+1 == small.__number.end() &&
                biter+1 != big.__number.end()
            ){
                size_t dhold(std::distance(big.__number.begin(), biter));
                small.__number.push_back(0);
                siter = small.__number.begin();
                    advance(siter, small.__number.size()-1);
                biter = big.__number.begin();
                    advance(biter, dhold);
            }
        //"Carry over" a number if needed
            if(catalyst >= __limit || catalyst <= -__limit)
                __carry = catalyst/__limit;
            else __carry = 0;
        //Replace old number with sum without
        //   carry included
            *biter = catalyst-__carry*__limit;
        }
        return (*this = big);
    }
    Precision_Int& Precision_Int::operator-=(const Precision_Int& rhs)
        {return (*this += (-rhs));}
    Precision_Int& Precision_Int::operator*=(const Precision_Int& rhs)
    {
        if(rhs == -1){
            __sign *= -1;
            return *this;
        }else if(rhs == 1) return *this;
        longI __carry(0);
        short signhold = __sign*rhs.__sign;
        std::vector<Precision_Int> addends;
        {
            auto iter = rhs.__number.begin();
            size_t setnum(0);
            for(; iter != rhs.__number.end(); ++iter, ++setnum){
                Precision_Int AIcatalyst;
                AIcatalyst.__number.clear();
                for(auto titer = __number.begin();; ++titer){
                //Check if last of digit sets but there is still a carry
                    if(titer == __number.end() && __carry > 0){
                        AIcatalyst.__number.push_back(__carry);
                        __carry = 0;
                        break;
                    }else if(titer == __number.end()) break;
                //Actual "multiplication"
                    longI catalyst = (*titer)*(*iter)+__carry;
                    if(catalyst >= __limit){
                        __carry = catalyst/__limit;
                        catalyst -= __carry*__limit;
                    }else __carry = 0;
                    AIcatalyst.__number.push_back(catalyst);
                }
                addends.push_back(AIcatalyst);
                AIcatalyst.__number.clear();
            }
        }
        __number.clear();
        __number.push_back(0);
        size_t additionalsets(0);
        for(auto iter(addends.begin()); iter != addends.end(); ++iter)
        {
            if(iter->__number.back() == 0 && iter->__number.size() > 1)
                ++additionalsets;
            else (*this) += *iter;
        }
        for(; additionalsets > 0; --additionalsets)
            __number.insert(__number.begin(),0);
        __sign = signhold;
        return *this;
    }
/*    Precision_Int& Precision_Int::operator/=(const Precision_Int& rhs)
    {
        const auto start(__number.begin());
        const size_t
            num_of_sets(__number.size()),
            dig_count
        ;
        using std::distance;
        for(
            auto liter(start);
            distance(liter, start) < num_of_sets;
            
        ){
        }
    }
	Precision_Int& Precision_Int::operator%=(const Precision_Int&);
*/  Precision_Int& Precision_Int::operator--()
        {return (*this += -1);}
    Precision_Int Precision_Int::operator--(int)
        {return (*this += -1)+1;}
    Precision_Int& Precision_Int::operator++()
        {return (*this += 1);}
    Precision_Int Precision_Int::operator++(int)
        {return (*this += 1)-1;}
            
	Precision_Int operator+
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) += s);}
    Precision_Int operator-
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) -= s);}
    Precision_Int operator*
        (const Precision_Int& f, const Precision_Int& s)
    {return Precision_Int(f) *= s;}
/*    Precision_Int operator/
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) /= s);}
	Precision_Int operator%
        (const Precision_Int& f, const Precision_Int& s)
    {return (Precision_Int(f) %= s);}
*/	Precision_Int operator-(const Precision_Int& f)
        {return f * -1;}
//Read-only functions
    short Precision_Int::sign()const
        {return __sign;}
    str Precision_Int::string()const{
        if(*this == 0)   return "0";
        str toreturn(__sign == 1 ? "+" : "-");
        for(
            auto iter(__number.rbegin());
            iter != __number.rend();
            ++iter
        ){
            if(*iter == 0){
                for(longI i(1); i < __digitlimit; ++i)
                    toreturn += "0";
                continue;
            }
            std::stringstream ss;
                ss << *iter;
            toreturn += ss.str();
        }
        return toreturn;
    }
    str Precision_Int::scientific_notation(size_t prec)const{
        if(*this == 0)   return "0";
        str toreturn(__sign == 1 ? "+" : "-");
        ld convert(__number.back());
        size_t dig_count((__number.size() - 1)*__digitlimit);
        while(convert > 10){
            convert /= 10;
            ++dig_count;
        }
        std::stringstream catalyst;
            catalyst << std::showpoint << std::setprecision(prec) << convert;
        toreturn += catalyst.str() + "E";
        catalyst.str("");
            catalyst << dig_count;
        toreturn += catalyst.str();
        return toreturn;
    }
    str Precision_Int::scientific_notation_with_spaces(size_t prec)const{
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
        __number({0}),
        __sign(newnumber < 0 ? -1 : 1)
    {
        newnumber *= __sign;
        longI limitconvert(__limit);
        if(newnumber >= limitconvert)
            __number.push_back(newnumber/limitconvert);
        __number.front() = newnumber - __number.back()*limitconvert;
    }
    Precision_Int::Precision_Int(diglist newnumber, short newsign):
        __number(newnumber),
        __sign(newsign == 1 ? 1 : -1)
    {}
    bool operator>=(const Precision_Int& f,const Precision_Int& s){
        if(
            f.__sign < s.__sign ||
            f.__number.size() < s.__number.size()
        ) return false;
        else if(
            f.__sign > s.__sign ||
            f.__number.size() > s.__number.size()
        ) return true;
        else if(f.__number.back() < s.__number.back()) return false;
        else if(f == s) return true;
        else return true;
    }
    bool operator<=(const Precision_Int& f,const Precision_Int& s)
        {return (f < s || f == s);}
    bool operator==(const Precision_Int& f,const Precision_Int& s){
        if(f.__sign != s.__sign) return false;
        else if(f.__number.size() != s.__number.size()) return false;
        else if(f.__number.back() != s.__number.back()) return false;
        else return true;
    }
    bool operator>(const Precision_Int& f,const Precision_Int& s)
        {return !(f <= s);}
    bool operator<(const Precision_Int& f,const Precision_Int& s)
        {return !(f >= s);}
    bool operator!=(const Precision_Int& f,const Precision_Int& s)
        {return !(f == s);}
    bool operator!(const Precision_Int& f)
        {return f == 0;}
    
    Precision_Int Pow(const Precision_Int& b, const Precision_Int& exp){
        Precision_Int toreturn(b);
        for(auto e(exp); e > 1; --e)
            toreturn *= toreturn;
        return toreturn;
    }
    
    Precision_Int operator"" _Precision_Int(char const *const raw){
        Precision_Int toreturn({0}, (raw[0] == '-') ? -1 : 0);
        size_t i(0);
        if(raw[0] == '-' || raw[0] == '+') ++i;
        for(; i < sizeof(raw)/sizeof(char); ++i)
            toreturn += (raw[i]-'0')*pow(10, i);
        return toreturn;
    }
    Precision_Int operator"" _Precision_Int_E(char const *const raw){
        std::string convert(raw);
        size_t pos(convert.find('E'));
        if(pos == str::npos) pos = convert.find('e');
        if(pos == str::npos) pos  = convert.size();
        Precision_Int toreturn({0}, (raw[0] == '-') ? -1 : 0);
        size_t i(0);
        if(raw[0] == '-' || raw[0] == '+') ++i;
        for(; i < pos; ++i) toreturn += convert[i] - '0';
        if(pos == convert.size()) return toreturn;
//Temporarily use this method until mingw supports stoul or atoul
        std::stringstream ss(convert.substr(pos+1));
        size_t exp(0); ss >> exp;
        toreturn *= pow(10, exp);
        return toreturn;
    }
}
namespace MTool{
/*********************************************************************
                           Precision_Int_String
*********************************************************************/
//Overloaded operators
    Precision_Int_String& Precision_Int_String::operator+=(const Precision_Int_String& rhs)
    {
        Precision_Int_String
            big (rhs.__number.size() > __number.size() ? rhs : *this),
            small (rhs.__number.size() > __number.size() ? *this : rhs)
        ;
        //Ensure small number is always negative
        short sign_holder(big.__sign * small.__sign);
        if(big.__sign < 0) big.__sign *= -1, small.__sign *= -1;
        short __carry(0);
        for(size_t siter(0), biter(0); siter < small.__number.size(); ++biter, ++siter){
        //Actual "addition"
            short catalyst(
                (big.__number[biter]-'0')*big.__sign
                + (small.__number[siter]-'0')*small.__sign
                + __carry
            );
        //"Borrow" a number if needed
            if(
                catalyst < 0 &&
                biter+1 < big.__number.size() &&
                big.__number.back() != '0'
            ){
                catalyst += __limit;
                --big.__number[biter+1];
            }
        //"Carry over" a number if needed
            if(catalyst >= __limit || catalyst <= -__limit)
                __carry = catalyst/__limit;
            else __carry = 0;
        //If we reach the end of small.__number but not big.__number
            if(
                siter+1 == small.__number.size() &&
                biter < big.__number.size()
            ) small.__number.push_back('0');
        //If we reach the end of big.__number; switch to negative number
            if(
                catalyst < 0 &&
                biter+1 == big.__number.size()
            ){
                big.__sign = -1;
                catalyst *= -1;
            }
        //Replace old number with sum without carry included
            big.__number[biter] = catalyst-__carry*__limit + '0';
        }
        big.__sign *= sign_holder;
        return (*this = big);
    }
    Precision_Int_String& Precision_Int_String::operator-=(const Precision_Int_String& rhs)
        {return (*this += (-rhs));}
    Precision_Int_String& Precision_Int_String::operator*=(const Precision_Int_String& rhs)
    {
        if(rhs == -1){__sign *= -1; return *this;}
        else if(rhs == 1) return *this;
        short signhold(__sign*rhs.__sign);
        std::vector<Precision_Int_String> addends;
        {
            auto iter = rhs.__number.begin();
            size_t setnum(0);
            for(; iter != rhs.__number.end(); ++iter, ++setnum){
                Precision_Int_String AIcatalyst;
                AIcatalyst.__number.clear();
                short __carry(0);
                for(auto titer = __number.begin();; ++titer){
                //Check if last of digit sets but there is still a carry
                    if(titer == __number.end() && __carry > 0){
                        AIcatalyst.__number.push_back(__carry + '0');
                        break;
                    }else if(titer == __number.end()) break;
                //Actual "multiplication"
                    short catalyst((*titer-'0')*(*iter-'0')+__carry);
                    if(catalyst >= __limit){
                        __carry = catalyst/__limit;
                        catalyst -= __carry*__limit;
                    }else __carry = 0;
                    AIcatalyst.__number.push_back(catalyst+'0');
                }
                addends.push_back(AIcatalyst);
                AIcatalyst.__number.clear();
            }
        }
        __number.clear();
        __number.push_back('0');
        size_t additionalsets(0);
        for(auto iter(addends.begin()); iter != addends.end(); ++iter)
        {
            if(iter->__number.back() == '0' && iter->__number.size() > 1)
                ++additionalsets;
            else (*this) += *iter;
        }
        for(; additionalsets > 0; --additionalsets)
            __number.insert(__number.begin(),'0');
        __sign = signhold;
        return *this;
    }
/*    Precision_Int_String& Precision_Int_String::operator/=(const Precision_Int_String& rhs)
    {
        const auto start(__number.begin());
        const size_t
            num_of_sets(__number.size()),
            dig_count
        ;
        using std::distance;
        for(
            auto liter(start);
            distance(liter, start) < num_of_sets;
            
        ){
        }
    }
	Precision_Int_String& Precision_Int_String::operator%=(const Precision_Int_String&);
*/  Precision_Int_String& Precision_Int_String::operator--()
        {return (*this += -1);}
    Precision_Int_String Precision_Int_String::operator--(int)
        {return (*this += -1)+1;}
    Precision_Int_String& Precision_Int_String::operator++()
        {return (*this += 1);}
    Precision_Int_String Precision_Int_String::operator++(int)
        {return (*this += 1)-1;}
            
	Precision_Int_String operator+
        (const Precision_Int_String& f, const Precision_Int_String& s)
    {return (Precision_Int_String(f) += s);}
    Precision_Int_String operator-
        (const Precision_Int_String& f, const Precision_Int_String& s)
    {return (Precision_Int_String(f) -= s);}
    Precision_Int_String operator*
        (const Precision_Int_String& f, const Precision_Int_String& s)
    {return Precision_Int_String(f) *= s;}
/*    Precision_Int_String operator/
        (const Precision_Int_String& f, const Precision_Int_String& s)
    {return (Precision_Int_String(f) /= s);}
	Precision_Int_String operator%
        (const Precision_Int_String& f, const Precision_Int_String& s)
    {return (Precision_Int_String(f) %= s);}
*/	Precision_Int_String operator-(const Precision_Int_String& f)
        {return f * -1;}
//Read-only functions
    short Precision_Int_String::sign()const
        {return __sign;}
    str Precision_Int_String::string()const{
        if(*this == 0)   return "0";
        str toreturn(__sign == 1 ? "+" : "-");
        for(
            auto iter(__number.rbegin());
            iter != __number.rend();
            ++iter
        ) toreturn += *iter;
        return toreturn;
    }
    str Precision_Int_String::scientific_notation(size_t prec)const{
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
    str Precision_Int_String::scientific_notation_with_spaces(size_t prec)const{
        str toreturn(this->scientific_notation(prec));
        if(toreturn == "0") return toreturn;
        toreturn.insert(1, 1, ' ');
        toreturn.insert(toreturn.find('E'), 1, ' ');
        toreturn.insert(toreturn.find_last_of('E')+1, 1, ' ');
        return toreturn;
    }
    Precision_Int_String Precision_Int_String::Magnitude()const{
        //Seclude from multiplication operators
        Precision_Int_String toreturn(*this);
            toreturn.__sign = 1;
        return toreturn;
    }
    size_t Precision_Int_String::count_digits()const
        {return Precision_Int_String::string().size() - 1;}
    //Constructors and destructor
    Precision_Int_String::Precision_Int_String(longI newnumber):
        __number({}),
        __sign(newnumber < 0 ? -1 : 1)
    {
        newnumber *= __sign;
        while(newnumber > 0){
            __number.push_back(newnumber%__limit + '0');
            newnumber/=__limit;
        }
    }
    Precision_Int_String::Precision_Int_String(diglist_s newnumber, short newsign):
        __number(newnumber),
        __sign(newsign == 1 ? 1 : -1)
    {}
    bool operator>=(const Precision_Int_String& f,const Precision_Int_String& s){
        if(
            f.__sign < s.__sign ||
            f.__number.size() < s.__number.size()
        ) return false;
        else if(
            f.__sign > s.__sign ||
            f.__number.size() > s.__number.size()
        ) return true;
        else if(f.__number.back() < s.__number.back()) return false;
        else if(f == s) return true;
        else return true;
    }
    bool operator<=(const Precision_Int_String& f,const Precision_Int_String& s)
        {return (f < s || f == s);}
    bool operator==(const Precision_Int_String& f,const Precision_Int_String& s){
        if(f.__sign != s.__sign) return false;
        else if(f.__number.size() != s.__number.size()) return false;
        else if(f.__number.back() != s.__number.back()) return false;
        else return true;
    }
    bool operator>(const Precision_Int_String& f,const Precision_Int_String& s)
        {return !(f <= s);}
    bool operator<(const Precision_Int_String& f,const Precision_Int_String& s)
        {return !(f >= s);}
    bool operator!=(const Precision_Int_String& f,const Precision_Int_String& s)
        {return !(f == s);}
    bool operator!(const Precision_Int_String& f)
        {return f == 0;}
    
    Precision_Int_String Pow(const Precision_Int_String& b, const Precision_Int_String& exp){
        Precision_Int_String toreturn(b);
        for(auto e(exp); e > 1; --e)
            toreturn *= toreturn;
        return toreturn;
    }
    
    Precision_Int_String operator"" _Precision_Int_String(char const *const raw){
        Precision_Int_String toreturn({0}, (raw[0] == '-') ? -1 : 0);
        size_t i(0);
        if(raw[0] == '-' || raw[0] == '+') ++i;
        for(; i < sizeof(raw)/sizeof(char); ++i)
            toreturn += (raw[i]-'0')*pow(10, i);
        return toreturn;
    }
    Precision_Int_String operator"" _Precision_Int_String_E(char const *const raw){
        std::string convert(raw);
        size_t pos(convert.find('E'));
        if(pos == str::npos) pos = convert.find('e');
        if(pos == str::npos) pos  = convert.size();
        Precision_Int_String toreturn({0}, (raw[0] == '-') ? -1 : 0);
        size_t i(0);
        if(raw[0] == '-' || raw[0] == '+') ++i;
        for(; i < pos; ++i) toreturn += convert[i] - '0';
        if(pos == convert.size()) return toreturn;
//Temporarily use this method until mingw supports stoul or atoul
        std::stringstream ss(convert.substr(pos+1));
        size_t exp(0); ss >> exp;
        toreturn *= pow(10, exp);
        return toreturn;
    }
}
/*********************************************
             End MTool Namespace
*********************************************/
