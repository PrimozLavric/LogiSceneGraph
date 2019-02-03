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

#ifndef LSG_COMPONENTS_ORTHOGRAPHIC_CAMERA_H
#define LSG_COMPONENTS_ORTHOGRAPHIC_CAMERA_H

#include <glm/glm.hpp>

#include "Camera.h"

namespace lsg {

class OrthographicCamera : public Camera {
public:

  /**
	 * @brief	Initializes orthographic camera parameters with the given values.
	 *
	 * @param	owner	Owner of the camera component.
	 * @param	xmag	Horizontal magnification of the view.
	 * @param	ymag	Vertical magnification of the view.
	 * @param	far	  Distance to the far clipping plane.
	 * @param	near	Distance to the near clipping plane.
	 */
	OrthographicCamera(const Ref<Object>& owner, float xmag, float ymag, float far, float near);

  /**
	 * @brief	  Retrieve projection matrix.
	 *
	 * @return	Projection matrix.
	 */
	const glm::mat4x4& projectionMatrix() override;

  /**
	 * @brief	  Retrieve horizontal magnification of the view.
	 *
	 * @return	Horizontal magnification of the view.
	 */
	float xmag() const;

  /**
	 * @brief	  Retrieve vertical magnification of the view.
	 *
	 * @return	Vertical magnification of the view.
	 */
	float ymag() const;

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
	 * @brief	Set horizontal magnification of the view.
	 *
	 * @param	xmag	Horizontal magnification of the view to be set.
	 */
	void setXmag(float xmag);

  /**
	 * @brief	Set vertical magnification of the view.
	 *
	 * @param	ymag	Vertical magnification of the view to be set.
	 */
	void setYmag(float ymag);

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
   * Horizontal magnification of the view.
   */
	float xmag_;

  /**
   * Vertical magnification of the view.
   */
	float ymag_;

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

#endif // LSG_COMPONENTS_ORTHOGRAPHIC_CAMERA_H
