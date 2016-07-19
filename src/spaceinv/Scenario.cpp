
#include "Scenario.hpp"

void Scenario::spawnMissile(const xe::Vector3f &position, const xe::Vector3f &direction) {
    auto missileNode = std::make_unique<xe::sg::SceneNode>(m_missileRenderable);
    auto missile = std::make_unique<Missile>(missileNode.get(), position, direction);

    m_node->childs.push_back(std::move(missileNode));

    m_updatables.push_back(missile.get());
    m_missiles.push_back(std::move(missile));
}

void Scenario::update(const float seconds) {
    for (Updatable *updatable : m_updatables) {
        updatable->update(seconds);
    }
}
