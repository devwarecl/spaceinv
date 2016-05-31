
#include "Player.hpp"

void Player::moveLeft() {
	m_position -= xe::Vector3f(1.0f, 0.0f, 0.0f) * m_time;
	m_node->transform = this->getTranform();
}

void Player::moveRight() {
	m_position += xe::Vector3f(1.0f, 0.0f, 0.0f) * m_time;
	m_node->transform = this->getTranform();
}

void Player::moveForward() {
	m_position += xe::Vector3f(0.0f, 0.0f, -1.0f) * m_time;
	m_node->transform = this->getTranform();
}

void Player::moveBackward() {
	m_position -= xe::Vector3f(0.0f, 0.0f, -1.0f) * m_time;
	m_node->transform = this->getTranform();
}

xe::Matrix4f Player::getTranform() {
	return xe::translate(m_position);
}

void Player::fire() {

}
