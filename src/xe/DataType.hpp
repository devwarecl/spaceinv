
#pragma once

#ifndef __xe_datatype__
#define __xe_datatype__

#include <iostream>
#include <cstdint>

namespace xe {
    enum class DataType {
        Unknown,
        UInt8,      UInt16, UInt32,
        Int8,       Int16,  Int32,
        Float16,    Float32 
    };

    template<typename Type>
    constexpr DataType getDataType() {return DataType::Unknown;}

    template<>
    constexpr DataType getDataType<std::int32_t>() {return DataType::Int32;}

    template<>
    constexpr DataType getDataType<float>() {return DataType::Float32;}

	std::size_t getSize(DataType dataType)  {
		switch (dataType) {
			case DataType::UInt8:
			case DataType::Int8:
				return 1;

			case DataType::UInt16:
			case DataType::Int16:
			case DataType::Float16:
				return 2;

			case DataType::UInt32:
			case DataType::Int32:
			case DataType::Float32:
				return 4;

			default:
				return 0;
		}
	}
}

#endif
