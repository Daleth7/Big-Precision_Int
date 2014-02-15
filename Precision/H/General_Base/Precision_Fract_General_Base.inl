#include "Precision_Math_Shared_Functions.h"

#include <sstream>

namespace Precision{
    namespace General_Base{
        //Arithmetic operators

        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator+=(const FRACT_INST_& rhs){
            if(*this == FRACT_INST_(0))          return *this = rhs;
            else if(rhs == FRACT_INST_(0))       return *this;
            else if(rhs == *this){
                m_numer *= 2;
                this->Simplify();
                return *this;
            //Guaranteed one of them to be negative if true
            }else if(rhs.magnitude() == this->magnitude())
                return *this = 0;
            else if(m_denom == rhs.m_denom){
                m_numer += rhs.m_numer;
                this->Simplify();
                return *this;
            }

            m_numer = m_numer * rhs.m_denom + rhs.m_numer * m_denom;
            m_denom *= rhs.m_denom;

            this->Simplify();
            return *this;
        }

        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator-=(const FRACT_INST_& rhs){
            if(*this == rhs) return *this = 0;
            return *this += -rhs;
        }

        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator*=(const FRACT_INST_& rhs){
            if(*this == FRACT_INST_(0) || rhs == FRACT_INST_(0))
                return *this = 0;
            else if(*this == FRACT_INST_(1))         return *this = rhs;
            else if(rhs == FRACT_INST_(1))           return *this;

            //Make use of the simplify function via constructor
            FRACT_INST_
                operand1(m_numer, rhs.m_denom, m_precision),
                operand2(rhs.m_numer, m_denom, m_precision)
            ;
            m_numer = operand1.m_numer * operand2.m_numer;
            m_denom = operand1.m_denom * operand2.m_denom;
        //No need to call simplify because that work was done in construction
            return *this;
        }

        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator/=(const FRACT_INST_& rhs){
            if(
                *this == FRACT_INST_(0) ||
                rhs == FRACT_INST_(1) ||
                rhs == FRACT_INST_(0)
            )   return *this;
            else if(*this == FRACT_INST_(1))
                return *this = ~rhs;
            return *this *= ~rhs;
        }

        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator%=(const FRACT_INST_& rhs){
            *this /= rhs;
            return (*this -= this->whole());
        }

        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator--()
            {return *this -= 1;}

        FRACT_TEMPL_
        FRACT_INST_ FRACT_INST_::operator--(int)
            {return (*this -= 1)+FRACT_INST_(1);}

        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator++()
            {return *this += 1;}

        FRACT_TEMPL_
        FRACT_INST_ FRACT_INST_::operator++(int)
            {return (*this += 1)+FRACT_INST_(-1);}


        FRACT_TEMPL_
        FRACT_INST_ FRACT_INST_::operator-()const{
            FRACT_INST_ toreturn(*this);
            toreturn.m_numer.negate();
            return toreturn;
        }

        //Overloaded operators with new meanings
            //Invert the fraction

        FRACT_TEMPL_
        FRACT_INST_ FRACT_INST_::operator~()const
            {return FRACT_INST_(m_denom, m_numer, m_precision);}


        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::operator^=(const FRACT_INST_& rhs){
            return
                (rhs.m_denom == Integer(1))
                ? this->exponentiate(rhs.m_numer)
                : this->exponentiate(rhs, m_precision)
            ;
        }



        //Read-only functions

        FRACT_TEMPL_
        typename FRACT_INST_::sign_type FRACT_INST_::sign()const
            {return m_numer.sign();}

        FRACT_TEMPL_
        bool FRACT_INST_::even()const
            {return this->decimal().even();}

        FRACT_TEMPL_
        bool FRACT_INST_::odd()const
            {return this->decimal.odd();}

        FRACT_TEMPL_
        bool FRACT_INST_::positive()const
            {return m_numer.positive();}

        FRACT_TEMPL_
        bool FRACT_INST_::negative()const
            {return m_numer.negative();}

        FRACT_TEMPL_
        typename FRACT_INST_::Integer FRACT_INST_::numerator()const
            {return m_numer;}

        FRACT_TEMPL_
        typename FRACT_INST_::Integer FRACT_INST_::denominator()const
            {return m_denom;}

