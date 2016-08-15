

#include "BdmModelPart.hpp"

void BdmModelPart::renderWith(xe::sg::Pipeline *renderer) {
    renderer->render(this);
}
