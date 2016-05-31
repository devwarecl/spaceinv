
#pragma once

#ifndef __player__
#define __player__

#include "xe/sg/SceneNode.hpp"

class Player {
public:

	Player() {}
	explicit Player(xe::sg::SceneNode *node) : m_node(node) {
		assert(m_node);
	}

	~Player() {}

	void setTime(float time) {
		m_time = time;
	}

	void moveLeft();

	void moveRight();

	void moveForward();

	void moveBackward();

	void fire();

protected:
	xe::Matrix4f getTranform();

private:
	xe::sg::SceneNode *m_node = nullptr;
	xe::Vector3f m_position = {0.0f, 0.0f, 0.0f};
	float m_time = 0.0f;
};

#endif
