
#include "Player.hpp"

#include "xe/Common.hpp"

static const xe::Vector3f s_initialDirection = {0.0f, 0.0f, 1.0f};

//
//void Player::moveLeft() {
//	m_position -= xe::Vector3f(1.0f, 0.0f, 0.0f) * m_time;
//	m_node->transform = this->getTranform();
//}
//
//void Player::moveRight() {
//	m_position += xe::Vector3f(1.0f, 0.0f, 0.0f) * m_time;
//	m_node->transform = this->getTranform();
//}

Player::Player(xe::sg::SceneNode *world, xe::sg::SceneNode *node) : m_world(world), m_node(node) {
	assert(m_node);

	m_direction = s_initialDirection;
}

void Player::move(const float distancePerSecond) {
	m_position += distancePerSecond * m_direction * m_time;
}

void Player::turn(const float anglePerSecond) {
	xe::Matrix4f rotation = xe::rotate(m_time * anglePerSecond, m_up);
	xe::Vector3f direction = xe::transform(rotation, m_direction);

	m_direction = direction;
}

xe::Matrix4f Player::getTranform() {

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

void Player::updateNode() {
	m_node->transform = this->getTranform();
}

void Player::fire() {

}
