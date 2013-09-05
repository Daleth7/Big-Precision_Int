#include "Precision_Int.h"

#include <sstream>

Precision::Int operator"" _Precision_Int(char const *const raw, size_t)
    {return Precision::Int(Precision::Int::Str(raw));}
Precision::Int operator"" _Precision_Int_E(char const *const raw, size_t)
{
    using Str = Precision::Int::Str;
    const Str convert(raw);
    size_t e_pos(convert.find('E'));
    if(e_pos == Str::npos) e_pos = convert.find('e');
    if(e_pos == Str::npos)
        return Precision::Int(Str(raw));
        //Negative exponent
    if(convert[e_pos+1] == '-') return 0;

    Str base(convert.substr(0, e_pos));
    size_t exp(0);
    std::stringstream catalyst(convert.substr(e_pos+1));
    catalyst >> exp;
    size_t point(base.find('.'));
    if(point == Str::npos || point == base.size()-1){
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