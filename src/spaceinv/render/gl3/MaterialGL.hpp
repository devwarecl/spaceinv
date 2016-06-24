
#pragma once

#ifndef __gl3_material__
#define __gl3_material__

#include "GL.hpp"
#include "xe/DataFormat.hpp"
#include "xe/Vector.hpp"

namespace gl3 {

    typedef xe::DataFormat<xe::Attrib> MaterialFormat;

	enum class FaceMode {
		Point,
		Line,
		Triangle
	};

    struct MaterialGL {
        bool depthTest = true;
        bool cullFace = true;
		FaceMode faceMode = FaceMode::Triangle;

        xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        xe::Vector4f diffuse = {0.8f, 0.8f, 0.8f, 1.0f};
        xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};
        xe::Vector4f emissive = {0.0f, 0.0f, 0.0f, 1.0f};
		
        float shininess = 0.0f;
    };
}

#endif
