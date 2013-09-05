#include <vector>

namespace Precision{
    template <typename OutIter>
    void Erato_Sieve(unsigned long long int max, OutIter dest){
        const unsigned long long int init_prime(2);
        std::vector<bool> flags((max-init_prime), true);

        size_t init(0);
        while(init < flags.size()){
            size_t iter(init), gap(init + init_prime);

            while((iter += gap) < flags.size())
                flags[iter] = false;
            
            while(!flags[++init] && init < flags.size());
        }
        for(size_t i(0); i < flags.size(); ++i){
            if(flags[i])
                *(dest++) = (i + init_prime);
        }
    }
}