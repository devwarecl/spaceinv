
#include "Scenario.hpp"

Scenario::Scenario (xe::sg::SceneNode *node, xe::sg::Renderable *missileRenderable, xe::sg::Renderable *floorRenderable) {
    m_node = node;
    m_missileRenderable = missileRenderable;
    m_floorRenderable = floorRenderable;

    m_node->addChild()->setRenderable(m_floorRenderable);
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
