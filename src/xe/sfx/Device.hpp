

#ifndef __xe_sfx_device_hpp__
#define __xe_sfx_device_hpp__

#include "xe/Vector.hpp"
#include "xe/Buffer.hpp"

namespace xe { namespace sfx { 
    
    struct Listener {
        xe::Vector3f position = {0.0f, 0.0f, 0.0f};
        xe::Vector3f velocity = {0.0f, 0.0f, 0.0f};
        
        struct {
            xe::Vector3f lookat = {0.0f, 0.0f, -1.0f};
            xe::Vector3f up = {0.0f, 1.0f, 0.0f};
        } orientation;
    };
    
    class Device {
    public:
        
        ~Device() {}
        
        virtual BufferPtr createBuffer() = 0;
        
        virtual void setListener(const Listener &listener) = 0;
        virtual Listener getListener() const = 0;
    };
}}

#endif
