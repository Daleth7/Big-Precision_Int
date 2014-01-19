#ifndef PRECISION_DIGI_DEFINITION_H__
#define PRECISION_DIGI_DEFINITION_H__

//Note:
//Custom digit type must be signed and able to store values from
//  -(N-1)^2 to (N-1)^2 where N is the base.

#define DIG_TEMPL_              \
    template <                  \
        typename Digit_Type,    \
        typename Base10_Type,   \
        Base10_Type base,       \
        Digit_Type _0,          \
        class Base10toBaseN,    \
        class BaseNtoBase10     \
    >

#define DIG_INST_       \
    digit_class <       \
        Digit_Type,     \
        Base10_Type,    \
        base, _0,       \
        Base10toBaseN,  \
        BaseNtoBase10   \
    >

namespace Precision{
    DIG_TEMPL_
    class digit_class{
        public:
    //Constants
            static constexpr type   k_0     = _0;
            static constexpr type10 k_base  = base;

    //Type aliases
            using type = Digit_Type;
            using type10 = Base10_Type;
            using decton = Base10toBaseN;
            using ntodec = BaseNtoBase10;

    //Read-only
            type value()const;
            operator type()const;

            type10 decimal()const;
            operator type10()const;

            const decton& converter_10toN()const;
            const ntodec& converter_Nto10()const;

            DIG_INST_ operator~()const;

            type carry()const;

    //Modifiers
            DIG_INST_& assign(type);
            DIG_INST_& assign(type10);

        //If (val >= N) or (val <= -N), reduce the
        //  magnitude of val, so (-N < val < N)
            DIG_INST_& reduce();
            
    //Arithmetic
            DIG_INST_& operator+=(const DIG_INST_&);
            DIG_INST_& operator-=(const DIG_INST_&);
            DIG_INST_& operator*=(const DIG_INST_&);
            DIG_INST_& operator/=(const DIG_INST_&);
            DIG_INST_& operator%=(const DIG_INST_&);

    //Bitwise
            DIG_INST_& operator&=(const DIG_INST_&);
            DIG_INST_& operator|=(const DIG_INST_&);
            DIG_INST_& operator^=(const DIG_INST_&);
            DIG_INST_& operator>>=(const DIG_INST_&);
            DIG_INST_& operator<<=(const DIG_INST_&);

    //Constructors and Destructor
            digit_class(const type&);
            digit_class(const type10&);

            digit_class()                               = default;
            digit_class(const DIG_INST_&)               = default;
            digit_class(DIG_INST_&&)                    = default;
            digit_class& operator=(const DIG_INST_&)    = default;
            digit_class& operator=(DIG_INST_&&)         = default;
            ~digit_class()                              = default;

        private:
            type m_digit;
            decton m_decton;
            ntodec m_ntodec;
    };
}

DIG_TEMPL_
Precision::DIG_INST_ operator+(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator-(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator*(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator/(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator%(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);

DIG_TEMPL_
Precision::DIG_INST_ operator&(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator|(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator^(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator>>(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator<<(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);

DIG_TEMPL_
bool operator!(const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator==(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator!=(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator>=(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator<=(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator>(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator<(const Precision::DIG_INST_&, const Precision::DIG_INST_&);

#include "Precision_Digit_Class.inl"

#undef DIG_TEMPL_
#undef DIG_INST_

#endif