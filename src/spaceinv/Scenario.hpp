#pragma once

#include <list>

#include "Updatable.hpp"
#include "Missile.hpp"

class Scenario {
public:
	Scenario (xe::sg::SceneNode *node, xe::sg::Renderable *missileRenderable) {
		m_node = node;
		m_missileRenderable = missileRenderable;
	}

	void update(const float seconds) {
		for (Updatable *updatable : m_updatables) {
			updatable->update(seconds);
		}
	}

	void spawnMissile(const xe::Vector3f &position, const xe::Vector3f &direction) {
		auto missileNode = std::make_unique<xe::sg::SceneNode>(m_missileRenderable);
		auto missile = std::make_unique<Missile>(missileNode.get(), position, direction);

		m_node->childs.push_back(std::move(missileNode));

		m_updatables.push_back(missile.get());
		m_missiles.push_back(std::move(missile));
	}

private:	
	xe::sg::SceneNode *m_node = nullptr;
	xe::sg::Renderable *m_missileRenderable = nullptr;

	std::list<Updatable*> m_updatables;
	std::list<MissilePtr> m_missiles;
};
