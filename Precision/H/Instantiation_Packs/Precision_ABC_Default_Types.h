#ifndef PRECISION_ABCDEF_DEFAULT_TYPES__H__
#define PRECISION_ABCDEF_DEFAULT_TYPES__H__

#include <cstddef>

namespace Precision{
    namespace ABC{
        namespace Default_Type{
            struct image{
                static constexpr char set[26]
                    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z'};
            };
            using digit                 = char;
            using decimal               = std::ptrdiff_t;
            constexpr decimal k_base    = 26;
        }
    }
}

#endif