        FRACT_TEMPL_
        typename FRACT_INST_::str_type FRACT_INST_::str()const{
            str_type temp(m_denom.str().substr(1));
            return m_numer.str() + str_type(1, _slash) + temp;
        }

        FRACT_TEMPL_
        typename FRACT_INST_::str_type FRACT_INST_::mixed()const{
            if(this->whole() == Integer(0)) return this->str();
            return
                this
                -> whole()
                . str()
                + str_type(1, _space)
                + (m_numer%m_denom)
                . str()
                . substr(1)
                + str_type(1, _slash)
                + m_denom
                . str()
                . substr(1)
            ;
        }

            //Set the precision through parameter
        FRACT_TEMPL_
        FRACT_INST_ FRACT_INST_::magnitude()const{
            FRACT_INST_ toreturn(*this);
            toreturn.sign(1);
            return toreturn;
        }

        FRACT_TEMPL_
        typename FRACT_INST_::size_type FRACT_INST_::precision()const
            {return m_precision;}

        FRACT_TEMPL_
        short FRACT_INST_::compare(const FRACT_INST_& s)const{
            if(this == &s)                              return 0;
            else if(m_numer.sign() < s.m_numer.sign())  return -1;
            else if(m_numer.sign() > s.m_numer.sign())  return 1;
            Integer gcfactor = Precision::gcf(m_denom, s.m_denom);
            return (m_numer*gcfactor).compare(s.m_numer*gcfactor);
        }

            //Following two pairs are merely different names for the same thing
        FRACT_TEMPL_
        typename FRACT_INST_::Integer FRACT_INST_::whole()const
            {return m_numer/m_denom;}

        FRACT_TEMPL_
        typename FRACT_INST_::Floating FRACT_INST_::decimal()const
            {return Floating(m_numer)/Floating(m_denom);}

        FRACT_TEMPL_
        typename FRACT_INST_::Integer FRACT_INST_::integer()const
            {return this->whole();}

        FRACT_TEMPL_
        typename FRACT_INST_::Floating FRACT_INST_::floating_point()const
            {return this->decimal();}

        FRACT_TEMPL_
        typename FRACT_INST_::Integer FRACT_INST_::gcd(const FRACT_INST_& s)const
            {return this->GCD_Helper(m_denom, s.m_denom);}


        FRACT_TEMPL_
        FRACT_INST_ FRACT_INST_::remainder(const FRACT_INST_& rhs)const
            {return FRACT_INST_(*this) %= rhs;}

        FRACT_TEMPL_
        FRACT_INST_ FRACT_INST_::inverse()const
            {return ~(*this);}

        FRACT_TEMPL_
        bool FRACT_INST_::is_integer()const
            {return m_denom == Integer(1);}

        FRACT_TEMPL_
        typename FRACT_INST_::image_type FRACT_INST_::digit(size_type i)const
            {return this->decimal().digit(i);}

        FRACT_TEMPL_
        typename FRACT_INST_::digit_10_type
            FRACT_INST_::digit_10(size_type i)
        const{return this->decimal().digit_10(i);}


        FRACT_TEMPL_
        constexpr typename FRACT_INST_::digit_10_type FRACT_INST_::base()
            {return Floating::base();}


        //Other modifiers

        FRACT_TEMPL_
        void FRACT_INST_::precision(size_type inPrec)
            {m_precision = (inPrec ? inPrec : 1);}


        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::invert(){
            std::swap(m_numer, m_denom);
            if(m_denom.sign() < 0)
                m_numer.negate(), m_denom.sign(1);
            return *this;
        }


        FRACT_TEMPL_
        void FRACT_INST_::sign(sign_type newsign)
            {m_numer.sign(newsign);}


        FRACT_TEMPL_
        void FRACT_INST_::negate()
            {m_numer.negate();}


        FRACT_TEMPL_
        void FRACT_INST_::swap(FRACT_INST_& s){
            std::swap(m_numer, s.m_numer);
            std::swap(m_denom, s.m_denom);
            std::swap(m_precision, s.m_precision);
        }


        FRACT_TEMPL_
        void FRACT_INST_::shift(lli z){
            if(z < 0)
                this->shift_right(-z);
            else
                this->shift_left(z);
        }


        FRACT_TEMPL_
        void FRACT_INST_::shift_left(size_type e){
            m_numer.shift_left(e);
            this->Simplify();
        }


