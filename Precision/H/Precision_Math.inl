#include <vector>
#include <stdexcept>

namespace Precision{
    template <class _Precision_Type_>
    _Precision_Type_ Sqrt(const _Precision_Type_& base, size_t prec){
        if(base.sign() < 0) throw std::domain_error("Sqrt of negative number.");
        else if(base == 0 || base == 1) return base;
    //Uses Babylonian method:
    //  http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
    //      #Babylonian_method
        _Precision_Type_ toreturn(base/2);
        while(prec-- > 0)
            toreturn = (toreturn + base/toreturn)/2;
        return toreturn;
    }
    template <typename OutIter>
    void Erato_Sieve(OutIter dest, size_t max){
        const size_t init_prime(2);
        static std::vector<bool> flags((max-init_prime), true);
        static bool already_filled(false);

        if(!already_filled && max != flags.size()){
            flags.resize(max);
            size_t init(0);
            while(init < flags.size()){
                size_t iter(init), gap(init + init_prime);

                while((iter += gap) < flags.size())
                    flags[iter] = false;
                
                while(!flags[++init] && init < flags.size());
            }
            already_filled = true;
        }
        for(size_t i(0); i < flags.size(); ++i){
            if(flags[i])
                *(dest++) = (i + init_prime);
        }
    }
}