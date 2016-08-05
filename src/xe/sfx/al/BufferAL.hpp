
#include <AL/al.h>
#include "xe/Buffer.hpp"

namespace xe { namespace sfx { namespace al {
    
    class BufferAL : public Buffer {
    public:
        BufferAL();
        
        ~BufferAL();
        
        ALuint getId() const {
            return m_id;
        }
        
        virtual std::size_t getSize() const override;

        virtual void read(void* destination, const int size = 0, const int offset = 0, const int destination_offset = 0) const override;

        virtual void write(const void *source, const int size = 0, const int offset = 0, const int source_offset = 0) override;
        
    private:
        ALuint m_id;
    };
    
}}}
