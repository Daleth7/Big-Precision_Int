#ifndef __PRECISION_FLOAT_IMPL_H
#define __PRECISION_FLOAT_IMPL_H

#include "Precision_Int.h"
#include "Precision_UInt.h"
#include "Shared_Constants.h"

#include <string>

class Impl_Float_{
    public:
//Type aliases
        using Integer       = Precision::Int;
        using UInteger      = Precision::UInt;
        using str_type      = std::string;
        using sign_type     = Integer::sign_type;
        using diglist_type  = Integer::diglist_type;
        using lli           = Integer::lli;
        using ld            = long double;
        using size_type     = Integer::size_type;
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
        sign_type sign()const;
        bool even()const;
        bool odd()const;
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
        Impl_Float_ magnitude()const;
        size_type count_digits()const;
        size_type count_left_digits()const;
        size_type count_right_digits()const;
        size_type precision()const;
        short compare(const Impl_Float_&)const;
        Integer integer()const;
        bool show_full()const;

        Impl_Float_ remainder(const Impl_Float_&)const;
        Impl_Float_ inverse()const;
        bool is_integer()const;
//Modifers
        bool show_full(bool);
            //Multiplies integer by a power of ten
        void shift(lli);
        void shift_left(size_type);
        void shift_right(size_type);
        void sign(sign_type);
        void negate();
        Impl_Float_& exponentiate(const Integer&);
        Impl_Float_& exponentiate(const Impl_Float_&, size_type = 0);
        Impl_Float_& invert();
        void swap(Impl_Float_&);

//Overload cast operators
        explicit operator Integer() const;

//Constructors and destructor
        Impl_Float_(ld = 0.0, size_type = k_default_prec);
        Impl_Float_(str_type, size_type = k_default_prec);
        Impl_Float_(const Integer&, size_type = k_default_prec);
        Impl_Float_(const UInteger&, size_type = k_default_prec);

        Impl_Float_(const Impl_Float_&)             =default;
        Impl_Float_(Impl_Float_&&)                  =default;
        Impl_Float_& operator=(const Impl_Float_&)  =default;
        Impl_Float_& operator=(Impl_Float_&&)       =default;
        ~Impl_Float_()                              =default;
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

void swap(Impl_Float_&, Impl_Float_&);

#endif