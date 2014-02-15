#ifndef PRECISION_DEFAULT_INSTANTIATION__PACK__H__
#define PRECISION_DEFAULT_INSTANTIATION__PACK__H__

#include <vector>

namespace Precision{
    namespace Default_Type{
        struct image{
            static constexpr char set[10]
                {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        };
        using digit                         = char;
        using decimal                       = std::ptrdiff_t;
        constexpr decimal k_base            = 10;
        template <typename... Args>
        using container                     = std::vector<Args...>;
    }
}

#endif