        FRACT_TEMPL_
        void FRACT_INST_::shift_right(size_type e){
            m_denom.shift_left(e);
            this->Simplify();
        }


        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::exponentiate(const Integer& exp){
            m_numer = Precision::exponentiate(m_numer, exp);
            m_denom = Precision::exponentiate(m_denom, exp);
            return *this;
        }


        FRACT_TEMPL_
        FRACT_INST_& FRACT_INST_::exponentiate(
            const FRACT_INST_& exp,
            size_type prec
        ){
            if(m_numer.sign().negative() && exp.m_denom.even())
                return *this = 0;
            return *this
                = Precision::exponentiate(*this, exp, prec ? prec : m_precision);
        }

        //Overload cast operators

        FRACT_TEMPL_
        FRACT_INST_::operator Integer() const
            {return this->whole();}

        FRACT_TEMPL_
        FRACT_INST_::operator Floating() const
            {return Floating(m_numer) / m_denom;}

        //Constructors and destructor

        FRACT_TEMPL_
        FRACT_INST_::Fract(ld inFP, size_type inPrec)
            : m_numer(0)
            , m_denom(1)
            , m_precision(inPrec)
        {
            if(inFP > 1e-15 || inFP < -1e-15){
                Floating catalyst(inFP);
                this->Check_Pattern(
                    catalyst
                    . str()
                    . substr(catalyst.str().find(_point) + 1)
                    , catalyst
                );

                if(m_denom == Integer(1)){
                    m_denom.shift_left(catalyst.count_right_digits());
                    catalyst.shift_left(catalyst.count_right_digits());
                    m_numer = catalyst.integer();
                }

                this->Simplify();
            }
        }

        FRACT_TEMPL_
        FRACT_INST_::Fract(const str_type& inImage, size_type inPrec)
            : m_numer(0)
            , m_denom(1)
            , m_precision(inPrec)
        {
            size_type pos(inImage.find(_slash));
            m_numer = Integer(inImage.substr(0, pos));
            if(pos != str_type::npos)
                m_denom = Integer(inImage.substr(pos+1));
            m_denom.sign(1);
            this->Simplify();
        }

        FRACT_TEMPL_
        FRACT_INST_::Fract(const Integer& inWhole, size_type inPrec)
            : m_numer(inWhole)
            , m_denom(1)
            , m_precision(inPrec)
        {}

        FRACT_TEMPL_
        FRACT_INST_::Fract(const Floating& inFP)
            : m_numer(0)
            , m_denom(1)
            , m_precision(inFP.precision())
        {
            const str_type topass(inFP.str(0, true));
            this->Check_Pattern(topass.substr(topass.find(_point)+1), inFP);

            if(m_denom == Integer(1)){
                m_denom.shift_left(inFP.count_right_digits());
                Floating catalyst(inFP);
                catalyst.shift_left(catalyst.count_right_digits());
                m_numer = catalyst.integer();
            }

            this->Simplify();
        }

        FRACT_TEMPL_
        FRACT_INST_::Fract(
            const Integer& inNumerator,
            const Integer& inDenominator,
            size_type inPrecision
        )
            : m_numer(inNumerator)
            , m_denom(inDenominator)
            , m_precision(inPrecision)
        {this->Simplify();}

        //Helpers

        FRACT_TEMPL_
        void FRACT_INST_::Simplify(){
            if(m_numer == Integer(0)){
                m_denom = 1;
                return;
            }else if(m_denom == Integer(0)){
                m_numer = 0;
                m_denom = 1;
                return;
            }else if(m_denom.sign().negative()){
                m_numer.negate();
                m_denom.sign(1);
            }

            const Integer GCD(this->GCD_Helper(m_denom, m_numer.magnitude()));

            m_numer /= GCD;
            m_denom /= GCD;
        }


