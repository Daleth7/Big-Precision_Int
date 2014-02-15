#ifndef OCTAL_BASE_DEFAULT_TYPES_H__
#define OCTAL_BASE_DEFAULT_TYPES_H__

#include <cstddef>

namespace Precision{
    namespace Octal{
        namespace Default_Type{
            struct image{
                static constexpr char set[8]
                    {'0', '1', '2', '3', '4', '5', '6', '7'};
            };
            using digit                 = char;
            using decimal               = std::ptrdiff_t;
            constexpr decimal k_base    = 8;
        }
    }
}

#endif