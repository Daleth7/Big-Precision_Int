#include "Precision_Binary.h"
#include "General_Base/Precision_Math_Shared_Functions.h"

#include <vector>
#include <algorithm>
#include <sstream>
#include <utility>

namespace Precision{
    namespace Binary{
        //Overloaded operators
        Int& Int::operator+=(const Int& s){
            if(s == Int(0)) return *this;
            if(*this == Int(0)) return (*this = s);

            image_type carry(0);
            diglist_type small(s.m_number), big(m_number);
            if(big.size() < small.size())
                std::swap(big, small);
            small.insert(small.end(), big.size() - small.size(), false);
            for(
                auto titer(m_number.begin()), siter(small.begin());
                titer != m_number.end();
                ++titer, ++siter
            ){
                image_type catalyst(
                    *titer * m_sign
                    + *siter * s.m_sign
                    + carry
                );
                carry = catalyst / (1 << k_range);
                if(catalyst < 0)
                    catalyst *= -1;
                *titer = catalyst % (1 << k_range);
            }
            m_number = big;

            if(carry){
                if(carry < 0){
                    m_sign = -1;
                    carry *= -1;
                }
                m_number.push_back(carry);
            }

            return *this;
        }

        Int& Int::operator-=(const Int& rhs){
            if(*this == rhs) return (*this = Int(0));
            return (*this += (-rhs));
        }

        Int& Int::operator*=(const Int& rhs){
            if(rhs == Int(0))         return *this = Int(0);
            else if(*this == Int(0) || rhs == Int(1))
                                            return *this;
            else if(*this == Int(1))  return *this = rhs;
            else if(rhs == Int(-1))   return m_sign.negate(), *this;
            else if(*this == Int(-1)){
                *this = rhs;
                m_sign.negate();
                return *this;
            }
            sign_type sign_hold(m_sign * rhs.m_sign);

            Int big(*this), small(rhs);
            if(big.magnitude() < small.magnitude())
                std::swap(big, small);
            size_type z_count(0);
            while(big.m_number.size() > 0 && big.m_number.front() == 0)
                big.m_number.erase(big.m_number.begin()), ++z_count;
            while(small.m_number.size() > 0 && small.m_number.front() == 0)
                small.m_number.erase(small.m_number.begin()), ++z_count;
            if(big.m_number.size() == 0 || small.m_number.size() == 0)
                return *this = 0;
            std::vector<Int> addends;
        //Cut down on runtime by reducing number of iterations
            auto iter(small.m_number.begin());
            for(size_type i(0); i < small.m_number.size(); ++i, ++iter){
                Int addend(0);
                image_type operand(*iter);
                while(operand-- > 0)
                    addend += big;
                addend.m_number.insert(addend.m_number.begin(), i, 0);
                addends.push_back(addend);
            }
            m_number = diglist_type(1, 0);
            for(
                auto addend(addends.begin());
                addend != addends.end();
                ++addend
            ) *this += *addend;
            m_number.insert(m_number.begin(), z_count, 0);

            this->m_sign = sign_hold;
            return *this;
        }

        Int& Int::operator/=(const Int& rhs){
            if(*this == rhs) return (*this = 1);
            else if(rhs == Int(0) || this->magnitude() < rhs.magnitude())
                return (*this = Int(0));
            else if(rhs == Int(1)) return *this;
            return divide(rhs);
        }

        Int& Int::operator%=(const Int& rhs){
            if(rhs == *this || rhs == Int(0) || rhs == Int(1))
                return (*this = Int(0));
            else if(rhs.magnitude() > this->magnitude()) return *this;
            else if(rhs == Int(2))   return *this = this->odd();
            return divide(rhs, true);
        }

        Int& Int::operator--()
            {return (*this += -1);}

        Int Int::operator--(int)
            {return (*this += Int(-1))+Int(1);}

        Int& Int::operator++()
            {return (*this += 1);}

