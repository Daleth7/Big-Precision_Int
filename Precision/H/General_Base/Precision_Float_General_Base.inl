#include "Precision_Math_Shared_Functions.h"

#include <sstream>
#include <utility>

namespace Precision{
    namespace General_Base{
        //Arithmetic operators

        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator+=(const FLOAT_INST_& rhs){
            m_whole
                = this->Generate_Operand(rhs.m_precision)
                + rhs.Generate_Operand(this->m_precision)
            ;
            this->Update_Precision(rhs.m_precision);
            return *this;
        }

        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator-=(const FLOAT_INST_& rhs){
            m_whole
                = this->Generate_Operand(rhs.m_precision)
                - rhs.Generate_Operand(this->m_precision)
            ;
            this->Update_Precision(rhs.m_precision);
            return *this;
        }

        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator*=(const FLOAT_INST_& rhs){
            m_whole *= rhs.m_whole;
            m_whole.shift_right(rhs.m_precision);
            this->Update_Precision(rhs.m_precision);
            return *this;
        }

        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator/=(const FLOAT_INST_& rhs){
            Integer exp(1);
            exp.shift_left(rhs.count_right_digits());
            FLOAT_INST_ operand(rhs * FLOAT_INST_(exp));
            (m_whole *= exp) /= operand.integer();

            this->Update_Precision(rhs.m_precision);
            return *this;
        }

        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator%=(const FLOAT_INST_& rhs){
            if(*this == rhs || rhs == FLOAT_INST_(0))
                return *this = FLOAT_INST_(0);

            *this /= rhs;
            FLOAT_INST_ catalyst(*this);
            catalyst.shift_right(m_precision);
            catalyst.shift_left(m_precision);
            return *this -= catalyst;
        }

        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator--()
            {return (*this -= 1);}

        FLOAT_TEMPL_
        FLOAT_INST_ FLOAT_INST_::operator--(int)
            {return (*this -= 1) + FLOAT_INST_(1);}

        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator++()
            {return (*this += 1);}

        FLOAT_TEMPL_
        FLOAT_INST_ FLOAT_INST_::operator++(int)
            {return (*this += 1) + FLOAT_INST_(-1);}


        FLOAT_TEMPL_
        FLOAT_INST_ FLOAT_INST_::operator-()const{
            FLOAT_INST_ toreturn(*this);
            toreturn.m_whole.negate();
            return toreturn;
        }



        //Other operators with different meaning
            //Return the inverse

        FLOAT_TEMPL_
        FLOAT_INST_ FLOAT_INST_::operator~()const
            {return (FLOAT_INST_(1) / *this);}

            //Raise to the power of
        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::operator^=(const FLOAT_INST_& s){
            return (
                s.is_integer()
                ? this->exponentiate(s.integer())
                : this->exponentiate(s, m_precision)
            );
        }



        //Read-only functions

        FLOAT_TEMPL_
        typename FLOAT_INST_::sign_type FLOAT_INST_::sign()const
            {return m_whole.sign();}


        FLOAT_TEMPL_
        bool FLOAT_INST_::even()const
            {return m_whole.even();}


        FLOAT_TEMPL_
        bool FLOAT_INST_::odd()const
            {return m_whole.odd();}


        FLOAT_TEMPL_
        bool FLOAT_INST_::positive()const
            {return m_whole.positive();}


        FLOAT_TEMPL_
        bool FLOAT_INST_::negative()const
            {return m_whole.negative();}


