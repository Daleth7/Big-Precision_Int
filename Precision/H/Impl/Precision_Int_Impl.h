#ifndef __PRECISION_INT_IMPL_H
#define __PRECISION_INT_IMPL_H

#ifdef GENERAL_BASE_

#include "Precision_INT_BASE.h"

#include <string>

struct _10toChar{
    char operator()(short s)const
        {return s + '0';}
};

struct _Charto10{
    short operator()(char ch)const
        {return ch - '0';}
};

struct Impl_Int_
    : public INT_BASE_<
        std::string,
        char,
        short,
        10,
        '0',
        _Charto10,
        _10toChar
    >
{
    Impl_Int_(const std::string& s)
        : INT_BASE_(s)
    {}
    Impl_Int_(const std::string& s, Sign i)
        : INT_BASE_(s, i)
    {}
    Impl_Int_(lli i=0)
        : INT_BASE_(i)
    {}
    Impl_Int_(const INT_BASE_& b)
        : INT_BASE_(b)
    {}

    Impl_Int_(const Impl_Int_&)             =default;
    Impl_Int_(Impl_Int_&&)                  =default;
    Impl_Int_& operator=(const Impl_Int_&)  =default;
    Impl_Int_& operator=(Impl_Int_&&)       =default;
    ~Impl_Int_()                            =default;
};

inline Impl_Int_ operator+(Impl_Int_ f, const Impl_Int_& s)
    {return f += s;}
inline Impl_Int_ operator-(Impl_Int_ f, const Impl_Int_& s)
    {return f -= s;}
inline Impl_Int_ operator*(Impl_Int_ f, const Impl_Int_& s)
    {return f *= s;}
inline Impl_Int_ operator/(Impl_Int_ f, const Impl_Int_& s)
    {return f /= s;}
inline Impl_Int_ operator%(Impl_Int_ f, const Impl_Int_& s)
    {return f %= s;}

inline Impl_Int_ operator&(Impl_Int_ f, const Impl_Int_& s)
    {return f &= s;}
inline Impl_Int_ operator|(Impl_Int_ f, const Impl_Int_& s)
    {return f |= s;}
inline Impl_Int_ operator^(Impl_Int_ f, const Impl_Int_& s)
    {return f ^= s;}
inline Impl_Int_ operator>>(Impl_Int_ f, const Impl_Int_& s)
    {return f >>= s;}
inline Impl_Int_ operator<<(Impl_Int_ f, const Impl_Int_& s)
    {return f <<= s;}

inline bool operator==(const Impl_Int_& f, const Impl_Int_& s)
    {return (f.compare(s) == 0);}
inline bool operator!=(const Impl_Int_& f, const Impl_Int_& s)
    {return (f.compare(s) != 0);}
inline bool operator>=(const Impl_Int_& f, const Impl_Int_& s)
    {return (f.compare(s) >= 0);}
inline bool operator<=(const Impl_Int_& f, const Impl_Int_& s)
    {return (f.compare(s) <= 0);}
inline bool operator>(const Impl_Int_& f, const Impl_Int_& s)
    {return (f.compare(s) > 0);}
inline bool operator<(const Impl_Int_& f, const Impl_Int_& s)
    {return (f.compare(s) < 0);}
inline bool operator!(const Impl_Int_& t)
    {return t == 0;}

#else

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
        using digit10   = short;
        using Sign      = short;
        using Size_Type = unsigned long long int;
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
        Str sci_note(Size_Type=k_display_prec)const;
        Str sci_note_w_spaces(Size_Type=k_display_prec)const;
        Impl_Int_ magnitude()const;
        Size_Type count_digits()const;
        short compare(const Impl_Int_&)const;
        Impl_Int_ operator-()const;
        Impl_Int_ operator~()const;
        bool even()const;
        bool odd()const;
//Other modifiers
        void shift(lli);
        void sign(Sign);
        void negate();
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

        static constexpr digit      k_0bit  = '0';
        static constexpr digit10    k_limit = 10;
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

#endif  //End GENERAL_BASE_

#endif  //End Include guard