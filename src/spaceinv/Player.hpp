
#pragma once

#ifndef __player__
#define __player__

#include "xe/sg/SceneNode.hpp"

class Player {
public:
	Player() {}

	Player(xe::sg::SceneNode *world, xe::sg::SceneNode *node);

	~Player() {}

	void setTime(float time) {
		m_time = time;
	}

	void move(const float distancePerSecond);

	void turn(const float anglePerSecond);

	void fire();

	void updateNode();

protected:
	xe::Matrix4f getTranform();

private:
	xe::sg::SceneNode *m_world = nullptr;
	xe::sg::SceneNode *m_node = nullptr;

	xe::Vector3f m_position = {0.0f, 0.0f, 0.0f};
	xe::Vector3f m_direction;
	xe::Vector3f m_up = {0.0f, 1.0f, 0.0f};

	float m_time = 0.0f;
};

#endif
