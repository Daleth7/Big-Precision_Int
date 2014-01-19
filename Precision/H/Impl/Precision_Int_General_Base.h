#ifndef __PRECISION_INT_BASE_IMPL_H
#define __PRECISION_INT_BASE_IMPL_H

#include <string>
#include <functional>

#include "Shared_Constants.h"
#include "Precision_Sign_Class.h"

/*  Template Parameters Clarification
    1) Container                - Where the "digits" are stored. Any STL
                                    container will work. Must support
                                    these functions:
                                    * Container::Container(size_type, Digit_type)
                                    * Container::begin()
                                    * Container::end()
                                    * Container::rbegin()
                                    * Container::rend()
                                    * Container::push_back()
                                    * Bidirectional iterators
                                    * Container::size()
                                    * Container::insert(iterator, size_type,
                                        Digit_Type)
                                    * Container::erase(iterator, size_type)
    2) Digit_Type               - The type the "digit_type" value is stored in
                                    Must support the following functions:
        * std::stringstream& operator<<(std::stringstream&, Digit_Type);
        * std::stringstream& operator>>(std::stringstream&, Digit_Type&);
                                    Must also support basic arithmetic
                                    and logical operations.
    3) Decimal_Representation   - What type to use if the Digit_Type is
                                    converted to base 10.
    4) Base                     - The number base the class will use,
                                    represented in base 10.
    5) _0                       - The minimum value of the base,
                                    representing "0"
    6) BaseNtoBase10            - A converter from Base to decimal. Must
                                    support the function:
                        Decimal_Representation operator()(Digit_Type)const;
    7) Base10toBaseN            - A converter from decimal to Base. Must
                                    support the function:
                        Digit_Type operator()(Decimal_Representation)const;
                                    Parameter can be assumed to be
                                    within the range:
                                [ BaseNtoBase10(_0), Base+BaseNto10(_0) )

    Example Instantiation:

    struct char_to_B10{
        short operator()(char b2)
            {return b2 - '0';}
    };
    struct B10_to_char{
        char operator()(short us)
            {return us + '0';}
    };
    Int_General_Base<
        std::string, char,
        short, 10, '0',
        char_to_B10, B10_to_char
    > myInt;
*/
#define INT_TEMPL_                          \
        template <                          \
            class Container,                \
            typename Digit_Type,            \
            typename Decimal_Representation,\
            Decimal_Representation Base,    \
            Digit_Type _0,                  \
            class BaseNtoBase10,            \
            class Base10toBaseN             \
        >

#define INT_INST_                                           \
        Int_General_Base<                                   \
            Container, Digit_Type, Decimal_Representation,  \
            Base, _0, BaseNtoBase10, Base10toBaseN          \
        >

INT_TEMPL_
class Int_General_Base{
    public:
//Type aliases
        using str_type      = std::string;
        using lli           = long long int;
        using ld            = long double;
        using diglist_type  = Container;
        using digit_type    = Digit_Type;
        using digit10       = Decimal_Representation;
        using sign_type     = Precision::sign_class;
        using size_type     = size_t;
        using ntodec        = BaseNtoBase10;
        using decton        = Base10toBaseN;
//Arithmetic operators
        INT_INST_& operator+=(const INT_INST_&);
        INT_INST_& operator-=(const INT_INST_&);
        INT_INST_& operator*=(const INT_INST_&);
        INT_INST_& operator/=(const INT_INST_&);
        INT_INST_& operator%=(const INT_INST_&);
        INT_INST_& operator--();
        INT_INST_ operator--(int);
        INT_INST_& operator++();
        INT_INST_ operator++(int);
//Bitwise operators
        INT_INST_& operator&=(const INT_INST_&);
        INT_INST_& operator|=(const INT_INST_&);
        INT_INST_& operator^=(const INT_INST_&);
        INT_INST_& operator<<=(const INT_INST_&);
        INT_INST_& operator>>=(const INT_INST_&);
//Read-only functions
        const ntodec& converter_Nto10()const;
        const decton& converter_10toN()const;
        sign_type sign()const;
        str_type str()const;
    //Set the precision through parameter
        str_type sci_note(size_type=k_display_prec)const;
        str_type sci_note_w_spaces(size_type=k_display_prec)const;
        INT_INST_ magnitude()const;
        size_type count_digits()const;
        short compare(const INT_INST_&)const;
        INT_INST_ operator-()const;
        INT_INST_ operator~()const;
        bool even()const;
        bool odd()const;
//Other modifiers
        void shift(lli);
        void shift_left(size_type);
        void shift_right(size_type);
        void sign(sign_type);
        void negate();
        void swap(INT_INST_&);
//Constructors and destructor
        Int_General_Base(lli=0);
        Int_General_Base(const str_type&);
        Int_General_Base(const diglist_type&, sign_type);

        Int_General_Base(const INT_INST_&)             =default;
        Int_General_Base(INT_INST_&&)                  =default;
        Int_General_Base& operator=(const INT_INST_&)  =default;
        Int_General_Base& operator=(INT_INST_&&)       =default;
        ~Int_General_Base()                            =default;
    protected:
            //Helper divide function to allow modulus and divide
            //  operators take about the same time to calculate.
            //  True ~ modulus
            //  False ~ division
        INT_INST_& divide(const INT_INST_&, bool = false);
            //Since AND, OR, and XOR implementations differ in
            //  only the condition, use a helper to centralize
            //  the implementation.
        INT_INST_& bitwise_operation(
            INT_INST_,
            const std::function<bool(bool,bool)>&
        );
    private:
    //Numbers are stored in reverse, e.g. 190 040 002 would be
    //   stored as 002 040 190. The number is reversed because
    //   the length is varied according to the leftmost side.
        diglist_type         m_number;
        sign_type       m_sign;
        /*static constexpr*/ ntodec    m_n10;// = ntodec();
        /*static constexpr*/ decton    m_10n;// = decton();

        static constexpr digit_type      k_0bit  = _0;
        static constexpr digit10    k_base = Base;
};

INT_TEMPL_
INT_INST_ operator+(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator-(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator*(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator/(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator%(INT_INST_, const INT_INST_&);

INT_TEMPL_
INT_INST_ operator&(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator|(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator^(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator>>(INT_INST_, const INT_INST_&);
INT_TEMPL_
INT_INST_ operator<<(INT_INST_, const INT_INST_&);

INT_TEMPL_
bool operator==(const INT_INST_&, const INT_INST_&);
INT_TEMPL_
bool operator!=(const INT_INST_&, const INT_INST_&);
INT_TEMPL_
bool operator>=(const INT_INST_&, const INT_INST_&);
INT_TEMPL_
bool operator<=(const INT_INST_&, const INT_INST_&);
INT_TEMPL_
bool operator>(const INT_INST_&, const INT_INST_&);
INT_TEMPL_
bool operator<(const INT_INST_&, const INT_INST_&);
INT_TEMPL_
bool operator!(const INT_INST_&);

INT_TEMPL_
void swap(INT_INST_&, INT_INST_&);

#include "Precision_Int_General_Base.inl"

#undef INT_TEMPL_
#undef INT_INST_

#endif
