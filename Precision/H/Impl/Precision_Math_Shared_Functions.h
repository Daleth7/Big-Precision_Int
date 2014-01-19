#ifndef GENERALIZED_MATH_FUNCTION_TEMPLATES__H__
#define GENERALIZED_MATH_FUNCTION_TEMPLATES__H__

#include <utility>
#include "Shared_Constants.h"

namespace Precision{
    template <typename Number_Type>
    Number_Type sqrt(const Number_Type&, size_t = k_default_prec);

    template <typename Integer_Type>
    Integer_Type factorial_range(const Integer_Type&, const Integer_Type&);

    template <typename Integer_Type>
    Integer_Type factorial(const Integer_Type&);

    template <typename Floating_Type>
    Floating_Type nlog(Floating_Type, size_t = k_default_prec);

    template <typename Floating_Type>
    Floating_Type log(const Floating_Type&, size_t = k_default_prec);

    template <typename Floating_Type>
    Floating_Type log(
        const Floating_Type& x,
        const Floating_Type& base,
        size_t = k_default_prec
    );

    template <typename Floating_Type>
    Floating_Type pow_e(const Floating_Type&, size_t = k_default_prec);

    template <typename Number_Type, typename Integer_Type>
    Number_Type exponentiate(const Number_Type&, Integer_Type);

    template <typename Number_Type>
    Number_Type exponentiate(const Number_Type&, const Number_Type&, size_t);

    template <typename Number_Type>
    Number_Type gcd(const Number_Type&, const Number_Type&);

    template <typename Number_Type>
    Number_Type gcf(const Number_Type&, const Number_Type&);

//Arithmetic-Geometric mean
    template <typename Number_Type>
    Number_Type agm(const Number_Type&, const Number_Type&);
}

#include "Precision_Math_Shared_Functions.inl"

#endif