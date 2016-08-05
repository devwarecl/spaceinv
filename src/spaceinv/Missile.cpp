
#include "Missile.hpp"

void Missile::update(const float seconds) {
    m_lifetime -= seconds;

    if (m_lifetime<=0.0f) {
        m_lifetime = 0.0;
        m_alive = false;
    }

    if (m_alive == false) {
        m_node->setRenderable(nullptr);
    } else {
        m_position += m_direction * m_speed * seconds;

        m_node->setMatrix(xe::translate(m_position));
    }
}


