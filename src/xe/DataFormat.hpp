#pragma once

#ifndef __xe_dataformat__
#define __xe_dataformat__

#include <array>
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

        template<typename Type>
        Attrib make(const std::string &name) {
            return {name, 1, Traits<Type>::Enum};
        }
    };

    template<typename DataAttrib, std::size_t AttribCount>
    struct DataFormat {
        std::array<DataAttrib, AttribCount> attribs;
        
        DataFormat() {}
        DataFormat(const std::array<DataAttrib, AttribCount> &attribs_) : attribs(attribs_) {}

        std::size_t getSize() const {
            std::size_t size = 0;

            for (const DataAttrib &attrib : attribs) {
                size += attrib.getSize();
            }

            return size;
        }

        constexpr std::size_t getCount() const {
            return AttribCount;
        }
    };
}

#endif
