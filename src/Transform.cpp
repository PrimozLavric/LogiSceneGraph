#include "Transform.h"
#include "LSGMath.h"

namespace lsg {

Transform::Transform(Object* owner)
  : Component("Transform", owner), world_matrix_(), loc_matrix_(),
    loc_position_(), loc_rotation_(), loc_scale_(1.0f)  {}

void Transform::applyMatrix(const glm::mat4x4& matrix) {
	loc_matrix_ = matrix * loc_matrix_;
	decomposeMatrix(loc_matrix_, loc_position_, loc_rotation_, loc_scale_);
}

void Transform::applyQuaternion(const glm::quat& quat) {
	loc_rotation_ *= quat;
	loc_matrix_ = glm::mat4_cast(quat) * loc_matrix_;
}

glm::mat4x4 Transform::matrix() const {
  return loc_matrix_;
}

glm::vec3 Transform::position() const {
	return loc_position_;
}

void Transform::setPosition(const glm::vec3& position) {
	loc_position_ = position;
	loc_matrix_[3][0] = position[0];
	loc_matrix_[3][1] = position[1];
	loc_matrix_[3][2] = position[2];
}

void Transform::rotateX(const float angle) {
	const static glm::vec3 axis(1.0f, 0.0f, 0.0f);
  rotateOnAxis(angle, axis);
}

void Transform::rotateY(const float angle) {
	const static glm::vec3 axis(0.0f, 1.0f, 0.0f);
  rotateOnAxis(angle, axis);
}

void Transform::rotateZ(const float angle) {
	const static glm::vec3 axis(0.0f, 0.0f, 1.0f);
	rotateOnAxis(angle, axis);
}

void Transform::rotateOnAxis(const float angle, const glm::vec3& axis) {
  const glm::quat quaternion = glm::quat(axis * angle);
	loc_rotation_ *= quaternion;
	loc_matrix_ = glm::mat4_cast(quaternion) * loc_matrix_;
}

}
