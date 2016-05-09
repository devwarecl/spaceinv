
#pragma once

#ifndef __xe_traits__
#define __xe_traits__

#define XE_TRAITS(BasicType, DataTypeEnum)          \
    template<> struct Traits<BasicType> {           \
        typedef BasicType Type;                     \
        static const DataType Enum = DataTypeEnum;	\   
		static const int count = 1;					\
    }

namespace xe {
    template<typename BasicType> 
    struct Traits;

    XE_TRAITS(std::uint8_t , DataType::UInt8);
    XE_TRAITS(std::uint16_t, DataType::UInt16);
    XE_TRAITS(std::uint32_t, DataType::UInt32);
    XE_TRAITS(std::int8_t  , DataType::Int8);
    XE_TRAITS(std::int16_t , DataType::Int16);
    XE_TRAITS(std::int32_t , DataType::Int32);
    XE_TRAITS(float        , DataType::Float32); 
}

#endif
