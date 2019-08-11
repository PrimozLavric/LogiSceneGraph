/**
 * Project LogiSceneGraph source code
 * Copyright (C) 2019 Lana Besevic
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

#include "lsg/components/OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace lsg {

OrthographicCamera::OrthographicCamera(Object& owner, const float xmag, const float ymag, const float far,
                                       const float near)
  : Camera("OrthographicCamera", owner), xmag_(xmag), ymag_(ymag), far_(far), near_(near), dirty_(true) {}

const glm::mat4x4& OrthographicCamera::projectionMatrix() {
  updateProjectionMatrix();
  return projection_matrix_;
}

float OrthographicCamera::xmag() const {
  return xmag_;
}

float OrthographicCamera::ymag() const {
  return ymag_;
}

float OrthographicCamera::farPlane() const {
  return far_;
}

float OrthographicCamera::nearPlane() const {
  return near_;
}

void OrthographicCamera::setXmag(float xmag) {
  xmag_ = xmag;
  dirty_ = true;
}

void OrthographicCamera::setYmag(float ymag) {
  ymag_ = ymag;
  dirty_ = true;
}

void OrthographicCamera::setFarPlane(float far) {
  far_ = far;
  dirty_ = true;
}

void OrthographicCamera::setNearPlane(float near) {
  near_ = near;
  dirty_ = true;
}

void OrthographicCamera::updateProjectionMatrix() {
  if (!dirty_) {
    return;
  }

  projection_matrix_[0][0] = 1.0f / xmag_;
  projection_matrix_[1][1] = 1.0f / ymag_;
  projection_matrix_[2][2] = 2.0f / (near_ - far_);
  projection_matrix_[3][2] = (far_ + near_) / (near_ - far_);

  dirty_ = false;
}

} // namespace lsg
