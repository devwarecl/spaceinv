
#pragma once

#include <memory>

#include "Updatable.hpp"

#include "xe/Vector.hpp"
#include "xe/Matrix.hpp"
#include "xe/Boundary.hpp"
#include "xe/sg/SceneNode.hpp"

class Missile : public Updatable {
public:
    Missile() {}

    Missile(xe::sg::SceneNode *node, const xe::Vector3f &position, const xe::Vector3f &direction) 
        : m_node(node), m_position(position), m_direction(xe::normalize(direction)), m_alive(true) {}

    virtual void update(const float seconds) override;

    bool alive() const {
        return m_lifetime > 0.0f;
    }

public:
    xe::Boxf m_box = {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}};
    xe::Vector3f m_position = {0.0f, 0.0f, 0.0f};
    xe::Vector3f m_direction = {0.0f, 0.0f, 0.0f};
    xe::sg::SceneNode *m_node = nullptr;

    bool m_alive = false;
    float m_lifetime = 3.0f;

    const float m_speed = 100.0f;
};

typedef std::unique_ptr<Missile> MissilePtr;
