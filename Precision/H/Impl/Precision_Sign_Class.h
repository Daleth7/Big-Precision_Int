#ifndef SIGN_CLASS_DEFINITION_H__
#define SIGN_CLASS_DEFINITION_H__

namespace Precision{
    class sign_class{
        public:
    //Type Aliases
            using signed_type   = signed short;

    //Read-only
            signed_type value()const;
            bool positive()const;
            bool negative()const;
            operator signed_type()const;

    //Modifiers
            void flip();
                //Just another name for flip
            void negate();
            void assign(signed_type);
            void make_positive();
            void make_negative();

    //Constructors and Destructor
            sign_class(signed_type);
            sign_class()                                = default;
            sign_class(const sign_class&)               = default;
            sign_class(sign_class&&)                    = default;
            sign_class& operator=(const sign_class&)    = default;
            sign_class& operator=(sign_class&&)         = default;
            ~sign_class()                               = default;
        private:
            bool m_positive;
    };
}

#endif