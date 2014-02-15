#ifndef MATH_GEN_BASE_I_H_HH
#define MATH_GEN_BASE_I_H_HH

namespace Precision{
    template <typename Integer_Type>
    bool palindrome(const Integer_Type&);

    template <typename Integer_Type>
    Integer_Type fibonacci(size_t* =nullptr, size_t=1);

    template <typename Floating_Type>
    Floating_Type remainder(const Floating_Type&, const Floating_Type&);
}

#include "Precision_Math_General_Base.inl"

#include "Precision_Math_Trigonometry_General_Base.h"

#endif