
#include "Entity.hpp"
#include "Scenario.hpp"

#include "xe/Common.hpp"

static const xe::Vector3f s_initialDirection = {0.0f, 0.0f, 1.0f};

Entity::Entity(Scenario *scenario, xe::sg::SceneNode *node) : m_scenario(scenario), m_node(node) {
    assert(m_node);

    m_direction = s_initialDirection;
}

void Entity::move(const float distance) {
    this->move(distance, m_direction);
}

void Entity::move(const float distance, const xe::Vector3f &direction) {
    m_position += distance * direction;
}

void Entity::turn(const float angle) {
    xe::Matrix4f rotation = xe::rotate(angle, m_up);
    xe::Vector3f direction = xe::transform(rotation, m_direction);

    m_direction = direction;
}

void Entity::step(const float distance) {
    auto direction = xe::normalize(xe::cross(m_direction, m_up));
        
    this->move(distance, direction);
}

xe::Matrix4f Entity::getTranform() {
    xe::Matrix4f rotation = xe::identity<float, 4>();

    if (m_direction != s_initialDirection) {
        rotation = xe::rotate(
            std::acos(xe::dot(s_initialDirection, m_direction)),
            xe::cross(s_initialDirection, m_direction)
        );
    }

    xe::Matrix4f translation = xe::translate(m_position);

    return translation * rotation;
}

void Entity::syncNode() {
    m_node->transform = this->getTranform();
}

void Entity::fire() {
    m_scenario->spawnMissile(m_position + 1.0f * m_direction , m_direction);
}
