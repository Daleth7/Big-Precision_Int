#ifndef INTER_BASE_PRECISION_FUNCTIONS_H__
#define INTER_BASE_PRECISION_FUNCTIONS_H__

namespace Precision{
    template <typename Base_Return, typename Base_Param>
    Base_Return convert(const Base_Param&);
}

#include "Precision_InterBase_Functions.inl"

#endif