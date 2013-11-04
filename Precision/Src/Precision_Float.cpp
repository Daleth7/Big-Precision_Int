#include "Precision_Float.h"

#include "Precision_Math.h"

#include <string>
#include <sstream>
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
    using Str = Precision::Float::Str;
    const Str convert(raw);
    Precision::Float::Size_Type e_pos(convert.find('E'));
    if(e_pos == Str::npos) e_pos = convert.find('e');
    if(e_pos == Str::npos)
        return Precision::Float(Str(raw));

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