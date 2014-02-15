#ifndef __PRECISION_FLOAT_IMPL_GENERAL_BASE_H
#define __PRECISION_FLOAT_IMPL_GENERAL_BASE_H

#include "Precision_Int_General_Base.h"
#include "Precision_UInt_General_Base.h"

#include "Precision_Tags.h"
#include "Shared_Constants.h"

#include <vector>

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define FLOAT_TEMPL_            \
    template <                  \
        typename CharT,         \
        CharT const *const _0,  \
        std::ptrdiff_t Base,    \
        template <typename...>  \
            class Container,    \
        CharT _plus,            \
        CharT _neg,             \
        CharT _point,           \
        CharT _exp,             \
        CharT _space            \
    >

#define INST_PARAMS_                        \
        CharT, _0, Base, Container,         \
        _plus, _neg, _point, _exp, _space

#define FLOAT_INST_ Float <INST_PARAMS_>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0, std::ptrdiff_t Base,
            template <typename...> class Container = std::vector,
            CharT _plus = CharT('+'), CharT _neg = CharT('-'),
            CharT _point = CharT('.'), CharT _exp = CharT('E'),
            CharT _space = CharT(' ')
        >
        class Float : Tag::Floating_Point, Tag::Signed {
            public:
        //Type aliases
                using Integer       = Int<INST_PARAMS_>;
                using UInteger      = UInt<INST_PARAMS_>;
                using str_type      = typename Integer::str_type;
                using sign_type     = typename Integer::sign_type;
                using image_type    = typename Integer::image_type;
                using diglist_type  = typename Integer::diglist_type;
                using digit_type    = typename Integer::digit_type;
                using digit_10_type = typename Integer::digit_10_type;
                using lli           = typename Integer::lli;
                using ld            = typename Integer::ld;
                using size_type     = typename Integer::size_type;
        //Arithmetic operators
                FLOAT_INST_& operator+=(const FLOAT_INST_&);
                FLOAT_INST_& operator-=(const FLOAT_INST_&);
                FLOAT_INST_& operator*=(const FLOAT_INST_&);
                FLOAT_INST_& operator/=(const FLOAT_INST_&);
                FLOAT_INST_& operator%=(const FLOAT_INST_&);
                FLOAT_INST_& operator--();
                FLOAT_INST_ operator--(int);
                FLOAT_INST_& operator++();
                FLOAT_INST_ operator++(int);

                FLOAT_INST_ operator-()const;
        //Other operators with different meaning
                    //Return the inverse
                FLOAT_INST_ operator~()const;
                    //Raise to the power of
                FLOAT_INST_& operator^=(const FLOAT_INST_&);
        //Read-only functions
                sign_type sign()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
                str_type str(size_type = 0, bool inShowFull = false)const;
            //Set the precision through parameter
                str_type sci_note(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                str_type sci_note_w_spaces(
                    size_type = k_display_prec,
                    bool inShowFull = false
                )const;
                FLOAT_INST_ magnitude()const;
                size_type count_digits()const;
                size_type count_left_digits()const;
                size_type count_right_digits()const;
                size_type precision()const;
                short compare(const FLOAT_INST_&)const;
                Integer integer()const;
                bool show_full()const;

                FLOAT_INST_ remainder(const FLOAT_INST_&)const;
                FLOAT_INST_ inverse()const;
                bool is_integer()const;
                image_type digit(size_type)const;
                digit_10_type digit_10(size_type)const;

                static constexpr digit_10_type base();
        //Modifers
                bool show_full(bool);
                    //Multiplies integer by a power of ten
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                void sign(sign_type);
                void negate();
                FLOAT_INST_& exponentiate(const Integer&);
                FLOAT_INST_& exponentiate(const FLOAT_INST_&, size_type = 0);
                FLOAT_INST_& invert();
                void swap(FLOAT_INST_&);

        //Overload cast operators
                explicit operator Integer() const;

        //Constructors and destructor
                Float(ld = 0.0, size_type = k_default_prec);
                Float(str_type, size_type = k_default_prec);
                //Float(const Integer&, size_type = k_default_prec);
                Float(const Integer&);
                Float(const Integer&, size_type p);
                Float(const UInteger&, size_type = k_default_prec);

                Float(const FLOAT_INST_&)             =default;
                Float(FLOAT_INST_&&)                  =default;
                Float& operator=(const FLOAT_INST_&)  =default;
                Float& operator=(FLOAT_INST_&&)       =default;
                ~Float()                              =default;
            protected:
        //Helpers
                void Update_Precision(size_type);
                Integer Generate_Operand(size_type)const;
            private:
            //Use a mantissa-like format
                Integer                 m_whole;
            //Precision represents the number of digits to
            //  the right of the decimal point.
                size_type               m_precision;
                bool                    m_show_full;
        };

        FLOAT_TEMPL_
        FLOAT_INST_ operator+(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator-(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator*(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator/(FLOAT_INST_, const FLOAT_INST_&);
        FLOAT_TEMPL_
        FLOAT_INST_ operator%(FLOAT_INST_, const FLOAT_INST_&);

        FLOAT_TEMPL_
        FLOAT_INST_ operator^(FLOAT_INST_, const FLOAT_INST_&);

        FLOAT_TEMPL_
        bool operator==(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator!=(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator>=(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator<=(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator>(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator<(const FLOAT_INST_&, const FLOAT_INST_&);
        FLOAT_TEMPL_
        bool operator!(const FLOAT_INST_&);
    }
}

FLOAT_TEMPL_
void swap(
    Precision::General_Base::FLOAT_INST_&,
    Precision::General_Base::FLOAT_INST_&
);

#include "Precision_Float_General_Base.inl"

#undef FLOAT_TEMPL_
#undef FLOAT_INST_
#undef INST_PARAMS_

#endif  //Include guard