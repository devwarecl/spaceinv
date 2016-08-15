
#pragma once

#ifndef __spaceinv_render_model_hpp__
#define __spaceinv_render_model_hpp__

#include "xe/sg/Geometry.hpp"
#include "xe/Box.hpp"
#include "xe/gfx/Mesh.hpp"

class SubModel {
public:
    SubModel(xe::gfx::Mesh *mesh, const std::size_t coordIndex);
    
    size_t getVertexCount() const;
    
    xe::Boxf getBox() const;
    
private:
    std::size_t m_coordIndex = 0;
    xe::gfx::Mesh *m_mesh = nullptr;
};

class Model {
public:
    virtual ~Model() {}

    virtual SubModel* getFrame(const std::size_t frameIndex) = 0;
    
    virtual const SubModel* getFrame(const std::size_t frameIndex) const = 0;
    
    virtual std::size_t getFrameIndex() const = 0;
    
    virtual void setFrameIndex(const std::size_t frameIndex) = 0;
    
private:
    
};

#endif
