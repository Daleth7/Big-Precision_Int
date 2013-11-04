#include "Precision_Math.h"

#include "Precision_Int.h"
#include "Precision_Float.h"
#include "Constants.h"

#include <sstream>
#include <cmath>
#include <list>
#include <iterator>

namespace Precision{
//Int
    Int Pow(const Int& b, Int exp){
        if(exp == 1) return b;
        else if(exp == 0) return 1;
        else if(exp.sign() < 0) return 0;
        
        Int toreturn(b);
        exp = exp.magnitude();
        Int operand(b);
            //Exponentiation by squaring
        toreturn
            = (exp % 2 == 0)
            ? Pow( (operand * operand), (exp/2) )
            : operand * Pow( (operand * operand), ((exp - 1)/2) )
        ;
        
        return toreturn;
    }

    Int Factorial_Range(const Int& f, const Int& s){
        if(s == f)
            return s;
        else if(s < f)
            return 1;
        else if(f+1 == s)
            return f*s;
        else
            return
                Factorial_Range(f, (f+s)/2)
                * Factorial_Range((f+s)/2+1, s)
            ;
    }

    Int Factorial(const Int& start){
        return Factorial_Range(2, start);
/*
        Int toreturn(1), counter(start);
        while(counter > 1)
            toreturn *= counter--;
        return toreturn;
*/
    }

    Int Log(const Int& base, const Int& result){
        if(base == result) return 1;
        else if(base > result) return 0;
        Int toreturn(1), testee(base);
        while(testee < result)
            ++toreturn, testee *= base;
        return toreturn;
    }
    Int GCF(Int toreturn, Int quotient){
    //Euclid's Algorithm:
    //  http://en.wikipedia.org/wiki/
    //  Greatest_common_divisor
    //  #Using_Euclid.27s_algorithm
        while(true){
            if(quotient % toreturn == 0) break;
            Int hold(toreturn);
            toreturn = quotient % toreturn;
            quotient = hold;
        }
        return toreturn;
    }
    //sin needs to make an internal copy anyway, so pass by value
    double Sin(Int angle){
        double buildup(0.0);
        while(angle.magnitude() > 2*PI__){
            angle -= 2*PI__*angle.sign();
            buildup += 2*PI__ - static_cast<unsigned>(2*PI__);
            if(buildup > 1) --buildup, angle -= angle.sign();
        }
        Int::Str copy(angle.str());
        if(copy[0] == '+' || copy[0] == '-')
            copy.erase(0, 1);
        std::stringstream ss(copy);
        long long int topass(0);
        ss >> topass;
        return ::sin(topass*angle.sign());
    }
    double Cos(const Int& angle)
        {return Sin(angle + PI__/2 + 1);}
    double Tan(const Int& angle)
        {return Sin(angle)/Cos(angle);}
    double Csc(const Int& angle)
        {return pow(Sin(angle), -1);}
    double Sec(const Int& angle)
        {return pow(Cos(angle), -1);}
    double Cot(const Int& angle)
        {return pow(Tan(angle), -1);}
    bool Palindrome(const Int& testee){
        Int::Str test_string(testee.str());
        test_string.erase(0, 1);
        const size_t max_s(test_string.size());
        for(size_t i(0); i < max_s/2; ++i)
            if(test_string[i] != test_string[max_s - i - 1])
                return false;
        return true;
    }
    
    Int Rand(Int seed, Int max){
        static Int sseed(1), toreturn(sseed);
        if(seed.sign() >= 0){
            sseed = seed;
            toreturn = sseed * Rand();
        }
        else if(toreturn > max)
            toreturn = sseed;
        toreturn |= toreturn * 2;
        toreturn <<= 1;
        toreturn &= toreturn / 2;
        toreturn <<= 1;
        toreturn ^= toreturn * 2;
        toreturn >>= 1;
        if(sseed % 2 == 1)
            sseed -= 1;
        else sseed += 1;
        toreturn += sseed;
        sseed |= sseed / 2;
        sseed <<= 1;
        sseed &= sseed / 2;
        sseed >>= 1;
        sseed ^= sseed / 2;
        sseed >>= 1;
        if(sseed > max)
            sseed.shift(-static_cast<Int::lli>(3*sseed.count_digits()/4));
        return toreturn;
    }

    Int Fibonacci(size_t* term_holder, size_t term){
        static Int toreturn(1), hold1(1), hold2(0);
        static size_t curr_term(2);
        if(term > 1)
            toreturn = 1, hold1 = 1, hold2 = 0, --term;
        curr_term += term;
        for(; term > 0; --term)
            hold2 = toreturn, toreturn += hold1, hold1 = hold2;
        if(term_holder != nullptr) *term_holder = curr_term;
        return toreturn;
    }
}

