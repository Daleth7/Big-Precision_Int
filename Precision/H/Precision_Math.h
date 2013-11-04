#ifndef __PRECISION_MATH_H
#define __PRECISION_MATH_H

#include "Precision_Float.h"
#include "Precision_Int.h"

namespace Precision{
//Int
    template <class _Precision_Type_>
        _Precision_Type_ Sqrt(const _Precision_Type_&, size_t = 10);
    Int Pow(const Int&, Int);
    Int Factorial(const Int&);
    Int Log(const Int&, const Int&);
    Int GCF(Int, Int);
    //Trigonomic functions -- default is radians
        //sin needs to make an internal copy anyway, so make non-const
    double Sin(Int);
    double Cos(const Int&);
    double Tan(const Int&);
    double Csc(const Int&);
    double Sec(const Int&);
    double Cot(const Int&);
    //Note: support no arcFOO functions because their domains suggest
    //   no need for Precision::Int
    bool Palindrome(const Int&);
    
    template <typename OutIter>
    void Erato_Sieve(unsigned long long int max, OutIter);
    
    Int Fibonacci(size_t* =nullptr, size_t=1);
    std::string Num_to_Words(Int);
    
    Int Rand(Int = -1, Int = Int("1" + Int::Str(19, '0')));
    
//Float
    Float fPow(const Float&, Float::Integer);
    Float fPow(const Float&, const Float&);
    Float ln(const Float&, size_t = 0);
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