        FLOAT_TEMPL_
        typename FLOAT_INST_::str_type
            FLOAT_INST_::str(size_type inPrec, bool inShowFull)
        const{
            if(inPrec > m_precision)
                inPrec = m_precision;
            str_type toreturn(m_whole.str());

            if(toreturn.size() == 2 && toreturn.back() == _0[0])
                return toreturn += str_type(1, _point)
                    + str_type(inPrec ? inPrec : 1, _0[0]);
                //If the number is something like 0.009
            if(m_precision > m_whole.count_digits())
                toreturn.insert(1, m_precision - m_whole.count_digits(), _0[0]);
            toreturn.insert(toreturn.size() - m_precision, 1, _point);

            if(m_precision >= m_whole.count_digits())
                toreturn.insert(1, 1, _0[0]);
            if(m_show_full || inShowFull) return toreturn;
            else if(inPrec == 0){
                while(toreturn.back() == _0[0] && toreturn.back() != _point)
                    toreturn.pop_back();

                if(toreturn.back() == _point && m_precision > 0)
                    toreturn.push_back(_0[0]);
                else if(toreturn.back() == _point)
                    toreturn.pop_back();

                return toreturn;
            }

            size_type min = m_precision - inPrec - 1;
            while(min-- > 0) toreturn.pop_back();
            
            if(toreturn.back() == _point && m_precision > 0)
                toreturn.push_back(_0[0]);
            else
                toreturn.pop_back();
            
            return toreturn;
        }

        //Set the precision through parameter

        FLOAT_TEMPL_
        typename FLOAT_INST_::str_type
            FLOAT_INST_::sci_note(size_type inPrec, bool inShowFull)
        const{
            if(inPrec == 0)
                inPrec = m_precision;
            str_type toreturn(m_whole.sci_note((m_show_full || inShowFull)
                ? m_precision : inPrec));
            toreturn.erase(toreturn.find(_exp)+1);

            toreturn += (
                (m_whole.count_digits() < m_precision)
                ? str_type(1, _neg)
                    + Integer(m_precision - m_whole.count_digits() + 1)
                    . str()
                    . substr(1)
                : Integer(m_whole.count_digits() - m_precision - 1)
                    . str()
                    . substr(1)
            );
            return toreturn;
        }


        FLOAT_TEMPL_
        typename FLOAT_INST_::str_type FLOAT_INST_::sci_note_w_spaces(
            size_type inPrec,
            bool inShowFull
        )const{
            str_type toreturn(this->sci_note(inPrec, inShowFull));
            toreturn.insert(1, 1, _space);
            toreturn.insert(toreturn.find(_exp), 1, _space);
            toreturn.insert(toreturn.find(_exp)+1, 1, _space);
            return toreturn;
        }


        FLOAT_TEMPL_
        FLOAT_INST_ FLOAT_INST_::magnitude()const{
            FLOAT_INST_ toreturn(*this);
            toreturn.m_whole = toreturn.m_whole.magnitude();
            return toreturn;
        }


        FLOAT_TEMPL_
        typename FLOAT_INST_::size_type FLOAT_INST_::count_digits()const
            {return this->count_left_digits() + this->count_right_digits();}


        FLOAT_TEMPL_
        typename FLOAT_INST_::size_type FLOAT_INST_::count_left_digits()const
            {return m_whole.count_digits() - m_precision;}


        FLOAT_TEMPL_
        typename FLOAT_INST_::size_type FLOAT_INST_::count_right_digits()const{
            if(m_whole == Integer(0)) return 1;
            str_type image(m_whole.str().substr(
                    //Add 1 to account for sign character
                m_whole.count_digits() + 1 - m_precision
            ));
            while(image.back() == _0[0]) image.pop_back();
            return image.size();
        }


        FLOAT_TEMPL_
        typename FLOAT_INST_::size_type FLOAT_INST_::precision()const
            {return m_precision;}


        FLOAT_TEMPL_
        short FLOAT_INST_::compare(const FLOAT_INST_& s)const{
            if(m_whole.sign() < s.m_whole.sign())
                return -1;
            else if(m_whole.sign() > s.m_whole.sign())
                return 1;
            else if(m_whole == Integer(0) && s.m_whole != Integer(0))
                return -1;
            else if(m_whole != Integer(0) && s.m_whole == Integer(0))
                return 1;

            Integer a(m_whole), b(s.m_whole);
            if(m_precision > s.m_precision){
                a.shift_right(m_precision - s.m_precision);
            }else{
                b.shift_right(s.m_precision - m_precision);
            }

            return a.compare(b);
        }


        FLOAT_TEMPL_
        typename FLOAT_INST_::Integer FLOAT_INST_::integer()const{
            Integer toreturn(m_whole);
            toreturn.shift_right(m_precision);
            return toreturn;
        }


