#ifndef PRECISION_BINARY_SPECIALIZATION
#define PRECISION_BINARY_SPECIALIZATION

#include "General_Base/Shared_Constants.h"
#include "General_Base/Precision_Sign_Class.h"

#include <string>
#include <functional>
#include <list>

namespace Precision{
    namespace Binary{
        class Int{
            public:
        //Type aliases
                using str_type      = std::string;
                using lli           = long long int;
                using ld            = long double;
                using image_type    = char;
                using digit_type    = image_type const *;
                using diglist_type  = std::list<image_type>;
                using digit_10_type = std::ptrdiff_t;
                using sign_type     = sign_class;
                using size_type     = size_t;
        //Arithmetic operators
                Int& operator+=(const Int&);
                Int& operator-=(const Int&);
                Int& operator*=(const Int&);
                Int& operator/=(const Int&);
                Int& operator%=(const Int&);
                Int& operator--();
                Int operator--(int);
                Int& operator++();
                Int operator++(int);
        //Bitwise operators
                Int& operator&=(const Int&);
                Int& operator|=(const Int&);
                Int& operator^=(const Int&);
                Int& operator<<=(const Int&);
                Int& operator>>=(const Int&);
        //Read-only functions
                sign_type sign()const;
                str_type str()const;
            //Set the precision through parameter
                str_type sci_note(size_type=k_display_prec)const;
                str_type sci_note_w_spaces(size_type=k_display_prec)const;
                Int magnitude()const;
                size_type count_digits()const;
                short compare(const Int&)const;
                Int operator-()const;
                Int operator~()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
                image_type digit(size_type)const;
                digit_10_type digit_10(size_type)const;

                static constexpr digit_10_type base();
        //Other modifiers
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                void sign(sign_type);
                void negate();
                void swap(Int&);
        //Constructors and destructor
                Int(lli = 0);
                Int(const str_type&);
                Int(const diglist_type&, sign_type);

                Int(const Int&)             =default;
                Int(Int&&)                  =default;
                Int& operator=(const Int&)  =default;
                Int& operator=(Int&&)       =default;
                ~Int()                      =default;
            protected:
                    //Helper divide function to allow modulus and divide
                    //  operators take about the same time to calculate.
                    //  True ~ modulus
                    //  False ~ division
                Int& divide(const Int&, bool = false);
                    //Since AND, OR, and XOR implementations differ in
                    //  only the condition, use a helper to centralize
                    //  the implementation.
                Int& bitwise_operation(const Int&, unsigned short);
            private:
            //Numbers are stored in reverse, e.g. 190 040 002 would be
            //   stored as 002 040 091. The number is reversed because
            //   the length is varied according to the leftmost side.
                diglist_type    m_number;
                sign_type       m_sign;

                static constexpr size_type  k_range = 4;
        };

        Int operator+(Int, const Int&);
        Int operator-(Int, const Int&);
        Int operator*(Int, const Int&);
        Int operator/(Int, const Int&);
        Int operator%(Int, const Int&);

        Int operator&(Int, const Int&);
        Int operator|(Int, const Int&);
        Int operator^(Int, const Int&);
        Int operator>>(Int, const Int&);
        Int operator<<(Int, const Int&);

        bool operator==(const Int&, const Int&);
        bool operator!=(const Int&, const Int&);
        bool operator>=(const Int&, const Int&);
        bool operator<=(const Int&, const Int&);
        bool operator>(const Int&, const Int&);
        bool operator<(const Int&, const Int&);
        bool operator!(const Int&);
    }
}

void swap(Precision::Binary::Int&, Precision::Binary::Int&);

#endif
