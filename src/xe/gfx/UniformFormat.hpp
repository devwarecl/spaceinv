
#pragma once

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"

namespace xe { namespace gfx { namespace gl3  {
	struct UniformDescriptor : public xe::Attrib {
		int location = -1;	//! Location
		int size = 0;		//! How many elements has the array

		size_t getSize() const {
			return size * xe::Attrib::getSize();
		}

		UniformDescriptor() {}

		UniformDescriptor(const std::string name_, size_t count_, xe::DataType type_, size_t size_=1) {
			name = name_;
			count = count_;
			type = type_;
			size = size_;
		}
	};
	
	typedef xe::DataFormat<UniformDescriptor> UniformFormat;
}}}