        FLOAT_TEMPL_
        bool FLOAT_INST_::show_full()const
            {return m_show_full;}


        FLOAT_TEMPL_
        FLOAT_INST_ FLOAT_INST_::remainder(const FLOAT_INST_& s)const
            {return *this % s;}


        FLOAT_TEMPL_
        FLOAT_INST_ FLOAT_INST_::inverse()const
            {return ~(*this);}


        FLOAT_TEMPL_
        bool FLOAT_INST_::is_integer()const
            {return this->count_right_digits() == 0;}

        FLOAT_TEMPL_
        typename FLOAT_INST_::image_type FLOAT_INST_::digit(size_type i)const
            {return m_whole.digit(i);}

        FLOAT_TEMPL_
        typename FLOAT_INST_::digit_10_type
            FLOAT_INST_::digit_10(size_type i)
        const{return m_whole.digit_10(i);}


        FLOAT_TEMPL_
        constexpr typename FLOAT_INST_::digit_10_type FLOAT_INST_::base()
            {return Integer::base();}

        //Modifiers

        FLOAT_TEMPL_
        bool FLOAT_INST_::show_full(bool inFlag){
            bool toreturn(m_show_full);
            m_show_full = inFlag;
            return toreturn;
        }
            //Multiplies integer by a power of ten

        FLOAT_TEMPL_
        void FLOAT_INST_::shift(lli tens_exp)
            {m_whole.shift(tens_exp);}

        FLOAT_TEMPL_
        void FLOAT_INST_::shift_left(size_type e)
            {m_whole.shift_left(e);}

        FLOAT_TEMPL_
        void FLOAT_INST_::shift_right(size_type e)
            {m_whole.shift_right(e);}

        FLOAT_TEMPL_
        void FLOAT_INST_::sign(sign_type newsign)
            {m_whole.sign(newsign);}

        FLOAT_TEMPL_
        void FLOAT_INST_::negate()
            {m_whole.negate();}


        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::exponentiate(const Integer& exp)
            {return *this = Precision::exponentiate(*this, exp);}


        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::exponentiate(
            const FLOAT_INST_& s,
            size_type prec
        ){
            if(this->sign().negative() && m_whole % Integer(4) != Integer(0))
                return *this = 0;
            return *this
                = Precision::exponentiate(*this, s, prec ? prec : m_precision);
        }


        FLOAT_TEMPL_
        FLOAT_INST_& FLOAT_INST_::invert()
            {return *this = FLOAT_INST_(1) / *this;}


        FLOAT_TEMPL_
        void FLOAT_INST_::swap(FLOAT_INST_& s){
            std::swap(m_whole, s.m_whole);
            std::swap(m_precision, s.m_precision);
            std::swap(m_show_full, s.m_show_full);
        }

        //Overload cast operators

        FLOAT_TEMPL_
        FLOAT_INST_::operator Integer() const
            {return this->integer();}

        //Constructors and destructor

        FLOAT_TEMPL_
        FLOAT_INST_::Float(ld inFP, size_type inPrec)
            : m_whole(1)
            , m_precision(inPrec ? inPrec : k_default_prec)
            , m_show_full(false)
        {
            sign_type newsign(inFP < 0 ? -1 : 1);

            std::stringstream ss("");
                //Use std::fixed to ensure converting the whole number
                ss << std::fixed << (inFP * newsign);
            std::string s(ss.str());
            const size_t pos(s.find('.')), e(s.size() - pos - 1);
            s.erase(pos, 1);
            ss.str("");
            ss << s;
            lli whole_part(0);
            ss >> whole_part;
            m_whole = Integer(whole_part);
            if(inPrec > e)
                m_whole.shift_left(inPrec - e);
        }


