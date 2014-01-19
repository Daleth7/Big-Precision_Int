namespace Precision{
//Read-only
    DIG_TEMPL
    type DIG_INST_::value()const
        {return m_value;}
    DIG_TEMPL
    DIG_INST_::operator type()const
        {return m_value;}

    DIG_TEMPL
    type10 DIG_INST_::decimal()const
        {return m_ntodec(m_value);}
    DIG_TEMPL
    DIG_INST_::operator type10()const
        {return this->decimal();}

    DIG_TEMPL
    const decton& DIG_INST_::converter_10toN()const
        {return m_decton;}
    DIG_TEMPL
    const ntodec& DIG_INST_::converter_Nto10()const
        {return m_ntodec;}

    DIG_TEMPL
    DIG_INST_ DIG_INST_::operator~()const
        {return ~m_value;}

    DIG_TEMPL
    type DIG_INST_::carry()const{
        type toreturn;
        if(m_value < k_0)
    }

//Modifiers
    DIG_TEMPL
    DIG_INST_& DIG_INST_::assign(type);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::assign(type10);

//If (val >= N) or (val <= -N), reduce the
//  magnitude of val, so (-N < val < N)
    DIG_TEMPL
    DIG_INST_& DIG_INST_::reduce();
    
//Arithmetic
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator+=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator-=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator*=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator/=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator%=(const DIG_INST_&);

//Bitwise
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator&=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator|=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator^=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator>>=(const DIG_INST_&);
    DIG_TEMPL
    DIG_INST_& DIG_INST_::operator<<=(const DIG_INST_&);

//Constructors and Destructor
    DIG_TEMPL
    DIG_INST_::digit_class(const type&);
    DIG_TEMPL
    DIG_INST_::digit_class(const type10&);
}

DIG_TEMPL_
Precision::DIG_INST_ operator+(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator-(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator*(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator/(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator%(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);

DIG_TEMPL_
Precision::DIG_INST_ operator&(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator|(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator^(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator>>(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
Precision::DIG_INST_ operator<<(
    const Precision::DIG_INST_&, const Precision::DIG_INST_&);

DIG_TEMPL_
bool operator!(const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator==(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator!=(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator>=(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator<=(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator>(const Precision::DIG_INST_&, const Precision::DIG_INST_&);
DIG_TEMPL_
bool operator<(const Precision::DIG_INST_&, const Precision::DIG_INST_&);