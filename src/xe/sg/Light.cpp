
#include "Light.hpp"

#include "xe/sg/Pipeline.hpp"

namespace xe { namespace sg {
    void Light::renderWith(Pipeline *pipeline) {
        pipeline->render(this);
    }
}}
