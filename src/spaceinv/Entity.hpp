
#pragma once

#ifndef __player__
#define __player__

#include "xe/sg/SceneNode.hpp"

class Scenario;

class Entity {
public:
	Entity() {}

	Entity(Scenario *scenario, xe::sg::SceneNode *node);

	~Entity() {}

	void move(const float distance);

	void move(const float distance, const xe::Vector3f &direction);

	void step(const float distance);

	void turn(const float angle);

	void fire();

	void syncNode();

protected:
	xe::Matrix4f getTranform();

private:
	Scenario *m_scenario = nullptr;

	xe::sg::SceneNode *m_node = nullptr;

	xe::Vector3f m_position = {0.0f, 0.0f, -8.0f};
	xe::Vector3f m_direction;
	xe::Vector3f m_up = {0.0f, 1.0f, 0.0f};
};

typedef std::unique_ptr<Entity> EntityPtr;

#endif
