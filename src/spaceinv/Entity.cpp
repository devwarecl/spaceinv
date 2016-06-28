
#include "Entity.hpp"

#include "xe/Common.hpp"

static const xe::Vector3f s_initialDirection = {0.0f, 0.0f, 1.0f};

Entity::Entity(xe::sg::SceneNode *world, xe::sg::SceneNode *node) : m_world(world), m_node(node) {
	assert(m_node);

	m_direction = s_initialDirection;
}

void Entity::move(const float distancePerSecond) {
	this->move(distancePerSecond, m_direction);
}

void Entity::move(const float distancePerSecond, const xe::Vector3f &direction) {
	m_position += distancePerSecond * direction * m_time;
}

void Entity::turn(const float anglePerSecond) {
	xe::Matrix4f rotation = xe::rotate(m_time * anglePerSecond, m_up);
	xe::Vector3f direction = xe::transform(rotation, m_direction);

	m_direction = direction;
}

void Entity::step(const float distancePerSecond) {
	auto direction = xe::normalize(xe::cross(m_direction, m_up));
		
	this->move(distancePerSecond, direction);
}

xe::Matrix4f Entity::getTranform() {
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

void Entity::updateNode() {
	m_node->transform = this->getTranform();
}

void Entity::fire() {

}
