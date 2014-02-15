#ifndef PRECISION_HEXADECIMAL_DEFAULT_TYPES_H__
#define PRECISION_HEXADECIMAL_DEFAULT_TYPES_H__

#include <cstddef>
#include <vector>

namespace Precision{
    namespace Hexadecimal{
        namespace Default_Type{
            struct image{
                static constexpr char set[16]
                    {'0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
            };
            using digit                         = char;
            using decimal                       = std::ptrdiff_t;
            constexpr decimal k_base            = 16;
            template <typename... Args>
            using container                     = std::vector<Args...>;
        }
    }
}

#endif