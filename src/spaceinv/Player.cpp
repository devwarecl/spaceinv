
#include "Player.hpp"

#include "xe/Common.hpp"

void Player::moveLeft() {
	m_position -= xe::Vector3f(1.0f, 0.0f, 0.0f) * m_time;
	m_node->transform = this->getTranform();
}

void Player::moveRight() {
	m_position += xe::Vector3f(1.0f, 0.0f, 0.0f) * m_time;
	m_node->transform = this->getTranform();
}

void Player::moveForward() {
	m_position += m_direction * m_time;
	m_node->transform = this->getTranform();
}

void Player::moveBackward() {
	m_position -= m_direction * m_time;
	m_node->transform = this->getTranform();
}

void Player::turnLeft() {
	const float speed = 60.0f;

	xe::Matrix4f rotation = xe::rotate(m_time * xe::rad(speed), m_up);
	xe::Vector3f direction = xe::transform(rotation, m_direction);

	m_direction = direction;
}

void Player::turnRight() {
	const float speed = -60.0f;

	xe::Matrix4f rotation = xe::rotate(m_time * xe::rad(speed), m_up);
	xe::Vector3f direction = xe::transform(rotation, m_direction);

	m_direction = direction;
}

xe::Matrix4f Player::getTranform() {
	xe::Vector3f direction = {0.0f, 0.0f, 1.0f};

	xe::Vector3f axis = xe::cross(direction, m_direction);
	float angle = std::acos(xe::dot(direction, m_direction));

	return /*xe::rotate(angle, axis) * */xe::translate(m_position);
}

void Player::fire() {

}
