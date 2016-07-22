
#pragma once

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"

namespace xe { namespace gfx {
    struct UniformDescriptor : public xe::Attrib {
        int location = -1;    //! Location
        size_t count = 0;        //! How many elements has the array

        size_t getSize() const {
            return count * xe::Attrib::getSize();
        }

        UniformDescriptor() {}

        UniformDescriptor(const std::string name_, size_t dim_, xe::DataType type_, size_t count_=1) {
            name = name_;
            dim = dim_;
            type = type_;
            count = count_;
        }
    };
    
    typedef xe::DataFormat<UniformDescriptor> UniformFormat;
}}
