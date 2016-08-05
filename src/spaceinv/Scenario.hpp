#pragma once

#include <list>

#include "Updatable.hpp"
#include "Missile.hpp"

class Scenario {
public:
    Scenario (xe::sg::SceneNode *node, xe::sg::Renderable *missileRenderable, xe::sg::Renderable *floorRenderable);

    void update(const float seconds);

    void spawnMissile(const xe::Vector3f &position, const xe::Vector3f &direction);

private:    
    xe::sg::SceneNode *m_node = nullptr;
    xe::sg::Renderable *m_missileRenderable = nullptr;
    xe::sg::Renderable *m_floorRenderable = nullptr;

    std::list<Updatable*> m_updatables;
    std::list<MissilePtr> m_missiles;
};
