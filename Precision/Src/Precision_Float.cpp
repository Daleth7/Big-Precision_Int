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