        FRACT_TEMPL_
        void FRACT_INST_::Check_Pattern(
            const str_type& image,
            const Floating& catalyst
        ){
        /*
                Derivation of Brent's derivation of
            the tortoise and hare algorithm
        */
        //First check if a pattern exists
            if(image.size() < 3)    //Arbitrary
                return;
            unsigned
                pow(1),
                lambda(1)    //Length of pattern
            ;
            const char
                *tortoise(image.c_str()),
                *hare(image.c_str()+1)
            ;
            while(tortoise[0] != hare[0]){
                if(pow == lambda){
                    tortoise = hare;
                    pow <<= 1;
                    lambda = 0;
                }
                ++hare;
                if(hare[0] == '\0')
                    return;
                ++lambda;
            }
            unsigned mu(0); //Position where pattern starts
            tortoise = image.c_str();
            hare = image.c_str() + lambda;
            while(tortoise[0] != hare[0]){
                ++tortoise;
                ++hare;
                ++mu;
            }

            if(
                (mu > 1 && image.substr(0, mu+1).find_last_of(_0[0]) > 0) ||
                lambda == image.size()
            )   return;
            const str_type pattern(image.substr(0, mu+lambda));
            if(pattern.find(image.substr(image.size()-lambda)) == str_type::npos)
                return;
            Integer nonpat(pattern.substr(0, mu));
                nonpat.sign(catalyst.sign());
            m_numer = pattern.substr(mu);
                m_numer.sign(catalyst.sign());
            m_denom = str_type(lambda, _0[Integer::base()-1]);
            m_numer += m_denom*nonpat;
                m_denom.shift_left(mu);
            m_numer += m_denom*catalyst.integer();
        }


        FRACT_TEMPL_
        typename FRACT_INST_::Integer FRACT_INST_::GCD_Helper(
            const Integer& a,
            const Integer& b
        )const{
//Euclid's Algorithm:
//http://en.wikipedia.org/wiki/Greatest_common_divisor#Using_Euclid.27s_algorithm

            Integer toreturn(a), prev(b);
            while(prev != Integer(0)){
                toreturn %= prev;
                std::swap(toreturn, prev);
            }
            return toreturn;
        }


        FRACT_TEMPL_
        typename FRACT_INST_::Integer FRACT_INST_::GCF_Helper(
            const Integer& a,
            const Integer& b
        )const{return (a*b)/GCD_Helper(a, b);}


        FRACT_TEMPL_
        FRACT_INST_ operator+(FRACT_INST_ lhs, const FRACT_INST_& rhs)
            {return FRACT_INST_(lhs) += rhs;}

        FRACT_TEMPL_
        FRACT_INST_ operator-(FRACT_INST_ lhs, const FRACT_INST_& rhs)
            {return FRACT_INST_(lhs) -= rhs;}

        FRACT_TEMPL_
        FRACT_INST_ operator*(FRACT_INST_ lhs, const FRACT_INST_& rhs)
            {return FRACT_INST_(lhs) *= rhs;}

        FRACT_TEMPL_
        FRACT_INST_ operator/(FRACT_INST_ lhs, const FRACT_INST_& rhs)
            {return FRACT_INST_(lhs) /= rhs;}

        FRACT_TEMPL_
        FRACT_INST_ operator%(FRACT_INST_ lhs, const FRACT_INST_& rhs)
            {return FRACT_INST_(lhs) %= rhs;}

        FRACT_TEMPL_
        FRACT_INST_ operator^(FRACT_INST_ lhs, const FRACT_INST_& rhs)
            {return FRACT_INST_(lhs) ^= rhs;}

        FRACT_TEMPL_
        bool operator==(const FRACT_INST_& lhs, const FRACT_INST_& rhs)
            {return lhs.compare(rhs) == 0;}

        FRACT_TEMPL_
        bool operator!=(const FRACT_INST_& lhs, const FRACT_INST_& rhs)
            {return lhs.compare(rhs) != 0;}

        FRACT_TEMPL_
        bool operator>=(const FRACT_INST_& lhs, const FRACT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        FRACT_TEMPL_
        bool operator<=(const FRACT_INST_& lhs, const FRACT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        FRACT_TEMPL_
        bool operator>(const FRACT_INST_& lhs, const FRACT_INST_& rhs)
            {return lhs.compare(rhs) > 0;}

        FRACT_TEMPL_
        bool operator<(const FRACT_INST_& lhs, const FRACT_INST_& rhs)
            {return lhs.compare(rhs) < 0;}

        FRACT_TEMPL_
        bool operator!(const FRACT_INST_& lhs)
            {return lhs == 0;}
    }
}

FRACT_TEMPL_
void swap(
    Precision::General_Base::FRACT_INST_& a,
    Precision::General_Base::FRACT_INST_& b
){a.swap(b);}