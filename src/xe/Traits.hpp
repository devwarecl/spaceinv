
#pragma once

#ifndef __xe_traits__
#define __xe_traits__

#include "xe/DataType.hpp"

namespace xe {
    template<typename Type_> 
    struct Traits {
        typedef Type_ Type;
        static const DataType Enum = xe::getDataType<Type_>();
        static const int count = 1;
    };
}

#endif
