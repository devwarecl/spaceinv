
#include "Scenario.hpp"

#include "xe/sg/Generators.hpp"

Scenario::Scenario (xe::sg::SceneNode *node, xe::sg::Renderable *missileRenderable, xe::sg::Renderable *floorRenderable) {
    m_node = node;
    m_missileRenderable = missileRenderable;

    // auto shape = xe::sg::gencoords<float>(xe::sg::Plane{{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0}}, {10.0f, 10.0f}, {10, 10});
}

void Scenario::spawnMissile(const xe::Vector3f &position, const xe::Vector3f &direction) {
    auto missileNode = m_node->addChild()->setRenderable(m_missileRenderable);
    auto missile = new Missile(missileNode, position, direction);

    m_updatables.push_back(missile);
    m_missiles.emplace_back(missile);
}

void Scenario::update(const float seconds) {
    for (Updatable *updatable : m_updatables) {
        updatable->update(seconds);
    }
}
