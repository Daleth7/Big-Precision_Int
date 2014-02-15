#ifndef PRECISION_MATH_TRIG_FUNCTIONS_GENERAL_BASE__H__
#define PRECISION_MATH_TRIG_FUNCTIONS_GENERAL_BASE__H__
#include "Shared_Constants.h"

//Trigonomic functions -- default is radians
namespace Precision{
    namespace General_Base{
        template <typename Number_Type>
        Number_Type sin(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type cos(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type tan(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type csc(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type sec(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type cot(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arcsin(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arccos(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arctan(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arccsc(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arcsec(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arccot(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );



        template <typename Number_Type>
        Number_Type sinh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type cosh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type tanh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type csch(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type sech(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type coth(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arcsinh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arccosh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arctanh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arccsch(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arcsech(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type arccoth(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );
    }
}

#include "Precision_Math_Trigonometry_General_Base.inl"

#endif