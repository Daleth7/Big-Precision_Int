#include "Precision_UInt.h"

namespace Precision{
//Constructors and destructor
    UInt::UInt(ulli inInt)
        : m_base(0)
    { //Manually convert using stringstream to avoid
        //  data loss when converting ulli to lli
        std::stringstream catalyst("");
        catalyst << inInt;
        m_base = Int(catalyst.str());
    }

    UInt::UInt(const diglist& inImage)
        : m_base(inImage)
    {
        if(m_base.sign() < 0)
            m_base = 0;
    }

    UInt::UInt(const Int& inInt)
        : m_base(inInt)
    {
        if(m_base.sign() < 0)
            m_base = 0;
    }

    UInt::UInt(Int&& inInt)
        : m_base(std::move(inInt))
    {
        if(m_base.sign() < 0)
            m_base = 0;
    }
}