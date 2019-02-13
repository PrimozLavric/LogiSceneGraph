/**
 * Project LogiSceneGraph source code
 * Copyright (C) 2019 Primoz Lavric
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lsg/components/Transform.h"
#include "lsg/core/Object.h"
#include "lsg/core/Math.h"

namespace lsg {

Transform::Transform(Ref<Object> owner)
  : Component("Transform", owner), world_matrix_(1.0), world_matrix_dirty_(false), 
    loc_matrix_(1.0), loc_matrix_dirty_(false), loc_position_(), loc_rotation_(), loc_scale_(1.0f) {

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

  // When the parent changes mark the world matrix dirty.
  owner->setOnParentChangeCallback(Ref<Identifiable>(this), [this] (Ref<Object>) {
	  this->markWorldMatrixDirty();
  });
}

const glm::mat4x4& Transform::matrix() {
  if (loc_matrix_dirty_) {
	  loc_matrix_ = glm::mat4_cast(loc_rotation_);
	  for (size_t i = 0; i < 3; i++) {
		  loc_matrix_[i][i] *= loc_scale_[i];
		  loc_matrix_[3][i] = loc_position_[i];
	  }
  }

	return loc_matrix_;
}

const glm::mat4x4& Transform::worldMatrix() {
  if (world_matrix_dirty_) {
	  updateWorldMatrix();
  }

  return world_matrix_;
}

const glm::vec3& Transform::position() const {
	return loc_position_;
}

const glm::quat& Transform::rotation() const {
	return loc_rotation_;
}

glm::vec3 Transform::eulerRotation() const {
	return glm::eulerAngles(loc_rotation_);
}

const glm::vec3& Transform::scale() const {
	return loc_scale_;
}

void Transform::applyMatrix(const glm::mat4& mat) {
	loc_matrix_ = mat * matrix();
	decomposeMatrix(loc_matrix_, loc_position_, loc_rotation_, loc_scale_);
	markWorldMatrixDirty();
}

void Transform::applyQuaternion(const glm::quat& quaternion) {
	loc_rotation_ *= quaternion;
	markLocalMatrixDirty();
}

void Transform::setLocalMatrix(const glm::mat4& mat) {
	loc_matrix_ = mat;
	decomposeMatrix(loc_matrix_, loc_position_, loc_rotation_, loc_scale_);
	markWorldMatrixDirty();
}

void Transform::setRotation(const glm::quat& quaternion) {
	loc_rotation_ = quaternion;
	markLocalMatrixDirty();
}

void Transform::setScale(const glm::vec3& scale) {
	loc_scale_ = scale;
	markLocalMatrixDirty();
}

void Transform::setPosition(const glm::vec3& position) {
	loc_position_ = position;
	markLocalMatrixDirty();
}

void Transform::translateOnAxis(const glm::vec3& axis, const float distance) {
	const glm::vec3 loc_axis = loc_rotation_ * axis;
	setPosition(loc_position_ + (loc_axis * distance));
}

void Transform::translateX(const float distance) {
	const static glm::vec3 axis(1.0f, 0.0f, 0.0f);
	translateOnAxis(axis, distance);
}

void Transform::translateY(const float distance) {
	const static glm::vec3 axis(0.0f, 1.0f, 0.0f);
	translateOnAxis(axis, distance);
}

void Transform::translateZ(const float distance) {
	const static glm::vec3 axis(0.0f, 0.0f, 1.0f);
	translateOnAxis(axis, distance);
}

void Transform::rotateOnAxis(const glm::vec3& axis, const float angle) {
	const auto quaternion = glm::quat(axis * angle);
	loc_rotation_ *= quaternion;
	markLocalMatrixDirty();
}

void Transform::rotateX(const float angle) {
	const static glm::vec3 axis(1.0f, 0.0f, 0.0f);
  rotateOnAxis(axis, angle);
}

void Transform::rotateY(const float angle) {
	const static glm::vec3 axis(0.0f, 1.0f, 0.0f);
  rotateOnAxis(axis, angle);
}

void Transform::rotateZ(const float angle) {
	const static glm::vec3 axis(0.0f, 0.0f, 1.0f);
	rotateOnAxis(axis, angle);
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
	  world_matrix_ = transform->world_matrix_ * matrix();
  } else {
	  world_matrix_ = matrix();
  }

  world_matrix_dirty_ = false;
}

void Transform::markLocalMatrixDirty() {
	loc_matrix_dirty_ = true;
	markWorldMatrixDirty();
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
