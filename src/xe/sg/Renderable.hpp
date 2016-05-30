#pragma once

#ifndef __xe_sg_renderable_hpp__
#define __xe_sg_renderable_hpp__

#include "xe/sg/Forward.hpp"

namespace xe { namespace sg {
	class Renderable {
	public:
		virtual ~Renderable() {}
		virtual void renderWith(xe::sg::Pipeline *renderer) = 0;
	};
}}

#endif 
