
#include "Program.hpp"

#include <cassert>

namespace xe { namespace gfx {
    Program::~Program() {}

    void Program::fillUniformLocations(UniformFormat *uniformFormat) const {
        assert(uniformFormat);

        for (UniformDescriptor &desc : uniformFormat->attribs) {
            desc.location = this->getUniform(desc.name);
        }
    }
}}
