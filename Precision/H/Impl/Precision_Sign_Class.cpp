#include "Precision_Sign_Class.h"

namespace Precision{
//Read-only
    sign_class::signed_type sign_class::value()const
        {return m_positive ? 1 : -1;}
    bool sign_class::positive()const
        {return m_positive;}
    bool sign_class::negative()const
        {return !m_positive;}
    sign_class::operator signed_type()const
        {return this->value();}

//Modifiers
    void sign_class::flip()
        {m_positive = !m_positive;}
        //Just another name for flip
    void sign_class::negate()
        {this->flip();}
    void sign_class::assign(signed_type n)
        {m_positive = n < 0 ? false : true;}
    void sign_class::make_positive()
        {m_positive = true;}
    void sign_class::make_negative()
        {m_positive = false;}

//Constructors and Destructor
    sign_class::sign_class(signed_type n)
        : m_positive(n < 0 ? false : true)
    {}
}