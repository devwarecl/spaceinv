#pragma once

#ifndef __xe_dataformat__
#define __xe_dataformat__

#include <vector>
#include <string>
#include "xe/DataType.hpp"
#include "xe/Traits.hpp"

namespace xe {

    struct Attrib {
        std::string name;
        std::size_t dim = 1;
        DataType    type = DataType::Unknown;
        
        std::size_t getSize() const {
            return dim * xe::getSize(type);
        }
    };

    template<typename DataAttrib>
    struct DataFormat {

        typedef std::vector<DataAttrib> AttribVector;

        AttribVector attribs;
        
        DataFormat() {}
        DataFormat(const std::vector<DataAttrib> &attribs_) : attribs(attribs_) {}

        std::size_t getSize() const {
            std::size_t size = 0;

            for (const DataAttrib &attrib : attribs) {
                size += attrib.getSize();
            }

            return size;
        }
    };
}

#endif
