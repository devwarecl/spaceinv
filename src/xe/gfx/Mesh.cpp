
#include "Mesh.hpp"

namespace xe { namespace gfx {
    bool Mesh::isIndexed() const {
        MeshFormat format = this->getFormat();

        for (const MeshAttrib attrib : format.attribs) {
            if (attrib.bufferType == BufferType::Index) {
                return true;
            }
        }

        return false;
    }
}}
