#ifndef __PRECISION_MATH_H
#define __PRECISION_MATH_H

#include "Precision_Default.h"
#include "Precision_Literal_Operators.h"

#include "Precision_Random.h"
#include "General_Base/Precision_Math_Shared_Functions.h"

namespace Precision{
//Int
    Int pow(const Int&, const Int&);
    Float powf(const Float&, const Float&);
    Int gcd(const Int&, const Int&);

    bool Palindrome(const Int&);

    template <typename OutIter>
    void Erato_Sieve(OutIter, size_t = 1000);

    Int Fibonacci(size_t* = nullptr, size_t = 1);
    std::string Num_to_Words(Int);

    Float Remainder(const Float&, const Float&);
/* Support only after studying mathematical gamma function for factorials
    Float Factorial(const Float&);
*/
//Trigonomic functions -- default is radians
    Float Sin(Float);
    Float Cos(const Float&);
    Float Tan(const Float&);
    Float Csc(const Float&);
    Float Sec(const Float&);
    Float Cot(const Float&);
    //Note: Consider support for arcFOO functions if
    //   implementation manually calculates values
}

#include "Precision_Math.inl"
    
#endif