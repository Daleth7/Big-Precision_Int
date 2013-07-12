#include "Mathematics_Toolbox.h"

#include <sstream>

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
                *(biter+1) != 0
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
    str Precision_Int::scientific_notation()const{
        if(*this == 0)   return "0";
        str toreturn(__sign == 1 ? "+" : "-");
        ld convert(__number.back());
        size_t dig_count((__number.size() - 1)*__digitlimit);
        while(convert > 10){
            convert /= 10;
            ++dig_count;
        }
        std::stringstream catalyst;
            catalyst << convert;
        toreturn += catalyst.str() + "E";
        catalyst.str("");
            catalyst << dig_count;
        toreturn += catalyst.str();
        return toreturn;
    }
    str Precision_Int::scientific_notation_with_spaces()const{
        str toreturn(this->scientific_notation());
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
        Precision_Int toreturn(0);
        for(size_t i(0); i < sizeof(raw)/sizeof(char); ++i)
            toreturn += (raw[i]-'0')*pow(10, i);
        return toreturn;
    }
    Precision_Int operator"" _Precision_Int_E(char const *const raw){
        std::string convert(raw);
        Precision_Int toreturn;
        size_t pos(convert.find('E'));
        if(pos == str::npos) pos = convert.find('e');
        if(pos == str::npos) pos  = convert.size();
        for(size_t i(0); i < pos; ++i) toreturn += convert[i] - '0';
        if(pos == convert.size()) return toreturn;
        toreturn*= pow(10, std::stoul(
            std::stringstream(convert.substr(pos)).str()
        ));
        return toreturn;
    }
}
/*********************************************
             End MTool Namespace
*********************************************/