        Int Int::operator++(int)
            {return (*this += Int(1))+Int(-1);}

        //Bitwise operators
        //Use vector<bool> for dynamic sized bitsets
        typedef std::vector<bool> BitSet;
        Int& Int::operator&=(const Int& rhs)
            {return bitwise_operation(rhs, 1);}

        Int& Int::operator|=(const Int& rhs)
            {return bitwise_operation(rhs, 2);}

        Int& Int::operator^=(const Int& rhs)
            {return bitwise_operation(rhs, 3);}

        Int& Int::operator<<=(const Int& rhs){
            if(rhs.m_sign.negative())
                return *this >>= rhs.magnitude();
            Int operand(rhs);
            auto reduce = [&](size_type i){
                while(operand > i*k_range){
                    operand -= i*k_range;
                    m_number.insert(m_number.begin(), i, false);
                }
            };
            reduce(100);
            reduce(18);
            reduce(1);
            image_type carry(false);
            const size_type shift_factor(operand.m_number.front());
            for(auto iter(m_number.rbegin()); iter != m_number.rend(); ++iter){
                image_type old_carry(carry);
                carry = *iter;
                carry >>= 8 - shift_factor;
                *iter <<= shift_factor;
                *iter &= (1 << k_range) - 1;
                *iter |= old_carry;
            }
            if(carry)
                m_number.push_back(carry);
            return *this;
        }

        Int& Int::operator>>=(const Int& rhs){
            if(rhs.m_sign.negative())
                return *this <<= rhs.magnitude();
            Int operand(rhs);
            auto reduce = [&](size_type i){
                while(operand > i*k_range){
                    operand -= i*k_range;
                    auto end(m_number.end());
                    advance(end, i);
                    m_number.erase(m_number.begin(), end);
                }
            };
            reduce(100);
            reduce(18);
            reduce(1);
            image_type carry(false);
            const size_type shift_factor(operand.m_number.front());
            for(auto iter(m_number.begin()); iter != m_number.end(); ++iter){
                image_type old_carry(carry);
                carry = *iter;
                carry &= (1 << shift_factor) - 1;
                *iter >>= shift_factor;
                *iter |= old_carry << (8 - shift_factor);
            }
            if(carry)
                m_number.push_back(carry);
            return *this;
        }


        //Read-only functions
        typename Int::sign_type Int::sign()const
            {return m_sign;}

        typename Int::str_type Int::str()const{
            if(*this == Int(0))   return "+0";
            str_type toreturn(m_sign.positive() ? "+" : "-");
            for(auto iter(m_number.rbegin()); iter != m_number.rend(); ++iter){
                str_type word(k_range, '0');
                for(size_type counter(0); counter < k_range; ++counter)
                    word[counter] = (*iter & (1 << counter)) ? '1' : '0';
                std::reverse(word.begin(), word.end());
                toreturn += word;
            }
            while(toreturn[1] == '0')
                toreturn.erase(1, 1);
            return toreturn;
        }

        typename Int::str_type Int::sci_note(size_type prec)const{
            if(*this == Int(0))
                return "+0";
            else if(m_number.size() < 2)
                return this->str() + "E1";

            str_type toreturn(this->str());
            size_type exp(toreturn.size() - 2);
            toreturn.insert(2, 1, '.');
            if(prec < exp)
                toreturn.erase(3+prec);
            if(toreturn.back() == '.')
                toreturn.pop_back();
            std::stringstream ss;
                ss << exp;
            toreturn += "E" + ss.str();

            return toreturn;
        }

        typename Int::str_type
            Int::sci_note_w_spaces(size_type prec)
        const{
            str_type toreturn(this->sci_note(prec));
            if(toreturn == "0") return toreturn;
            toreturn.insert(1, 1, ' ');//Insert space after the sign
            toreturn.insert(toreturn.find('E'), 1, ' ');
            toreturn.insert(toreturn.find('E')+1, 1, ' ');
            return toreturn;
        }

