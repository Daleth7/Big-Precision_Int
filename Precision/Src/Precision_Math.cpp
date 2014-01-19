#include "Precision_Math.h"

#include "Precision_Int.h"
#include "Precision_Float.h"
#include "Constants.h"

#include <sstream>
#include <cmath>
#include <list>
#include <iterator>
#include <utility>
#include <algorithm>

namespace Precision{
//Int
    Int pow(const Int& b, const Int& exp)
        {return exponentiate(b, exp);}
    Float powf(const Float& b, const Float& exp)
        {return exponentiate(b, exp, b.precision());}
    Int gcd(const Int& a, const Int& b)
        {return gcd<Int>(a, b);}
    bool Palindrome(const Int& testee){
        Int::str_type test_string(testee.str());
        test_string.erase(0, 1);
        const size_t max_s(test_string.size());
        for(size_t i(0); i < max_s/2; ++i)
            if(test_string[i] != test_string[max_s - i - 1])
                return false;
        return true;
    }

//Read-only
    const Int& Random::seed()const{return m_seed;}
    Int Random::min()const{return 0;}
    const Int& Random::max()const{return m_max;}
    const Int& Random::and1()const{return m_and1;}
    const Int& Random::and2()const{return m_and2;}
    const Int& Random::and3()const{return m_and3;}
    const Int& Random::and4()const{return m_and4;}
    Int::lli Random::order_of_entropy()const{return m_order_of_entropy;}
    size_t Random::push1()const{return m_push1;}
    size_t Random::push2()const{return m_push2;}
    size_t Random::push3()const{return m_push3;}
//Retrive and/or change state
    Int Random::operator()(){
    //Algorithm is a modified form of the SFMT as described in this paper:
    // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/sfmt.pdf
        Int::str_type image(m_seed.str());
        const size_t quad(image.size()/4);
        Int
            word_1(image.substr(0, quad)), word_2(image.substr(quad+1, quad)),
            word_3(image.substr(2*quad+1, quad)), word_4(image.substr(3*quad+1))
        ;
        m_seed = ((
            ( (m_seed << m_push1) ^ m_seed )        //wA
            ^ ( ((word_1 >> m_push2) & m_and1)
                ^ ((word_2 >> m_push2) & m_and2)
                ^ ((word_3 >> m_push2) & m_and3)
                ^ ((word_4 >> m_push2) & m_and4) )  //wB
            ^ (m_seed >> m_push1)                   //wC
            ^ (m_seed << m_push3)                   //wD
        ) >> ((quad*4)/3));
        image = m_seed.str().substr(1);
        std::reverse(image.begin(), image.end());
        m_seed = Int(image);
        if(m_seed >= m_max)
            m_seed %= m_max;
        m_seed.shift(m_order_of_entropy);
        return m_seed;
    }
    void Random::discard(){this->operator()();}
//Change settings
    void Random::seed(const Int& new_seed){
        if(new_seed.positive())
            m_seed = new_seed;
    }
    void Random::max(const Int& new_max){
        if(new_max.positive())
            m_seed = new_max;
    }
    void Random::and1(const Int& a1){m_and1 = a1;}
    void Random::and2(const Int& a2){m_and1 = a2;}
    void Random::and3(const Int& a3){m_and1 = a3;}
    void Random::and4(const Int& a4){m_and1 = a4;}
    void Random::order_of_entropy(Int::lli ooe){m_order_of_entropy = ooe;}
    void Random::push1(size_t p1){m_push1 = p1;}
    void Random::push2(size_t p2){m_push1 = p2;}
    void Random::push3(size_t p3){m_push1 = p3;}
//Constructor
    Random::Random(
        const Int& INseed, const Int& INmax, Int::lli INorder_of_entropy,
        const Int& INand1, const Int& INand2,
        const Int& INand3, const Int& INand4,
        size_t INpush1, size_t INpush2, size_t INpush3
    )
        : m_seed(INseed.positive() ? INseed : 1)
        , m_max(INmax.positive() ? INmax : "1E100"_Precision_Int_E)
        , m_and1(INand1), m_and2(INand2), m_and3(INand3), m_and4(INand4)
        , m_order_of_entropy(INorder_of_entropy)
        , m_push1(INpush1), m_push2(INpush2), m_push3(INpush3)
    {}

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
namespace{
    const std::map<Precision::Int, std::string> NumberWordBank{
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
}
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
            Int key1(pow(k_ten, i-1)), key2(toconvert / key1);

        switch(i){
            case 1: //One digit
                toreturn += NumberWordBank.at(key2);
                break;
            case 2: //Two digits
                if(toconvert >= 2*k_ten)
                    toreturn
                        += NumberWordBank.at(key2 * k_ten)
                        + (toconvert%k_ten > 0 ? "-" : "")
                    ;
                else if(toconvert >= k_ten){
                    toreturn += NumberWordBank.at(toconvert);
                    return toreturn;
                }
                break;
            case 3: //Three digits
                toreturn += NumberWordBank.at(key2) + ' ';
                toreturn += NumberWordBank.at(key1) + ' ';
                break;
            default:    //Four or more digits
                key2 = toconvert;
                key1 = 1;
                while(key2.count_digits() > 3){
                    key1 *= k_thousand;
                    key2 /= k_thousand;
                }
                
                toreturn += Num_to_Words(key2) + ' ';
                toreturn += NumberWordBank.at(key1) + ' ';
                break;
        }
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
    Float Remainder(const Float& f, const Float& s)
        {return f.remainder(s);}
/* Support only after studying mathematical gamma function for factorials
    Float Factorial(const Float&);
*/
//Trigonomic functions -- default is radians
    Float Sin(Float angle){
        const Float pi(k_pi_str, angle.precision());
        while(angle.magnitude() > 2*pi)
            angle /= 2*pi;
        Float::str_type copy(angle.str(15));
        std::stringstream ss(copy.substr(1));
        long long int topass(0);
        ss >> topass;
        return ::sin(topass*angle.sign());
    }
    Float Cos(const Float& angle)
        {return Sin(angle + Float(k_pi_str, angle.precision())/2);}
    Float Tan(const Float& angle)
        {return Sin(angle)/Cos(angle);}
    Float Csc(const Float& angle)
        {return 1 / Sin(angle);}
    Float Sec(const Float& angle)
        {return 1 / Cos(angle);}
    Float Cot(const Float& angle)
        {return Cos(angle)/Sin(angle);}
    //Note: Consider support for arcFOO functions if
    //   implementation manually calculates values
}