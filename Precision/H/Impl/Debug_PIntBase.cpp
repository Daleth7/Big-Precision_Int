#include "Precision_INT_BASE.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>

struct _10toChar{
    char operator()(short s)const
        {return s + '0';}
};

struct _Charto10{
    short operator()(char ch)const
        {return ch - '0';}
};

struct Int
    : public INT_BASE_<
        std::string,
        char,
        short,
        10,
        '0',
        _Charto10,
        _10toChar
    >
{
    Int(const std::string& s)
        : INT_BASE_(s)
    {}
    Int(const std::string& s, Sign i)
        : INT_BASE_(s, i)
    {}
    Int(lli i)
        : INT_BASE_(i)
    {}
};

struct _1000to10{
    short operator()(short s)const
        {return s;}
};
struct _10to1000{
    short operator()(short s)const
        {return s;}
};

struct _1000
    : public INT_BASE_<
        std::vector<long>,
        int,
        int,
        1000,
        1,
        _1000to10,
        _10to1000
    >
{
    _1000(const Str& s)
        : INT_BASE_(s)
    {}
    _1000(const diglist& s, Sign i)
        : INT_BASE_(s, i)
    {}
    _1000(lli i)
        : INT_BASE_(i)
    {}
};

int main(){
    {
        Int
            testee1("128375829875"),
            t2(0),
            t3(-912784),
            t4("29384", -1),
            t5(4)
        ;
        std::cout << testee1.str() << '\n';
        std::cout << t2.str() << '\n';
        std::cout << t3.str() << '\n';
        std::cout << t4.str() << '\n';
        std::cout << (t3+t4).str() << '\n';
        std::cout << t5.str() << '\n';
    }
    std::cout << '\n';
    {
        _1000
            testee1("29834"),
            t2(0),
            t3(-912784),
            t4(_1000::diglist({234, 333, 982, 19}), -1)
        ;
        std::cout << testee1.str() << '\n';
        std::cout << t2.str() << '\n';
        std::cout << t3.str() << '\n';
        std::cout << t4.str() << '\n';
        std::cout << (testee1+t4).str() << '\n';
    }

    return 0;
}
