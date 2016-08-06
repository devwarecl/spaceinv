
#ifndef __floor__
#define __floor__

#include "xe/gfx/Material.hpp"
#include "xe/gfx/Mesh.hpp"
#include "xe/sg/Renderable.hpp"

class Floor : public xe::sg::Renderable {
public:
    explicit Floor(xe::gfx::UniformFormat *format, xe::gfx::Mesh *mesh, int count);
    ~Floor();

    virtual void renderWith(xe::sg::Pipeline *pipeline) override;

private:
    xe::gfx::MaterialPtr m_material;
    xe::gfx::Mesh *m_mesh = nullptr;
    int m_count = 0;
};

#endif
