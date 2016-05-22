
#pragma once

#ifndef __xe_sg_scenenode__
#define __xe_sg_scenenode__

#include <vector>

#include "xe/Matrix.hpp"
#include "xe/sg/Forward.hpp"

namespace xe { namespace sg {
    
    struct SceneNode {
        std::string name;
        Matrix4f transform = xe::identity<float, 4>();
        Renderable *renderable = nullptr;
		
        std::vector<SceneNode> childs;
    };
}}

#endif
