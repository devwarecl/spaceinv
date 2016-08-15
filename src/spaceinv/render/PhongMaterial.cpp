
#include "PhongMaterial.hpp"

PhongMaterial::PhongMaterial(xe::gfx::UniformFormat *format) : Material(format) {
    flags.enable(xe::gfx::Material::CullFace);
    flags.enable(xe::gfx::Material::DepthTest);
}