        FLOAT_TEMPL_
        FLOAT_INST_::Float(str_type inImage, size_type inPrec)
            : m_whole(0)
            , m_precision(inPrec)
            , m_show_full(false)
        {
            if(inImage.size() != 0){
                const size_type pos = inImage.find(_point);
                if(pos == str_type::npos)
                    m_whole = Integer(inImage + str_type(m_precision, _0[0]));
                else{
                    inImage.erase(pos, 1);
                    const size_type str_prec(inImage.size() - pos);
                    m_whole = Integer(inImage);
                    if(str_prec > inPrec)
                        m_precision = str_prec;
                    else
                        m_whole.shift_left(inPrec - str_prec);
                }
            }
        }


        FLOAT_TEMPL_
        FLOAT_INST_::Float(const Integer& inInt)
            : m_whole(inInt)
            , m_precision(k_default_prec)
            , m_show_full(false)
        {m_whole.shift_left(m_precision);}

        FLOAT_TEMPL_
        FLOAT_INST_::Float(const Integer& inInt, size_type inPrec)
            : m_whole(inInt)
            , m_precision(inPrec)
            , m_show_full(false)
        {m_whole.shift_left(inPrec);}


        FLOAT_TEMPL_
        FLOAT_INST_::Float(const UInteger& inInt, size_type inPrec)
            : m_whole(inInt.base())
            , m_precision(inPrec)
            , m_show_full(false)
        {m_whole.shift_left(inPrec);}

        //Helpers

        FLOAT_TEMPL_
        void FLOAT_INST_::Update_Precision(size_type newPrec){
            if(newPrec >= m_precision) return;
            m_whole.shift_right(m_precision - newPrec);
            m_precision = newPrec;
        }


        FLOAT_TEMPL_
        typename FLOAT_INST_::Integer
            FLOAT_INST_::Generate_Operand(size_type inPrec)const
        {
            if(inPrec <= m_precision) return m_whole;
            Integer toreturn(m_whole);
            toreturn.shift_left(inPrec - m_precision);
            return toreturn;
        }



        FLOAT_TEMPL_
        FLOAT_INST_ operator+(FLOAT_INST_ lhs, const FLOAT_INST_& rhs)
            {return lhs += rhs;}

        FLOAT_TEMPL_
        FLOAT_INST_ operator-(FLOAT_INST_ lhs, const FLOAT_INST_& rhs)
            {return lhs -= rhs;}

        FLOAT_TEMPL_
        FLOAT_INST_ operator*(FLOAT_INST_ lhs, const FLOAT_INST_& rhs)
            {return lhs *= rhs;}

        FLOAT_TEMPL_
        FLOAT_INST_ operator/(FLOAT_INST_ lhs, const FLOAT_INST_& rhs)
            {return lhs /= rhs;}

        FLOAT_TEMPL_
        FLOAT_INST_ operator%(FLOAT_INST_ lhs, const FLOAT_INST_& rhs)
            {return lhs %= rhs;}


        FLOAT_TEMPL_
        FLOAT_INST_ operator^(FLOAT_INST_ lhs, const FLOAT_INST_& rhs)
            {return lhs ^= rhs;}


        FLOAT_TEMPL_
        bool operator==(const FLOAT_INST_& lhs, const FLOAT_INST_& rhs)
            {return lhs.compare(rhs) == 0;}

        FLOAT_TEMPL_
        bool operator!=(const FLOAT_INST_& lhs, const FLOAT_INST_& rhs)
            {return lhs.compare(rhs) != 0;}

        FLOAT_TEMPL_
        bool operator>=(const FLOAT_INST_& lhs, const FLOAT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        FLOAT_TEMPL_
        bool operator<=(const FLOAT_INST_& lhs, const FLOAT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        FLOAT_TEMPL_
        bool operator>(const FLOAT_INST_& lhs, const FLOAT_INST_& rhs)
            {return lhs.compare(rhs) > 0;}

        FLOAT_TEMPL_
        bool operator<(const FLOAT_INST_& lhs, const FLOAT_INST_& rhs)
            {return lhs.compare(rhs) < 0;}

        FLOAT_TEMPL_
        bool operator!(const FLOAT_INST_& lhs)
            {return lhs == 0;}
    }
}

FLOAT_TEMPL_
void swap(
    Precision::General_Base::FLOAT_INST_& a,
    Precision::General_Base::FLOAT_INST_& b
){a.swap(b);}