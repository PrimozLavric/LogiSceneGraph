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

#include "lsg/components/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace lsg {

PerspectiveCamera::PerspectiveCamera(const Ref<Object>& owner, const float fov, const float near, const float aspect_ratio, const float far)
  : Camera("PerspectiveCamera", owner), aspect_ratio_(aspect_ratio), fov_(fov), far_(far), near_(near), dirty_(true) {}

const glm::mat4x4& PerspectiveCamera::projectionMatrix() {
	updateProjectionMatrix();
	return projection_matrix_;
}

float PerspectiveCamera::aspectRatio() const {
	return aspect_ratio_;
}

float PerspectiveCamera::fov() const {
	return fov_;
}

float PerspectiveCamera::far() const {
	return far_;
}

float PerspectiveCamera::near() const {
	return near_;
}

void PerspectiveCamera::setAspectRatio(const float aspect_ratio) {
	aspect_ratio_ = aspect_ratio;
	dirty_ = true;
}

void PerspectiveCamera::setFov(const float fov) {
	fov_ = fov;
	dirty_ = true;
}

void PerspectiveCamera::setFar(const float far) {
	far_ = far;
	dirty_ = true;
}

void PerspectiveCamera::setNear(const float near) {
	near_ = near;
	dirty_ = true;
}

void PerspectiveCamera::updateProjectionMatrix() {
	if (!dirty_) {
		return;
	}

	if (far_ == std::numeric_limits<float>::max()) {
		projection_matrix_ = glm::infinitePerspective(fov_, aspect_ratio_, near_);
	} else {
		projection_matrix_ = glm::perspective(fov_, aspect_ratio_, near_, far_);
	}

	dirty_ = false;
}


}
