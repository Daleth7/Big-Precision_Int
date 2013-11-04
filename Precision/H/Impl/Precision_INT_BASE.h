#ifndef __PRECISION_INT_BASE_IMPL_H
#define __PRECISION_INT_BASE_IMPL_H

#include <string>

#include "Shared_Constants.h"

/*  Template Parameters Clarification
    1) Container                - Where the "digits" are stored. Any STL
                                    container will work. Must support
                                    these functions:
                                    * Container::begin()
                                    * Container::end()
                                    * Container::rbegin()
                                    * Container::rend()
                                    * Container::iterator::operator--()
                                    * Container::iterator::operator++()
                                    * Container::size()
    2) Digit_Type               - The type the "digit" value is stored in
                                    Must support the following functions:
        * std::stringstream& operator<<(std::stringstream&, Digit_Type);
        * std::stringstream& operator>>(std::stringstream&, Digit_Type);
                                    Must also support basic arithmetic
                                    and logical operations.
    3) Decimal_Representation   - What type to use if the Digit_Type is
                                    converted to base 10.
    4) Base                     - The number base the class will use
    5) _0                       - The minimum value of the base,
                                    representing "0"
    6) BaseNtoBase10            - A converter from Base to decimal. Must
                                    support the syntax:
                                        BaseNtoBase10 converter;
                                        Digit_Type dig1;
                                        Decimal_Representation dec;
                                        dec  = converter(dig1);
    7) Base10toBaseN            - A converter from decimal to Base. Must
                                    support the syntax:
                                        BaseNtoBase10 converter;
                                        Digit_Type dig1;
                                        Decimal_Representation dec;
                                        dig1  = converter(dec);
                                    Parameter can be assumed to be
                                    within the range:
                                        [BaseNtoBase10(_0), Base)

    Example Instantiation:

    struct char_to_B10{
        unsigned short operator()(char b2)
            {return b2 - '0';}
    };
    struct B10_to_char{
        char operator()(unsigned short us)
            {return us + '0';}
    };
    INT_BASE_<
        std::string,
        char,
        short,
        10,
        '0',
        char_to_B10,
        B10_to_char
    > myInt;
*/
#define __INT__TEMPLATE__HEADER_            \
        template <                          \
            class Container,                \
            typename Digit_Type,            \
            typename Decimal_Representation,\
            Digit_Type Base,                \
            Digit_Type _0,                  \
            class BaseNtoBase10,            \
            class Base10toBaseN             \
        >
#define INT_TEMPLATE_                       \
        INT_BASE_<                          \
            Container,                      \
            Digit_Type,                     \
            Decimal_Representation,         \
            Base,                           \
            _0,                             \
            BaseNtoBase10,                  \
            Base10toBaseN                   \
        >

__INT__TEMPLATE__HEADER_
class INT_BASE_{
    public:
//Type aliases
        using Str       = std::string;
        using lli       = long long int;
        using ld        = long double;
        using diglist   = Container;
        using digit     = Digit_Type;
        using digit10   = Decimal_Representation;
        using Sign      = short;
        using Size_Type = unsigned long long int;
        using _Nto10    = BaseNtoBase10;
        using _10toN    = Base10toBaseN;
//Arithmetic operators
        INT_TEMPLATE_& operator+=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator-=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator*=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator/=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator%=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator--();
        INT_TEMPLATE_ operator--(int);
        INT_TEMPLATE_& operator++();
        INT_TEMPLATE_ operator++(int);
//Bitwise operators
        INT_TEMPLATE_& operator&=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator|=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator^=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator<<=(const INT_TEMPLATE_&);
        INT_TEMPLATE_& operator>>=(const INT_TEMPLATE_&);
//Read-only functions
        Sign sign()const;
        Str str()const;
    //Set the precision through parameter
        Str sci_note(Size_Type=k_display_prec)const;
        Str sci_note_w_spaces(Size_Type=k_display_prec)const;
        INT_TEMPLATE_ magnitude()const;
        Size_Type count_digits()const;
        short compare(const INT_TEMPLATE_&)const;
        INT_TEMPLATE_ operator-()const;
        INT_TEMPLATE_ operator~()const;
        bool even()const;
        bool odd()const;
//Other modifiers
        void shift(lli);
        void sign(Sign);
        void negate();
//Constructors and destructor
        INT_BASE_(lli=0);
        INT_BASE_(diglist, Sign);
            //The image in the string should be in the same
            //  base as what the instantiation represents, not
            //  base 10.
        INT_BASE_(Str);

        INT_BASE_(const INT_TEMPLATE_&)                 =default;
        INT_BASE_(INT_TEMPLATE_&&)                      =default;
        INT_TEMPLATE_& operator=(const INT_TEMPLATE_&)  =default;
        INT_TEMPLATE_& operator=(INT_TEMPLATE_&&)       =default;
        ~INT_BASE_()                                    =default;
    private:
    //Numbers are stored in reverse, e.g. 190 040 002 would be
    //   stored as 002 040 190. The number is reversed because
    //   the length is varied according to the leftmost side.
        diglist     m_number;
        Sign        m_sign;

        //static constexpr _Nto10     NtoDec = _Nto10();
        //static constexpr _10toN     DectoN = _10toN();
        _Nto10     NtoDec = _Nto10();
        _10toN     DectoN = _10toN();
        static constexpr digit10    k_limit = Base;
        static constexpr digit      k_0bit  = _0;
};

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator+(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator-(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator*(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator/(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator%(INT_TEMPLATE_, const INT_TEMPLATE_&);

__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator&(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator|(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator^(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator>>(INT_TEMPLATE_, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
INT_TEMPLATE_ operator<<(INT_TEMPLATE_, const INT_TEMPLATE_&);

__INT__TEMPLATE__HEADER_
bool operator==(const INT_TEMPLATE_&, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
bool operator!=(const INT_TEMPLATE_&, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
bool operator>=(const INT_TEMPLATE_&, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
bool operator<=(const INT_TEMPLATE_&, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
bool operator>(const INT_TEMPLATE_&, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
bool operator<(const INT_TEMPLATE_&, const INT_TEMPLATE_&);
__INT__TEMPLATE__HEADER_
bool operator!(const INT_TEMPLATE_&);

#include "Precision_INT_BASE.inl"

#endif
