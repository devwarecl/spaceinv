
#pragma once

#ifndef __xe_sg_scene_hpp__
#define __xe_sg_scene_hpp__

#include <memory>
#include "xe/Vector.hpp"
#include "xe/sg/SceneNode.hpp"

namespace xe { namespace sg {
    struct Scene {
        Vector4f backcolor = {0.2f, 0.2f, 0.2f, 1.0f};
        SceneNode rootNode;
    };

	typedef std::unique_ptr<Scene> ScenePtr;
}}

#endif
