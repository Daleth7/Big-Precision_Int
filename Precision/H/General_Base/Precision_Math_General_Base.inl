namespace Precision{
    template <typename Integer_Type>
    bool palindrome(const Integer_Type& testee){
        typename Integer_Type::str_type test_string(testee.str().substr(1));
        const size_t max_s(test_string.size());
        for(size_t i(0); i < max_s/2; ++i)
            if(test_string[i] != test_string[max_s - i - 1])
                return false;
        return true;
    }

    template <typename Integer_Type>
    Integer_Type fibonacci(size_t* term_holder, size_t term){
        static Integer_Type toreturn(1), hold1(1), hold2(0);
        static size_t curr_term(2);
        if(term > 1)
            toreturn = 1, hold1 = 1, hold2 = 0, --term;
        curr_term += term;
        for(; term > 0; --term)
            hold2 = toreturn, toreturn += hold1, hold1 = hold2;
        if(term_holder != nullptr) *term_holder = curr_term;
        return toreturn;
    }

    template <typename Floating_Type>
    Floating_Type remainder(const Floating_Type& f, const Floating_Type& s)
        {return f.remainder(s);}
}