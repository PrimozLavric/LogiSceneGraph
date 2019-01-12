#include "lsg/components/Transform.h"
#include "lsg/core/Object.h"
#include "lsg/core/Math.h"

namespace lsg {

Transform::Transform(Object* owner)
  : Component("Transform", owner), world_matrix_(), world_matrix_dirty_(false), 
    loc_matrix_(), loc_position_(), loc_rotation_(), loc_scale_(1.0f) {

  // Traverse ancestors.
  owner->traverseUpExcl([this](const Ref<Object> object) {
	  const auto transform = object->getComponent<Transform>();

    // Check if the ancestor has transform component.
    if (transform) {
      if (transform->world_matrix_dirty_) {
		    this->markWorldMatrixDirty();
      } else {
		    world_matrix_ = world_matrix_ * loc_matrix_;
      }

		  return false;
    }

	  return true;
  });
}

void Transform::applyMatrix(const glm::mat4x4& matrix) {
	loc_matrix_ = matrix * loc_matrix_;
	decomposeMatrix(loc_matrix_, loc_position_, loc_rotation_, loc_scale_);
	markWorldMatrixDirty();
}

void Transform::applyQuaternion(const glm::quat& quat) {
	loc_rotation_ *= quat;
	loc_matrix_ = glm::mat4_cast(quat) * loc_matrix_;
	markWorldMatrixDirty();
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
	markWorldMatrixDirty();
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
  const auto quaternion = glm::quat(axis * angle);
	loc_rotation_ *= quaternion;
	loc_matrix_ = glm::mat4_cast(quaternion) * loc_matrix_;
	markWorldMatrixDirty();
}

void Transform::updateWorldMatrix() {
  // Do not update world matrix if not dirty.
  if (!world_matrix_dirty_) {
	  return;
  }

  Ref<Transform> transform;
  // Find first ancestor with transform.
  owner_->traverseUpExcl([this, &transform](const Ref<Object> object) {
	  transform = object->getComponent<Transform>();
	  return !static_cast<bool>(transform);
  });

  // Update ancestor transform and compute the world matrix.
  if (transform) {
	  transform->updateWorldMatrix();
	  world_matrix_ = transform->world_matrix_ * loc_matrix_;
  } else {
	  world_matrix_ = loc_matrix_;
  }

  world_matrix_dirty_ = false;
}

void Transform::markWorldMatrixDirty() {
  // Don't do anything if the matrix is already marked as dirty.
  if (world_matrix_dirty_) {
	  return;
  }

	world_matrix_dirty_ = true;
  // Mark all child objects world matrices as dirty.
	owner_->traverseDownExcl([](const Ref<Object> object) {
	  const auto transform = object->getComponent<Transform>();
    if (transform) {
		  transform->world_matrix_dirty_ = true;
    }

    // Descend.
	  return true;
	});
}

}
