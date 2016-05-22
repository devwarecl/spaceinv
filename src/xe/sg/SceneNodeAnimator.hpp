
#pragma once

#ifndef __xe_sg_scenenodeanimator__
#define __xe_sg_scenenodeanimator__

#include <memory>
#include "xe/sg/SceneNode.hpp"

namespace xe { namespace sg {

    struct SceneNodeAnimator {
        SceneNode *sceneNode = nullptr;

        virtual void update(float seconds) = 0;
    };

	typedef std::unique_ptr<SceneNodeAnimator> SceneNodeAnimatorPtr;
}}

#endif	// __EXENG_SCENEGRAPH_SCENENODEANIMATOR_HPP__
