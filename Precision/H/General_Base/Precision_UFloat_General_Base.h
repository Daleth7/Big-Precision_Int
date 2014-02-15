#ifndef __PRECISION_UNSIGNED_FLOAT_IMPL_GENERAL_BASE_H
#define __PRECISION_UNSIGNED_FLOAT_IMPL_GENERAL_BASE_H

#include "Precision_Float_General_Base.h"
#include "Precision_UInt_General_Base.h"

#include "Precision_Tags.h"
#include "Shared_Constants.h"

#include <vector>

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define UFLOAT_TEMPL_           \
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

#define UFLOAT_INST_ UFloat <               \
        CharT, _0, Base, Container,         \
        _plus, _neg, _point, _exp, _space   \
    >

#include <utility>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0, std::ptrdiff_t Base,
            template <typename...> class Container = std::vector,
            CharT _plus = CharT('+'), CharT _neg = CharT('-'),
            CharT _point = CharT('.'), CharT _exp = CharT('E'),
            CharT _space = CharT(' ')
        >
        class UFloat : Tag::Floating_Point, Tag::Unsigned {
            public:
        //Type aliases
                using UInteger      = UInt<CharT, _0, Base, Container>;
                using Integer       = Int<CharT, _0, Base, Container>;
                using Signed_Float  = Float<CharT, _0, Base, Container>;
                using str_type      = typename Signed_Float::str_type;
                using ld            = typename Signed_Float::ld;
                using lli           = typename Signed_Float::lli;
                using image_type    = typename Signed_Float::image_type;
                using diglist_type  = typename Signed_Float::diglist_type;
                using digit_type    = typename Signed_Float::digit_type;
                using digit_10_type = typename Signed_Float::digit_10_type;
                using size_type     = typename Signed_Float::size_type;
                using sign_type     = typename Signed_Float::sign_type;
        //Arithmetic operators
                UFLOAT_INST_& operator+=(const UFLOAT_INST_& rhs){
                    m_base += rhs.m_base;
                    m_base.sign(1);
                    return *this;
                }

                UFLOAT_INST_& operator-=(const UFLOAT_INST_& rhs){
                    m_base -= rhs.m_base;
                    m_base.sign(1);
                    return *this;
                }

                UFLOAT_INST_& operator*=(const UFLOAT_INST_& rhs)
                    {return m_base *= rhs.m_base, *this;}

                UFLOAT_INST_& operator/=(const UFLOAT_INST_& rhs)
                    {return m_base /= rhs.m_base, *this;}

                UFLOAT_INST_& operator%=(const UFLOAT_INST_& rhs)
                    {return m_base %= rhs.m_base, *this;}

                UFLOAT_INST_& operator--()
                    {return --m_base, *this;}

                UFLOAT_INST_ operator--(int)
                    {return UFLOAT_INST_(m_base--);}

                UFLOAT_INST_& operator++()
                    {return ++m_base, *this;}

                UFLOAT_INST_ operator++(int)
                    {return UFLOAT_INST_(m_base++);}

                    //Returns the power of, not XOR
                UFLOAT_INST_& operator^=(const Integer& rhs)
                    {return m_base ^= rhs, *this;}

                UFLOAT_INST_& operator^=(const UFLOAT_INST_& rhs)
                    {return m_base ^= rhs.m_base, *this;}

        //Read-only functions
                sign_type sign()const
                    {return 1;}

                str_type str(size_type inPrec = 0, bool inShowFull = false)const
                    {return m_base.str(inPrec, inShowFull);}

                bool even()const
                    {return m_base.even();}

                bool odd()const
                    {return m_base.odd();}

                bool positive()const
                    {return true;}

                bool negative()const
                    {return false;}

            //Set the precision through parameter
                str_type sci_note(
                    size_type inPrec = k_display_prec,
                    bool inShowFull = false
                )const{return m_base.sci_note(inPrec, inShowFull);}

                str_type sci_note_w_spaces(
                    size_type inPrec = k_display_prec,
                    bool inShowFull = false
                )const{return m_base.sci_note_w_spaces(inPrec, inShowFull);}

                size_type count_digits()const
                    {return m_base.count_digits();}

                size_type count_left_digits()const
                    {return m_base.count_left_digits();}

                size_type count_right_digits()const
                    {return m_base.count_right_digits();}

                size_type precision()const
                    {return m_base.precision();}

                short compare(const UFLOAT_INST_& s)const
                    {return m_base.compare(s.m_base);}

                Integer integer()const
                    {return m_base.integer();}

                bool show_full()const
                    {return m_base.show_full();}

                UFLOAT_INST_ remainder(const UFLOAT_INST_& s)const
                    {return UFLOAT_INST_(m_base.remainder(s.m_base));}

                Signed_Float get_signed()const
                    {return m_base;}
                
                Signed_Float operator-()const
                    {return -m_base;}

                bool is_integer()const
                    {return m_base.is_integer();}

                UFLOAT_INST_ inverse()const
                    {return UFLOAT_INST_(m_base.inverse());}

                static constexpr digit_10_type base()
                    {return Signed_Float::base();}

        //Other modifers
                void sign(sign_type){}

                bool show_full(bool inFlag)
                    {return m_base.show_full(inFlag);}

                    //Multiplies integer by a power of ten
                void shift(lli tens_exp)
                    {m_base.shift(tens_exp);}

                void shift_left(size_type e)
                    {m_base.shift_left(e);}

                void shift_right(size_type e)
                    {m_base.shift_right(e);}

                UFLOAT_INST_& invert()
                    {return m_base.invert(), *this;}

                void swap(UFLOAT_INST_& s)
                    {m_base.swap(s.m_base);}

        //Overload cast operators
                explicit operator Integer() const
                    {return m_base.integer();}

                explicit operator UInteger() const
                    {return UInteger(m_base.integer());}

                explicit operator Signed_Float() const
                    {return m_base;}

        //Constructors and destructor
                UFloat(
                    ld inFP = 0.0,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inFP*(inFP>0?1:-1), inPrec)
                {}

                UFloat(
                    const str_type& inImage,
                    size_type inPrec = k_default_prec
                )
                    : m_base(
                        inImage[0] == _neg || inImage[0] == _plus
                            ? inImage.substr(1) : inImage,
                        inPrec
                    )
                {}

                explicit UFloat(
                    const Integer& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inInt, inPrec)
                {m_base.sign(1);}

                explicit UFloat(
                    Integer&& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(std::move(inInt), inPrec)
                {m_base.sign(1);}

                explicit UFloat(
                    const UInteger& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inInt, inPrec)
                {m_base.sign(1);}

                explicit UFloat(
                    UInteger&& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(std::move(inInt), inPrec)
                {m_base.sign(1);}

                explicit UFloat(const Signed_Float& inFP)
                    : m_base(inFP)
                {m_base.sign(1);}

                explicit UFloat(Signed_Float&& inFP)
                    : m_base(std::move(inFP))
                {m_base.sign(1);}

                UFloat(const UFLOAT_INST_&)            =default;
                UFloat(UFLOAT_INST_&&)                 =default;
                UFloat& operator=(const UFLOAT_INST_&) =default;
                UFloat& operator=(UFLOAT_INST_&&)      =default;
                ~UFloat()                              =default;
            private:
                Signed_Float   m_base;
        };

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator+(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs += rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator-(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs -= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator*(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs *= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator/(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs /= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator%(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs %= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator^(
            UFLOAT_INST_ lhs,
            const typename UFLOAT_INST_::Integer& rhs
        )   {return lhs ^= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator^(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs ^= rhs;}

        UFLOAT_TEMPL_
        inline bool operator==(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) == 0;}

        UFLOAT_TEMPL_
        inline bool operator!=(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) != 0;}

        UFLOAT_TEMPL_
        inline bool operator>=(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        UFLOAT_TEMPL_
        inline bool operator<=(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        UFLOAT_TEMPL_
        inline bool operator>(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        UFLOAT_TEMPL_
        inline bool operator<(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        UFLOAT_TEMPL_
        inline bool operator!(const UFLOAT_INST_& testee)
            {return testee == 0;}
    }
}

UFLOAT_TEMPL_
inline void swap(
    Precision::General_Base::UFLOAT_INST_& a,
    Precision::General_Base::UFLOAT_INST_& b
){a.swap(b);}

#undef UFLOAT_TEMPL_
#undef UFLOAT_INST_

#endif  //Include guard