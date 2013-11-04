#ifndef __PRECISION_FLOAT_IMPL_H
#define __PRECISION_FLOAT_IMPL_H

#include "Precision_Int.h"
#include "Precision_UInt.h"
#include "Shared_Constants.h"

#include <string>

class Impl_Float_{
    public:
//Type aliases
        using Integer   = Precision::Int;
        using UInteger  = Precision::UInt;
        using Str       = std::string;
        using Sign      = Precision::Int::Sign;
        using diglist   = Precision::Int::diglist;
        using lli       = Precision::Int::lli;
        using ld        = long double;
        using Size_Type = Precision::Int::Size_Type;
//Arithmetic operators
        Impl_Float_& operator+=(const Impl_Float_&);
        Impl_Float_& operator-=(const Impl_Float_&);
        Impl_Float_& operator*=(const Impl_Float_&);
        Impl_Float_& operator/=(const Impl_Float_&);
        Impl_Float_& operator%=(const Impl_Float_&);
        Impl_Float_& operator--();
        Impl_Float_ operator--(int);
        Impl_Float_& operator++();
        Impl_Float_ operator++(int);

        Impl_Float_ operator-()const;
//Other operators with different meaning
            //Return the inverse
        Impl_Float_ operator~()const;
            //Raise to the power of
        Impl_Float_& operator^=(const Impl_Float_&);
//Read-only functions
        Sign sign()const;
        bool even()const;
        bool odd()const;
        Str str(Size_Type = 0, bool inShowFull = false)const;
    //Set the precision through parameter
        Str sci_note(
            Size_Type = k_display_prec,
            bool inShowFull = false
        )const;
        Str sci_note_w_spaces(
            Size_Type = k_display_prec,
            bool inShowFull = false
        )const;
        Impl_Float_ magnitude()const;
        Size_Type count_digits()const;
        Size_Type count_left_digits()const;
        Size_Type count_right_digits()const;
        Size_Type precision()const;
        short compare(const Impl_Float_&)const;
        Integer integer()const;
        bool show_full()const;

        Impl_Float_ remainder(const Impl_Float_&)const;
        Impl_Float_ inverse()const;
//Modifers
        bool show_full(bool);
            //Multiplies integer by a power of ten
        void shift(lli);
        void sign(Sign);
        void negate();
        Impl_Float_& exponentiate(const Impl_Float_&, Size_Type = 0);
//Overload cast operators
        explicit operator Integer() const;
//Constructors and destructor
        Impl_Float_(ld = 0.0, Size_Type = k_default_prec);
        Impl_Float_(diglist, Size_Type = k_default_prec);
        Impl_Float_(const Integer&, Size_Type = k_default_prec);
        Impl_Float_(const UInteger&, Size_Type = k_default_prec);

        Impl_Float_(const Impl_Float_&)             =default;
        Impl_Float_(Impl_Float_&&)                  =default;
        Impl_Float_& operator=(const Impl_Float_&)  =default;
        Impl_Float_& operator=(Impl_Float_&&)       =default;
        ~Impl_Float_()                              =default;
    protected:
//Helpers
        void Update_Precision(Size_Type);
        Integer Generate_Operand(Size_Type)const;
        Impl_Float_& Exponentiate_Hub(Integer);
        Impl_Float_& Exponentiate_Hub(const Impl_Float_&, Size_Type);
    private:
    //Use a mantissa-like format
        Integer                 m_whole;
    //Precision represents the number of digits to
    //  the right of the decimal point.
        Size_Type               m_precision;
        bool                    m_show_full;
};

Impl_Float_ operator+(Impl_Float_, const Impl_Float_&);
Impl_Float_ operator-(Impl_Float_, const Impl_Float_&);
Impl_Float_ operator*(Impl_Float_, const Impl_Float_&);
Impl_Float_ operator/(Impl_Float_, const Impl_Float_&);
Impl_Float_ operator%(Impl_Float_, const Impl_Float_&);

Impl_Float_ operator^(Impl_Float_, const Impl_Float_&);

bool operator==(const Impl_Float_&, const Impl_Float_&);
bool operator!=(const Impl_Float_&, const Impl_Float_&);
bool operator>=(const Impl_Float_&, const Impl_Float_&);
bool operator<=(const Impl_Float_&, const Impl_Float_&);
bool operator>(const Impl_Float_&, const Impl_Float_&);
bool operator<(const Impl_Float_&, const Impl_Float_&);
bool operator!(const Impl_Float_&);

#endif