#include <map>
const std::map<Precision::Int, std::string>
    NumberWordBank
{
    std::make_pair("0"_Precision_Int, "zero"),
    std::make_pair("1"_Precision_Int, "one"),
    std::make_pair("2"_Precision_Int, "two"),
    std::make_pair("3"_Precision_Int, "three"),
    std::make_pair("4"_Precision_Int, "four"),
    std::make_pair("5"_Precision_Int, "five"),
    std::make_pair("6"_Precision_Int, "six"),
    std::make_pair("7"_Precision_Int, "seven"),
    std::make_pair("8"_Precision_Int, "eight"),
    std::make_pair("9"_Precision_Int, "nine"),
    std::make_pair("10"_Precision_Int, "ten"),
    std::make_pair("11"_Precision_Int, "eleven"),
    std::make_pair("12"_Precision_Int, "twelve"),
    std::make_pair("13"_Precision_Int, "thirteen"),
    std::make_pair("14"_Precision_Int, "fourteen"),
    std::make_pair("15"_Precision_Int, "fifteen"),
    std::make_pair("16"_Precision_Int, "sixteen"),
    std::make_pair("17"_Precision_Int, "seventeen"),
    std::make_pair("18"_Precision_Int, "eighteen"),
    std::make_pair("19"_Precision_Int, "nineteen"),
    std::make_pair("20"_Precision_Int, "twenty"),
    std::make_pair("30"_Precision_Int, "thirty"),
    std::make_pair("40"_Precision_Int, "forty"),
    std::make_pair("50"_Precision_Int, "fifty"),
    std::make_pair("60"_Precision_Int, "sixty"),
    std::make_pair("70"_Precision_Int, "seventy"),
    std::make_pair("80"_Precision_Int, "eighty"),
    std::make_pair("90"_Precision_Int, "ninety"),
    std::make_pair("1e2"_Precision_Int_E, "hundred"),
    std::make_pair("1e3"_Precision_Int_E, "thousand"),
    std::make_pair("1e6"_Precision_Int_E, "million"),
    std::make_pair("1e9"_Precision_Int_E, "billion"),
    std::make_pair("1e12"_Precision_Int_E, "trillion"),
    std::make_pair("1e15"_Precision_Int_E, "quadrillion"),
    std::make_pair("1e18"_Precision_Int_E, "quintillion"),
    std::make_pair("1e21"_Precision_Int_E, "sextillion"),
    std::make_pair("1e24"_Precision_Int_E, "septillion"),
    std::make_pair("1e27"_Precision_Int_E, "octillion"),
    std::make_pair("1e30"_Precision_Int_E, "nonillion"),
    std::make_pair("1e33"_Precision_Int_E, "decillion"),
};
const std::string k_and("and ");
const unsigned k_ten(10), k_thousand(1e3);
namespace Precision{
    std::string Num_to_Words(Int toconvert){
        std::string toreturn(
            toconvert.sign() == -1
            ? "negative " : ""
        );

        toconvert = toconvert.magnitude();
        while(toconvert > 0){
            size_t i( toconvert.count_digits() );
        //key1 accesses words of order 10, like "thousand"
        //key2 accesses the single digits words, like "one"
            Int key1(Pow(k_ten, i-1)), key2(toconvert / key1);
            
        //Two digits
            if(i == 2){
                if(toconvert >= 2*k_ten)
                    toreturn
                        += NumberWordBank.at(key2 * k_ten)
                        + (toconvert%k_ten > 0 ? "-" : "")
                    ;
                else if(toconvert >= k_ten){
                    toreturn += NumberWordBank.at(toconvert);
                    return toreturn;
                }
        //Three digits
            }else if(i == 3){
                toreturn += NumberWordBank.at(key2) + ' ';
                toreturn += NumberWordBank.at(key1) + ' ';
        //Four or more digits
            }else if(i >= 4){
                key2 = toconvert;
                key1 = 1;
                while(key2.count_digits() > 3){
                    key1 *= k_thousand;
                    key2 /= k_thousand;
                }
                
                toreturn += Num_to_Words(key2) + ' ';
                toreturn += NumberWordBank.at(key1) + ' ';
        //One digit
            }else toreturn += NumberWordBank.at(key2);
        //Stop adding things once toconvert is 0
            if(key1*key2 == toconvert) break;
        //Inserting "and"
            if(
                (i == 3 && toconvert%100 > 0) ||
                (i >= 4 && toconvert%k_thousand < 100)
            ) toreturn += k_and;

            toconvert -= key1*key2;
        }
        while(toreturn.back() == ' ') toreturn.pop_back();

        return toreturn;
    }
//Float
    Float fPow(const Float& f, Float::Integer s)
        {return f ^ s;}
    Float fPow(const Float& f, const Float& s)
        {return f ^ s;}

    Float ln(const Float& res, size_t prec){
        const bool inverted(res.magnitude() > 1);
        Float
            toreturn(0),
            _x(inverted ? (1 / res) : res)
        ;
        for(size_t i(1); i < (prec ? prec : 100); ++i){
            toreturn
                += (i % 2 == 1 ? 1 : -1)
                * ( (_x - 1) ^ i )
                / i
            ;
        }
        if(inverted)
            toreturn.negate();
        return toreturn;
    }

    Float Remainder(const Float& f, const Float& s)
        {return f.remainder(s);}
/* Support only after studying mathematical gamma function for factorials
    Float Factorial(const Float&);
*/
//Trigonomic functions -- default is radians
    Float Sin(Float angle){
        while(angle.magnitude() > 2*PI__)
            angle /= 2*PI__;
        Float::Str copy(angle.str(15));
        std::stringstream ss(copy.substr(1));
        long long int topass(0);
        ss >> topass;
        return ::sin(topass*angle.sign());
    }
    Float Cos(const Float& angle)
        {return Sin(angle + PI__/2 + 1);}
    Float Tan(const Float& angle)
        {return Sin(angle)/Cos(angle);}
    Float Csc(const Float& angle)
        {return 1 / Sin(angle);}
    Float Sec(const Float& angle)
        {return 1 / Cos(angle);}
    Float Cot(const Float& angle)
        {return 1 / Tan(angle);}
    //Note: Consider support for arcFOO functions if
    //   implementation manually calculates values
}