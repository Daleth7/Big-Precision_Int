#include "Precision_Literal_Operators.h"
#include "Precision_Math.h"

#include <sstream>

Precision::Int operator"" _Precision_Int(char const *const raw, size_t)
    {return Precision::Int(Precision::Int::str_type(raw));}
Precision::Int operator"" _Precision_Int_E(char const *const raw, size_t)
{
    using str_type = Precision::Int::str_type;
    const str_type convert(raw);
    Precision::Int::size_type e_pos(convert.find('E'));
    if(e_pos == str_type::npos) e_pos = convert.find('e');
    if(e_pos == str_type::npos)
        return Precision::Int(str_type(raw));
        //Negative exponent
    if(convert[e_pos+1] == '-') return 0;

    str_type base(convert.substr(0, e_pos));
    Precision::Int::size_type exp(0);
    std::stringstream catalyst(convert.substr(e_pos+1));
    catalyst >> exp;
    Precision::Int::size_type point(base.find('.'));
    if(point == str_type::npos || point == base.size()-1){
        if(point == convert.size()-1)
            base.erase(point, 1);
        base.insert(base.size(), exp, '0');
        return base;
    }

    base.erase(point, 1);
    while(exp > 0 && point < base.size())
        --exp, ++point;
    if(point < base.size())
        base.erase(point);
    if(exp > 0)
        base.insert(base.size(), exp, '0');
    
    return base;
}
Precision::Int operator"" _Precision_Int(unsigned long long cooked)
    {return Precision::Int(cooked);}


/*********************************************************************
                           Float
*********************************************************************/
Precision::Float operator"" _Precision_Float(
    char const *const raw,
    size_t
){return Precision::Float(raw);}
Precision::Float operator"" _Precision_Float_E(
    char const *const raw,
    size_t
){
    using str_type = Precision::Float::str_type;
    const str_type convert(raw);
    Precision::Float::size_type e_pos(convert.find('E'));
    if(e_pos == str_type::npos) e_pos = convert.find('e');
    if(e_pos == str_type::npos)
        return Precision::Float(str_type(raw));

    Precision::Float toreturn(convert.substr(0, e_pos));
    long long int exp(0);
    std::istringstream catalyst(convert.substr(e_pos+1));
    catalyst >> exp;
    toreturn.shift(exp);

    return toreturn;

}
Precision::Float operator"" _Precision_Float(long double cooked)
    {return Precision::Float(cooked);}
Precision::Float operator"" _Precision_Float(unsigned long long cooked)
    {return Precision::Float(cooked);}


Precision::UInt operator"" _Precision_UInt(
    char const *const raw,
    size_t
){return Precision::UInt::str_type(raw);}

Precision::UInt operator"" _Precision_UInt_E(
    char const *const raw,
    size_t
){return operator"" _Precision_Int_E(raw, 0);}

Precision::UInt operator"" _Precision_UInt
    (unsigned long long cooked)
{return cooked;}


Precision::UFloat operator"" _Precision_UFloat(
    char const *const raw,
    size_t
){return Precision::UFloat::str_type(raw);}

Precision::UFloat operator"" _Precision_UFloat_E(
    char const *const raw,
    size_t
){return Precision::UFloat(operator"" _Precision_Float_E(raw, 0));}

Precision::UFloat operator"" _Precision_UFloat
    (unsigned long long cooked)
{return Precision::UFloat(cooked);}

Precision::UFloat operator"" _Precision_UFloat
    (long double cooked)
{return Precision::UFloat(cooked);}