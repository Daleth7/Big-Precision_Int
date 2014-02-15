//Explicitly define functions here to allow implicit conversion
namespace Precision{
    inline Int operator+(Int f, const Int& s)
        {return f += s;}
    inline Int operator-(Int f, const Int& s)
        {return f -= s;}
    inline Int operator*(Int f, const Int& s)
        {return f *= s;}
    inline Int operator/(Int f, const Int& s)
        {return f /= s;}
    inline Int operator%(Int f, const Int& s)
        {return f %= s;}

    inline Int operator&(Int f, const Int& s)
        {return f &= s;}
    inline Int operator|(Int f, const Int& s)
        {return f |= s;}
    inline Int operator^(Int f, const Int& s)
        {return f ^= s;}
    inline Int operator<<(Int f, const Int& s)
        {return f <<= s;}
    inline Int operator>>(Int f, const Int& s)
        {return f >>= s;}

    inline bool operator!(const Int& testee)
        {return testee.compare(0) == 0;}
    inline bool operator==(const Int& f, const Int& s)
        {return f.compare(s) == 0;}
    inline bool operator!=(const Int& f, const Int& s)
        {return f.compare(s) != 0;}
    inline bool operator<=(const Int& f, const Int& s)
        {return f.compare(s) <= 0;}
    inline bool operator>=(const Int& f, const Int& s)
        {return f.compare(s) >= 0;}
    inline bool operator<(const Int& f, const Int& s)
        {return f.compare(s) < 0;}
    inline bool operator>(const Int& f, const Int& s)
        {return f.compare(s) > 0;}



    inline UInt operator+(UInt f, const UInt& s)
        {return f += s;}
    inline UInt operator-(UInt f, const UInt& s)
        {return f -= s;}
    inline UInt operator*(UInt f, const UInt& s)
        {return f *= s;}
    inline UInt operator/(UInt f, const UInt& s)
        {return f /= s;}
    inline UInt operator%(UInt f, const UInt& s)
        {return f %= s;}

    inline UInt operator&(UInt f, const UInt& s)
        {return f &= s;}
    inline UInt operator|(UInt f, const UInt& s)
        {return f |= s;}
    inline UInt operator^(UInt f, const UInt& s)
        {return f ^= s;}
    inline UInt operator<<(UInt f, const UInt& s)
        {return f <<= s;}
    inline UInt operator>>(UInt f, const UInt& s)
        {return f >>= s;}

    inline bool operator!(const UInt& testee)
        {return testee.compare(0) == 0;}
    inline bool operator==(const UInt& f, const UInt& s)
        {return f.compare(s) == 0;}
    inline bool operator!=(const UInt& f, const UInt& s)
        {return f.compare(s) != 0;}
    inline bool operator<=(const UInt& f, const UInt& s)
        {return f.compare(s) <= 0;}
    inline bool operator>=(const UInt& f, const UInt& s)
        {return f.compare(s) >= 0;}
    inline bool operator<(const UInt& f, const UInt& s)
        {return f.compare(s) < 0;}
    inline bool operator>(const UInt& f, const UInt& s)
        {return f.compare(s) > 0;}



    inline Float operator+(Float f, const Float& s)
        {return f += s;}
    inline Float operator-(Float f, const Float& s)
        {return f -= s;}
    inline Float operator*(Float f, const Float& s)
        {return f *= s;}
    inline Float operator/(Float f, const Float& s)
        {return f /= s;}
    inline Float operator%(Float f, const Float& s)
        {return f %= s;}
    inline Float operator^(Float f, const Float& s)
        {return f ^= s;}

    inline bool operator!(const Float& testee)
        {return testee.compare(0) == 0;}
    inline bool operator==(const Float& f, const Float& s)
        {return f.compare(s) == 0;}
    inline bool operator!=(const Float& f, const Float& s)
        {return f.compare(s) != 0;}
    inline bool operator<=(const Float& f, const Float& s)
        {return f.compare(s) <= 0;}
    inline bool operator>=(const Float& f, const Float& s)
        {return f.compare(s) >= 0;}
    inline bool operator<(const Float& f, const Float& s)
        {return f.compare(s) < 0;}
    inline bool operator>(const Float& f, const Float& s)
        {return f.compare(s) > 0;}



