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

#ifndef LSG_COMPONENTS_PERSPECTIVE_CAMERA_H
#define LSG_COMPONENTS_PERSPECTIVE_CAMERA_H

#include <glm/glm.hpp>

#include "Camera.h"

namespace lsg {

class PerspectiveCamera : public Camera {
public:

  /**
	 * @brief	Initializes perspective camera parameters with the given values.
	 *
	 * @param	owner	        Owner of the camera component.
	 * @param	fov	          Field of view.
	 * @param	near	        Distance to the near clipping plane.
	 * @param	aspect_ratio  Aspect ratio.
	 * @param	far	          Distance to the far clipping plane.
	 */
	PerspectiveCamera(const Ref<Object>& owner, float fov, float near, float aspect_ratio = 1.0f, float far = std::numeric_limits<float>::max());

  /**
	 * @brief	  Retrieve projection matrix.
	 *
	 * @return	Projection matrix.
	 */
	const glm::mat4x4& projectionMatrix() override;

  /**
	 * @brief	  Retrieve aspect ratio.
	 *
	 * @return	Aspect ratio.
	 */
	float aspectRatio() const;

  /**
	 * @brief	  Retrieve field of view.
	 *
	 * @return	Field of view.
	 */
	float fov() const;

  /**
	 * @brief	  Retrieve distance to the far clipping plane.
	 *
	 * @return	Distance to the far clipping plane.
	 */
	float far() const;

  /**
	 * @brief	  Retrieve distance to the near clipping plane.
	 *
	 * @return	Distance to the near clipping plane.
	 */
	float near() const;

  /**
	 * @brief	Set aspect ratio.
	 *
	 * @param	aspect_ratio	Aspect ratio to be set.
	 */
	void setAspectRatio(float aspect_ratio);

  /**
	 * @brief	Set field of view.
	 *
	 * @param	fov Field of view to be set.
	 */
	void setFov(float fov);

  /**
	 * @brief	Set distance to the far clipping plane.
	 *
	 * @param	far	Distance to the far clipping plane to be set.
	 */
	void setFar(float far);

  /**
	 * @brief	Set distance to the near clipping plane.
	 *
	 * @param	near	Distance to the near clipping plane to be set.
	 */
	void setNear(float near);

  /**
	 * @brief	Update projection matrix.
	 */
	void updateProjectionMatrix();

private:
  /**
   * Aspect ratio.
   */
	float aspect_ratio_;

  /**
   * Field of view.
   */
	float fov_;

  /**
   * Distance to the far clipping plane.
   */
	float far_;

  /**
   * Distance to the near clipping plane.
   */
	float near_;

  /**
   * Projection matrix.
   */
	glm::mat4x4 projection_matrix_;

  /**
   * Flag that indicates the projection matrix needs to be updated.
   */
	bool dirty_;

};

}

#endif // LSG_COMPONENTS_PERSPECTIVE_CAMERA_H