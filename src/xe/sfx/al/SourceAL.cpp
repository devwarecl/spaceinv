
#include "SourceAL.hpp"

namespace xe { namespace sfx { 

    SourceAL::SourceAL() {
        ALuint source;
        
        alGenSources(1, &source);
    }
    
    SourceAL::~SourceAL() {
        
    }
    
    SourceDesc SourceAL::getDesc() const {
        
    }
    
    void SourceAL::setDesc(const SourceDesc &desc)  {
        
    }
    
    Buffer* SourceAL::getBuffer() const {
        
    }
    
    void SourceAL::setBuffer(Buffer* buffer) {
        
    }
}}
