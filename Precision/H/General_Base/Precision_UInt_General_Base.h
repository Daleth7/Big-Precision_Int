#ifndef __PRECISION_UNSIGNED_INT_IMPL_GENERAL_BASE_H
#define __PRECISION_UNSIGNED_INT_IMPL_GENERAL_BASE_H

#include "Precision_Int_General_Base.h"

#include "Precision_Tags.h"
#include "Shared_Constants.h"

#include <vector>
#include <sstream>
#include <utility>

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define UINT_TEMPL_             \
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

#define INST_PARAMS_ CharT, _0, Base, Container,    \
        _plus, _neg, _point, _exp, _space

#define UINT_INST_ UInt <INST_PARAMS_>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0, std::ptrdiff_t Base,
            template <typename...> class Container = std::vector,
            CharT _plus = CharT('+'), CharT _neg = CharT('-'),
            CharT _point = CharT('.'), CharT _exp = CharT('E'),
            CharT _space = CharT(' ')
        >
        class UInt : Tag::Integral, Tag::Unsigned {
            public:
        //Type aliases
                using Signed_Int    = Int<INST_PARAMS_>;
                using str_type      = typename Signed_Int::str_type;
                using ulli          = unsigned long long int;
                using ld            = typename Signed_Int::ld;
                using lli           = typename Signed_Int::lli;
                using image_type    = typename Signed_Int::image_type;
                using diglist_type  = typename Signed_Int::diglist_type;
                using digit_type    = typename Signed_Int::digit_type;
                using digit_10_type = typename Signed_Int::digit_10_type;
                using sign_type     = typename Signed_Int::sign_type;
                using size_type     = typename Signed_Int::size_type;
        //Arithmetic operators
                UINT_INST_& operator+=(const UINT_INST_& rhs){
                    m_base += rhs.m_base;
                    m_base.sign(1);
                    return *this;
                }

                UINT_INST_& operator-=(const UINT_INST_& rhs){
                    m_base -= rhs.m_base;
                    m_base.sign(1);
                    return *this;
                }

                UINT_INST_& operator*=(const UINT_INST_& rhs)
                    {return m_base *= rhs.m_base, *this;}

                UINT_INST_& operator/=(const UINT_INST_& rhs)
                    {return m_base /= rhs.m_base, *this;}

                UINT_INST_& operator%=(const UINT_INST_& rhs)
                    {return m_base %= rhs.m_base, *this;}

                UINT_INST_& operator--()
                    {return --m_base, *this;}

                UINT_INST_ operator--(int)
                    {return m_base--;}

                UINT_INST_& operator++()
                    {return ++m_base, *this;}

                UINT_INST_ operator++(int)
                    {return m_base++;}

        //Bitwise operators
                UINT_INST_& operator&=(const UINT_INST_& rhs)
                    {return m_base &= rhs.m_base, *this;}

                UINT_INST_& operator|=(const UINT_INST_& rhs)
                    {return m_base |= rhs.m_base, *this;}

                UINT_INST_& operator^=(const UINT_INST_& rhs)
                    {return m_base ^= rhs.m_base, *this;}

                UINT_INST_& operator<<=(const UINT_INST_& rhs)
                    {return m_base <<= rhs.m_base, *this;}

                UINT_INST_& operator>>=(const UINT_INST_& rhs)
                    {return m_base >>= rhs.m_base, *this;}

        //Logical Operators
                UINT_INST_ logical_and(const UINT_INST_& s)const
                    {return UINT_INST_(m_base.logical_and(s.m_base));}

                UINT_INST_ logical_or(const UINT_INST_& s)const
                    {return UINT_INST_(m_base.logical_or(s.m_base));}

                UINT_INST_ logical_xor(const UINT_INST_& s)const
                    {return UINT_INST_(m_base.logical_xor(s.m_base));}

                UINT_INST_ logical_inversion()const
                    {return UINT_INST_(m_base.logical_inversion());}

                UINT_INST_ logical_shift(lli e)const
                    {return UINT_INST_(m_base.logical_shift(e));}

                UINT_INST_ logical_shift_left(size_type e)const
                    {return UINT_INST_(m_base.logical_shift_left(e));}

                UINT_INST_ logical_shift_right(size_type e)const
                    {return UINT_INST_(m_base.logical_shift_right(e));}

        //Read-only functions
                bool is_integer()const
                    {return true;}

                sign_type sign()const
                    {return 1;}

                str_type str()const
                    {return m_base.str();}

                bool even()const
                    {return m_base.even();}

                bool odd()const
                    {return m_base.odd();}

                bool positive()const
                    {return true;}

                bool negative()const
                    {return false;}

            //Set the precision through parameter
                str_type sci_note(size_type inPrec = k_display_prec)const
                    {return m_base.sci_note(inPrec);}

                str_type
                    sci_note_w_spaces(size_type inPrec = k_display_prec)const
                {return m_base.sci_note_w_spaces(inPrec);}

                size_type count_digits()const
                    {return m_base.count_digits();}

                short compare(const UINT_INST_& s)const
                    {return m_base.compare(s.m_base);}

                Signed_Int get_signed()const
                    {return m_base;}

                Signed_Int operator-()const
                    {return -m_base;}

                    //Does not work for ~0
                Signed_Int operator~()const
                    {return Signed_Int(~m_base);}

                static constexpr digit_10_type base()
                    {return Signed_Int::base();}

        //Other modifiers
                void sign(sign_type){}
                    //Multiplies integer by a power of ten
                void shift(lli tens_exp)
                    {m_base.shift(tens_exp);}

                void shift_left(size_type e)
                    {m_base.shift_left(e);}

                void shift_right(size_type e)
                    {m_base.shift_right(e);}

                void swap(UINT_INST_& s)
                    {m_base.swap(s.m_base);}

        //Conversion operators
                explicit operator Signed_Int()
                    {return m_base;}

        //Constructors and destructor
                UInt(ulli inInt = 0)
                    : m_base(inInt)
                {}

                UInt(const str_type& inImage)
                    : m_base(inImage)
                {m_base.sign(1);}

                UInt(const Signed_Int& inInt)
                    : m_base(inInt)
                {m_base.sign(1);}

                UInt(Signed_Int&& inInt)
                    : m_base(std::move(inInt))
                {m_base.sign(1);}

                UInt(const UINT_INST_&)            =default;
                UInt(UINT_INST_&&)                 =default;
                UInt& operator=(const UINT_INST_&) =default;
                UInt& operator=(UINT_INST_&&)      =default;
                ~UInt()                            =default;
            private:
                Signed_Int   m_base;
        };

        UINT_TEMPL_
        inline UINT_INST_ operator+(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs += rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator-(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs -= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator*(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs *= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator/(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs /= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator%(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs %= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator&(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs &= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator|(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs |= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator^(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs ^= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator>>(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs >>= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator<<(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs <<= rhs;}

        UINT_TEMPL_
        inline bool operator==(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) == 0;}

        UINT_TEMPL_
        inline bool operator!=(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) != 0;}

        UINT_TEMPL_
        inline bool operator>=(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        UINT_TEMPL_
        inline bool operator<=(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        UINT_TEMPL_
        inline bool operator>(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) > 0;}

        UINT_TEMPL_
        inline bool operator<(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) < 0;}

        UINT_TEMPL_
        inline bool operator!(const UINT_INST_& testee)
            {return testee == 0;}
    }
}

UINT_TEMPL_
inline void swap(
    Precision::General_Base::UINT_INST_& a,
    Precision::General_Base::UINT_INST_& b
){a.swap(b);}

#undef UINT_TEMPL_
#undef UINT_INST_
#undef INST_PARAMS_

#endif  //Include guard
