
#include "Device.hpp"

namespace xe { namespace gfx {
	void Device::setUniform(const UniformFormat* format, void *uniforms) {
		assert(uniforms);
		assert(format->attribs.size() > 0);

		auto uniform = static_cast<std::uint8_t*>(uniforms);

		for (const UniformDescriptor &desc : format->attribs) {
			this->setUniform(desc, uniform);

			const size_t size = desc.getSize();

			uniform += size;
		}
	}
}}
