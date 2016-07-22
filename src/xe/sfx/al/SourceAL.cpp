
#include "SourceAL.hpp"

namespace xe { namespace sfx { namespace al {

    SourceAL::SourceAL() {
        ALuint source;
        
        alGenSources(1, &source);
    }
    
    SourceAL::~SourceAL() {
        
    }
    
    SourceDesc SourceAL::getDesc() const {
        return SourceDesc();
    }
    
    void SourceAL::setDesc(const SourceDesc &desc)  {
        
    }
    
    Buffer* SourceAL::getBuffer() const {
        return nullptr;
    }
    
    void SourceAL::setBuffer(Buffer* buffer) {
        
    }
}}}
