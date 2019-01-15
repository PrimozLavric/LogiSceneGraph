#ifndef LSG_COMPONENTS_TRANSFORM_H
#define LSG_COMPONENTS_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "lsg/core/Component.h"

namespace lsg {

class Transform : public Component {
public:
  explicit Transform(Object* owner);

  /**
   * @brief Apply the given matrix to the object.
   * 
   * @param	matrix  Matrix to be applied.
   */
  void applyMatrix(const glm::mat4x4& matrix);

  /**
   * @brief Apply the quaternion rotation to the object.
   * 
   * @param	quaternion  Quaternion to be applied. 
   */
  void applyQuaternion(const glm::quat& quaternion);


  glm::mat4x4 matrix() const;

  glm::vec3 position() const;

  /**
   * @brief Set object position.
   * 
   * @param position  New position. 
   */
  void setPosition(const glm::vec3& position);

  /**
   * @brief Rotate an object along an axis in object space.
   *
   * @param	axis  Axis. The axis is assumed to be normalized.
   * @param	angle The angle to rotate in radians.
   */
  void rotateOnAxis(const glm::vec3& axis, float angle);

  /**
   * @brief Rotates around x axis in local space.
   * 
   * @param	angle The angle to rotate in radians.
   */
  void rotateX(float angle);

  /**
   * @brief Rotates around y axis in local space.
   *
   * @param angle The angle to rotate in radians.
   */
  void rotateY(float angle);

  /**
   * @brief Rotates around z axis in local space.
   *
   * @param	angle The angle to rotate in radians.
   */
  void rotateZ(float angle);

  void translateOnAxis(const glm::vec3& axis, float distance);

  void translateX(float distance);

  void translateY(float distance);

  void translateZ(float distance);

protected:
	void updateWorldMatrix();

	void markWorldMatrixDirty();

private:
	glm::mat4x4 world_matrix_;
	bool world_matrix_dirty_;
	glm::mat4x4 loc_matrix_;

	glm::vec3 loc_position_;
	glm::quat loc_rotation_;
	glm::vec3 loc_scale_;
};

}

#endif // LSG_COMPONENTS_TRANSFORM_H