        Int Int::magnitude()const{
            //Seclude from multiplication operators
            Int toreturn(*this);
                toreturn.m_sign = 1;
            return toreturn;
        }

        typename Int::size_type Int::count_digits()const{
            size_type toreturn(m_number.size()*k_range);
            size_type counter(k_range);
            while(counter-- > 0){
                if( m_number.back() & (1 << counter) )
                    break;
                --toreturn;
            }
            return toreturn;
        }

        short Int::compare(const Int& s)const{
            if(this == &s)                                  return 0;
            else if(m_sign < s.m_sign)                      return -1;
            else if(m_sign > s.m_sign)                      return 1;
            else if(m_number == s.m_number)                 return 0;
            else if(m_sign == -1 && m_number.size() > s.m_number.size())
                                                            return -1;
            else if(m_sign == -1 && m_number.size() < s.m_number.size())
                                                            return 1;
            else if(m_number.size() < s.m_number.size())    return -1;
            else if(m_number.size() > s.m_number.size())    return 1;
            for(
                auto titer(m_number.rbegin()), siter(s.m_number.rbegin());
                titer != m_number.rend();
                ++titer, ++siter
            ){
                if(*titer < *siter)         return -m_sign.value();
                else if(*titer > *siter)    return m_sign.value();
            }
                                                            return 0;
        }

        Int Int::operator-()const{
            Int toreturn(*this);
            toreturn.m_sign.negate();
            return toreturn;
        }

        Int Int::operator~()const{
            if(*this == Int(0))
                return *this;

            Int toreturn(*this);
            for(
                auto iter(toreturn.m_number.begin());
                iter != toreturn.m_number.end();
                ++iter
            )   *iter = ~(*iter) & ((1 << k_range) - 1);
            toreturn.m_sign.negate();

            return toreturn;
        }

        bool Int::even()const
            {return !(this->odd());}

        bool Int::odd()const
            {return m_number.front();}

        bool Int::positive()const
            {return m_sign.positive();}

        bool Int::negative()const
            {return m_sign.negative();}

        typename Int::image_type Int::digit(size_type i)const{
            auto iter(m_number.begin());
            advance(iter, i/k_range);
            return ( *iter & (1 << (i%k_range)) ) ? true : false;
        }

        typename Int::digit_10_type Int::digit_10(size_type i)const
            {return this->digit(i);}

        constexpr typename Int::digit_10_type Int::base()
            {return 2;}

        //Other modifiers
        void Int::shift(lli tens_exp){
            if(tens_exp < 0)
                this->shift_right(-tens_exp);
            else
                this->shift_left(tens_exp);
        }

        void Int::shift_left(size_type e)
            {*this <<= Int(e);}

        void Int::shift_right(size_type e)
            {*this >>= Int(e);}

        void Int::sign(sign_type newsign)
            {m_sign = newsign;}

        void Int::negate()
            {m_sign.negate();}

        void Int::swap(Int& s){
            std::swap(m_number, s.m_number);
            std::swap(m_sign, s.m_sign);
        }
        //Constructors and destructor
        Int::Int(lli newnumber)
            : m_number(0, false)
            , m_sign(newnumber < 0 ? -1 : 1)
        {
            newnumber *= m_sign;
            while(newnumber){
                m_number.push_back(newnumber % (1 << k_range));
                newnumber >>= k_range;
            }
        }

        Int::Int(const str_type& newnumber)
            : m_number(0, false)
            , m_sign(newnumber[0] == '-' ? -1 : 1)
        {
            if(newnumber.size() > 0){
                auto convert = [](const str_type& word){
                    image_type toreturn(false);
                    for(size_type i(0); i < k_range; ++i){
                        if(word[i] != '1' && word[i] != '0')
                            continue;
                        toreturn += ( (word[i]-'0') << i );
                    }
                    return toreturn;
                };
                str_type image(newnumber.substr(m_sign.negative()));
                std::reverse(image.begin(), image.end());
                while(image.size() > 0){
                    m_number.push_back(convert(image.substr(0, k_range)));
                    image.erase(0, k_range);
                }

                while(m_number.size() > 1 && !m_number.back())
                    m_number.pop_back();

                if(m_number.size() == 1 && !m_number.front())
                    m_sign.make_positive();
            }
        }

