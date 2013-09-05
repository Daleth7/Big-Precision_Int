#ifndef __PRECISION_INT_IMPL_H
#define __PRECISION_INT_IMPL_H

#include <string>

#include "Shared_Constants.h"

class Impl_Int_{
    public:
//Type aliases
        using Str       = std::string;
        using lli       = long long int;
        using ld        = long double;
        using diglist   = std::string;
        using digit     = char;
        using Sign      = short;
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
        Sign sign()const;
        Str str()const;
    //Set the precision through parameter
        Str sci_note(size_t=k_display_prec)const;
        Str sci_note_w_spaces(size_t=k_display_prec)const;
        Impl_Int_ magnitude()const;
        size_t count_digits()const;
        short compare(const Impl_Int_&)const;
        Impl_Int_ operator-()const;
        Impl_Int_ operator~()const;
//Other modifiers
        void shift(lli);
//Constructors and destructor
        Impl_Int_(lli=0);
        Impl_Int_(diglist);

        Impl_Int_(const Impl_Int_&)             =default;
        Impl_Int_(Impl_Int_&&)                  =default;
        Impl_Int_& operator=(const Impl_Int_&)  =default;
        Impl_Int_& operator=(Impl_Int_&&)       =default;
        ~Impl_Int_()                            =default;
    private:
    //Numbers are stored in reverse, e.g. 190 040 002 would be
    //   stored as 002 040 190. The number is reversed because
    //   the length is varied according to the leftmost side.
        diglist     m_number;
        Sign        m_sign;
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

#endif