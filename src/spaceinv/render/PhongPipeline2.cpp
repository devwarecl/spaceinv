
#include "PhongPipeline2.hpp"

#include <xe/FileUtil.hpp>

namespace spaceinv {

    PhongPipeline2::PhongPipeline2(xe::gfx::Device *device) {
        assert(device);
        
        m_device = device;

        // inicializar las matrices por defecto
        m_proj = xe::identity<float, 4>();
        m_view = xe::identity<float, 4>();
        m_world = xe::identity<float, 4>();

        // programa shader
        std::string vshader = xe::FileUtil::loadTextFile("assets/shaders/vertex.glsl");
        std::string fshader = xe::FileUtil::loadTextFile("assets/shaders/fragment.glsl");

        std::list<xe::gfx::ShaderSource> sources = {
            {xe::gfx::ShaderType::Vertex, vshader},
            {xe::gfx::ShaderType::Fragment, fshader}
        };

        m_program = m_device->createProgram(sources);

        m_device->setProgram(m_program.get());
    }

    PhongPipeline2::~PhongPipeline2() {}




}