        Int::Int(const diglist_type& n, sign_type s)
            : m_number(n)
            , m_sign(s)
        {std::reverse(m_number.begin(), m_number.end());}

        Int& Int::divide(const Int& rhs, bool get_modulus){
            if(*this == rhs) return (*this = 1);
            else if(rhs == Int(0) || this->magnitude() < rhs.magnitude())
                return (*this = Int(0));
            else if(rhs == Int(1)) return *this;

            Int
                quotient(0),
                remainder(this->magnitude()),
                tens(rhs.magnitude())
            ;
            size_type t_counter(remainder.m_number.size() - tens.m_number.size());

            tens.m_number.insert(tens.m_number.begin(), t_counter, false);

            while(tens >= rhs.magnitude()){
                Int addend(1);
                addend.shift_left(t_counter);
                while(remainder >= tens){
                    quotient += addend;
                    remainder -= tens;
                }
                tens.m_number.erase(tens.m_number.begin()), --t_counter;
            }
            if(!get_modulus){
                quotient.m_sign = this->m_sign * rhs.m_sign;
                return (*this = quotient);
            }else
                return (*this = remainder);
        }

        Int& Int::bitwise_operation(
            const Int& s,
            unsigned short condition
        ){
            auto titer(m_number.begin());
            auto siter(s.m_number.cbegin());
            for(;
                titer != m_number.end() && siter != s.m_number.cend();
                ++titer, ++siter
            ){
                switch(condition){
                    case 1:
                        *titer &= *siter;
                        break;
                    case 2:
                        *titer |= *siter;
                        break;
                    case 3:
                        *titer ^= *siter;
                        break;
                    default:
                        break;
                }
            }
            switch(condition){
                case 1:
                    m_sign = m_sign.negative() & s.m_sign.negative();
                    break;
                case 2:
                    m_sign = m_sign.negative() | s.m_sign.negative();
                    break;
                case 3:
                    m_sign = m_sign.negative() ^ s.m_sign.negative();
                    break;
                default:
                    break;
            }
            return *this;
        }

        Int operator+(Int lhs, const Int& rhs)
            {return lhs += rhs;}

        Int operator-(Int lhs, const Int& rhs)
            {return lhs -= rhs;}

        Int operator*(Int lhs, const Int& rhs)
            {return lhs *= rhs;}

        Int operator/(Int lhs, const Int& rhs)
            {return lhs /= rhs;}

        Int operator%(Int lhs, const Int& rhs)
            {return lhs %= rhs;}

        Int operator&(Int lhs, const Int& rhs)
            {return lhs &= rhs;}

        Int operator|(Int lhs, const Int& rhs)
            {return lhs |= rhs;}

        Int operator^(Int lhs, const Int& rhs)
            {return lhs ^= rhs;}

        Int operator>>(Int lhs, const Int& rhs)
            {return lhs >>= rhs;}

        Int operator<<(Int lhs, const Int& rhs)
            {return lhs <<= rhs;}

        bool operator==(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) == 0;}

        bool operator!=(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) != 0;}

        bool operator>=(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) >= 0;}

        bool operator<=(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) <= 0;}

        bool operator>(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) > 0;}

        bool operator<(const Int& lhs, const Int& rhs)
            {return lhs.compare(rhs) < 0;}

        bool operator!(const Int& lhs)
            {return lhs == Int(0);}
    }
}

void swap(
    Precision::Binary::Int& a,
    Precision::Binary::Int& b
)   {a.swap(b);}