    inline UFloat operator+(UFloat f, const UFloat& s)
        {return f += s;}
    inline UFloat operator-(UFloat f, const UFloat& s)
        {return f -= s;}
    inline UFloat operator*(UFloat f, const UFloat& s)
        {return f *= s;}
    inline UFloat operator/(UFloat f, const UFloat& s)
        {return f /= s;}
    inline UFloat operator%(UFloat f, const UFloat& s)
        {return f %= s;}
    inline UFloat operator^(UFloat f, const UFloat& s)
        {return f ^= s;}

    inline bool operator!(const UFloat& testee)
        {return testee.compare(0) == 0;}
    inline bool operator==(const UFloat& f, const UFloat& s)
        {return f.compare(s) == 0;}
    inline bool operator!=(const UFloat& f, const UFloat& s)
        {return f.compare(s) != 0;}
    inline bool operator<=(const UFloat& f, const UFloat& s)
        {return f.compare(s) <= 0;}
    inline bool operator>=(const UFloat& f, const UFloat& s)
        {return f.compare(s) >= 0;}
    inline bool operator<(const UFloat& f, const UFloat& s)
        {return f.compare(s) < 0;}
    inline bool operator>(const UFloat& f, const UFloat& s)
        {return f.compare(s) > 0;}



    inline Fract operator+(Fract f, const Fract& s)
        {return f += s;}
    inline Fract operator-(Fract f, const Fract& s)
        {return f -= s;}
    inline Fract operator*(Fract f, const Fract& s)
        {return f *= s;}
    inline Fract operator/(Fract f, const Fract& s)
        {return f /= s;}
    inline Fract operator%(Fract f, const Fract& s)
        {return f %= s;}
    inline Fract operator^(Fract f, const Fract& s)
        {return f ^= s;}

    inline bool operator!(const Fract& testee)
        {return testee.compare(0) == 0;}
    inline bool operator==(const Fract& f, const Fract& s)
        {return f.compare(s) == 0;}
    inline bool operator!=(const Fract& f, const Fract& s)
        {return f.compare(s) != 0;}
    inline bool operator<=(const Fract& f, const Fract& s)
        {return f.compare(s) <= 0;}
    inline bool operator>=(const Fract& f, const Fract& s)
        {return f.compare(s) >= 0;}
    inline bool operator<(const Fract& f, const Fract& s)
        {return f.compare(s) < 0;}
    inline bool operator>(const Fract& f, const Fract& s)
        {return f.compare(s) > 0;}



    inline UFract operator+(UFract f, const UFract& s)
        {return f += s;}
    inline UFract operator-(UFract f, const UFract& s)
        {return f -= s;}
    inline UFract operator*(UFract f, const UFract& s)
        {return f *= s;}
    inline UFract operator/(UFract f, const UFract& s)
        {return f /= s;}
    inline UFract operator%(UFract f, const UFract& s)
        {return f %= s;}
    inline UFract operator^(UFract f, const UFract& s)
        {return f ^= s;}

    inline bool operator!(const UFract& testee)
        {return testee.compare(0) == 0;}
    inline bool operator==(const UFract& f, const UFract& s)
        {return f.compare(s) == 0;}
    inline bool operator!=(const UFract& f, const UFract& s)
        {return f.compare(s) != 0;}
    inline bool operator<=(const UFract& f, const UFract& s)
        {return f.compare(s) <= 0;}
    inline bool operator>=(const UFract& f, const UFract& s)
        {return f.compare(s) >= 0;}
    inline bool operator<(const UFract& f, const UFract& s)
        {return f.compare(s) < 0;}
    inline bool operator>(const UFract& f, const UFract& s)
        {return f.compare(s) > 0;}
}