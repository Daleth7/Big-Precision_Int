#ifndef __PRECISION_MATH_H
#define __PRECISION_MATH_H

#include "Precision_Float.h"
#include "Precision_Int.h"
#include "Precision_UFloat.h"
#include "Precision_UInt.h"

#include "Impl/Precision_Math_Shared_Functions.h"

namespace Precision{
//Int
    Int pow(const Int&, const Int&);
    Float powf(const Float&, const Float&);
    Int gcd(const Int&, const Int&);
    //Note: support no arcFOO functions because their domains suggest
    //   no need for Precision::Int
    bool Palindrome(const Int&);

    template <typename OutIter>
    void Erato_Sieve(unsigned long long int max, OutIter);
    
    Int Fibonacci(size_t* =nullptr, size_t=1);
    std::string Num_to_Words(Int);

//Warning: This Random class is slow at generating numbers
    class Random{
        public:
        //Read-only
            const Int& seed()const;
            Int min()const;  //will always return 0
            const Int& max()const;
            const Int& and1()const;
            const Int& and2()const;
            const Int& and3()const;
            const Int& and4()const;
            Int::lli order_of_entropy()const;
            size_t push1()const;
            size_t push2()const;
            size_t push3()const;
        //Retrieve and/or change state
            Int operator()();
            void discard();
        //Change settings
            void seed(const Int&);
            void max(const Int&);
            void and1(const Int&);
            void and2(const Int&);
            void and3(const Int&);
            void and4(const Int&);
            void order_of_entropy(Int::lli);
            void push1(size_t);
            void push2(size_t);
            void push3(size_t);
        //Constructor
            Random(
            //Seed
                const Int& INseed = 1,
                const Int& INmax = "1E100"_Precision_Int_E,
            //Order of Entropy
            //  --> Inf => More random but slower
            //  --> -Inf => Less random but faster
            //Resembles a K^(-e^2), i.e. a form of the Gaussian function
            //Currently set on a relatively fast setting with low randomness
                Int::lli INorder_of_entropy = -5,
            //These help randomize each bit
                const Int& INand1 = 0xBFFFFFF6, const Int& INand2 = 0xBFFAFFFF,
                const Int& INand3 = 0xDDFECB7F, const Int& INand4 = 0xDFFFFFEF,
            //These help refresh the number to avoid repetition
                size_t INpush1 = 8, size_t INpush2 = 11, size_t INpush3 = 18
            );
        private:
            Int m_seed, m_max;
            Int m_and1, m_and2, m_and3, m_and4;
            Int::lli m_order_of_entropy;
            size_t m_push1, m_push2, m_push3; 
    };

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