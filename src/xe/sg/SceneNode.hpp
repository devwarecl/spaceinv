
#pragma once

#ifndef __xe_sg_scenenode__
#define __xe_sg_scenenode__

#include <list>
#include <memory>

#include "xe/Matrix.hpp"
#include "xe/sg/Forward.hpp"

namespace xe { namespace sg {
	struct SceneNode;
	typedef std::unique_ptr<SceneNode> SceneNodePtr;
	
    struct SceneNode {
        std::string name;
        Renderable *renderable = nullptr;
		Matrix4f transform = xe::identity<float, 4>();
		
        std::list<SceneNodePtr> childs;

		SceneNode() {}
		SceneNode(const Matrix4f &transform_) : transform(transform_) {}
		SceneNode(Renderable *renderable_) : renderable(renderable_) {}
		SceneNode(Renderable *renderable_, const Matrix4f &transform_) : renderable(renderable_), transform(transform_) {}
    };
}}

#endif
