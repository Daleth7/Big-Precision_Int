#ifndef __PRECISION_INT_IMPL_H
#define __PRECISION_INT_IMPL_H

#define GENERAL_BASE

#ifndef GENERAL_BASE

#include <string>
#include <functional>

#include "Shared_Constants.h"
#include "Precision_Sign_Class.h"

class Impl_Int_{
    public:
//Type aliases
        using str_type      = std::string;
        using lli           = long long int;
        using ld            = long double;
        using diglist_type  = std::string;
        using digit_type    = char;
        using digit_10_type = short;
        using sign_type     = Precision::sign_class;
        using size_type     = size_t;
//Arithmetic operators
        Impl_Int_& operator+=(const Impl_Int_&);
        Impl_Int_& operator-=(const Impl_Int_&);
        Impl_Int_& operator*=(const Impl_Int_&);
        Impl_Int_& operator/=(const Impl_Int_&);
        Impl_Int_& operator%=(const Impl_Int_&);
        Impl_Int_& operator--();
        Impl_Int_ operator--(int);
        Impl_Int_& operator++();
        Impl_Int_ operator++(int);
//Bitwise operators
        Impl_Int_& operator&=(const Impl_Int_&);
        Impl_Int_& operator|=(const Impl_Int_&);
        Impl_Int_& operator^=(const Impl_Int_&);
        Impl_Int_& operator<<=(const Impl_Int_&);
        Impl_Int_& operator>>=(const Impl_Int_&);
//Read-only functions
        sign_type sign()const;
        str_type str()const;
    //Set the precision through parameter
        str_type sci_note(size_type=k_display_prec)const;
        str_type sci_note_w_spaces(size_type=k_display_prec)const;
        Impl_Int_ magnitude()const;
        size_type count_digits()const;
        short compare(const Impl_Int_&)const;
        Impl_Int_ operator-()const;
        Impl_Int_ operator~()const;
        bool even()const;
        bool odd()const;
//Other modifiers
        void shift(lli);
        void shift_left(size_type);
        void shift_right(size_type);
        void sign(sign_type);
        void negate();
        void swap(Impl_Int_&);
//Constructors and destructor
        Impl_Int_(lli=0);
        Impl_Int_(const diglist_type&);

        Impl_Int_(const Impl_Int_&)             =default;
        Impl_Int_(Impl_Int_&&)                  =default;
        Impl_Int_& operator=(const Impl_Int_&)  =default;
        Impl_Int_& operator=(Impl_Int_&&)       =default;
        ~Impl_Int_()                            =default;
    protected:
            //Helper divide function to allow modulus and divide
            //  operators take about the same time to calculate.
            //  True ~ modulus
            //  False ~ division
        Impl_Int_& divide(const Impl_Int_&, bool = false);
            //Since AND, OR, and XOR implementations differ in
            //  only the condition, use a helper to centralize
            //  the implementation.
        Impl_Int_& bitwise_operation(
            Impl_Int_,
            const std::function<bool(bool,bool)>&
        );
    private:
    //Numbers are stored in reverse, e.g. 190 040 002 would be
    //   stored as 002 040 190. The number is reversed because
    //   the length is varied according to the leftmost side.
        diglist_type     m_number;
        sign_type   m_sign;

        static constexpr digit_type      k_0bit  = '0';
        static constexpr digit_10_type    k_limit = 10;
};

Impl_Int_ operator+(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator-(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator*(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator/(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator%(Impl_Int_, const Impl_Int_&);

Impl_Int_ operator&(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator|(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator^(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator>>(Impl_Int_, const Impl_Int_&);
Impl_Int_ operator<<(Impl_Int_, const Impl_Int_&);

bool operator==(const Impl_Int_&, const Impl_Int_&);
bool operator!=(const Impl_Int_&, const Impl_Int_&);
bool operator>=(const Impl_Int_&, const Impl_Int_&);
bool operator<=(const Impl_Int_&, const Impl_Int_&);
bool operator>(const Impl_Int_&, const Impl_Int_&);
bool operator<(const Impl_Int_&, const Impl_Int_&);
bool operator!(const Impl_Int_&);

void swap(Impl_Int_&, Impl_Int_&);

#else

#include "Precision_Int_General_Base.h"

#include <string>

struct char_to_short{constexpr short operator()(char c)const{return c-'0';}};
struct short_to_char{constexpr char operator()(short c)const{return c+'0';}};

using Impl_Int_ = Int_General_Base <std::string, char, short, 10, '0', 
    char_to_short, short_to_char>;

#endif  //End GENERAL_BASE

#endif  //End Include guard
