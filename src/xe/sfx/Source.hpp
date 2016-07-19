
#ifndef __xe_sfx_source_hpp__
#define __xe_sfx_source_hpp__

#include "xe/Vector.hpp"
#include "xe/Buffer.hpp"

namespace xe { namespace sfx { 
    
    struct SourceDesc {
        float pitch = 1.0;
        float gain = 1.0;
        xe::Vector3f position;
        xe::Vector3f velocity;
        bool looping = false;
    };
    
    class Source {
    public:
        virtual ~Source() {}
        
        virtual SourceDesc getDesc() const = 0;
        virtual void setDesc(const SourceDesc &desc) = 0;
        
        virtual Buffer* getBuffer() const = 0;
        
        virtual void setBuffer(Buffer* buffer) = 0;
    };
}}

#endif

