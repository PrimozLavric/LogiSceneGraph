#ifndef LSG_COMPONENTS_TRANSFORM_H
#define LSG_COMPONENTS_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "lsg/core/Component.h"
#include "lsg/core/Shared.h"

namespace lsg {

class Transform : public Component {
public:

  /**
   * @brief Initialize transform based on the owner.
   * 
   * @param	owner Owner of the transform component.
   */
  explicit Transform(Ref<Object> owner);

  /**
   * @brief   Retrieve local transform matrix.
   *
   * @return	Local transform matrix.
   */
  const glm::mat4x4& matrix();

  /**
   * @brief   Retrieve world transform matrix.
   *
   * @return	World transform matrix.
   */
  const glm::mat4x4& worldMatrix();

  /**
   * @brief	  Retrieve object position in object space.
   *
   * @return	Position in object space.
   */
  const glm::vec3& position() const;

  /**
   * @brief   Retrieve object rotation in object space
   * 
   * @return	Rotation in object space.
   */
  const glm::quat& rotation() const;

  /**
   * @brief	  Retrieve euler rotation in object space.
   * 
   * @return	Euler rotation in object space.
   */
  glm::vec3 eulerRotation() const;

  /**
   * @brief   Retrieve the object local scale.
   * 
   * @return	Object local scale.
   */
  const glm::vec3& scale() const;

  /**
   * @brief Apply the given matrix to the object.
   * 
   * @param	mat  Matrix to be applied.
   */
  void applyMatrix(const glm::mat4& mat);

  /**
   * @brief Apply the quaternion rotation to the object.
   * 
   * @param	quaternion  Quaternion to be applied. 
   */
  void applyQuaternion(const glm::quat& quaternion);

  /**
   * @brief Set object rotation.
   * 
   * @param	quaternion  Quaternion specifying object rotation.
   */
  void setRotation(const glm::quat& quaternion);

  /**
   * @brief Set object local scale.
   * 
   * @param	scale Scale to be set.
   */
  void setScale(const glm::vec3& scale);

  /**
   * @brief Set object position.
   * 
   * @param position  New position. 
   */
  void setPosition(const glm::vec3& position);

  /**
   * @brief Translate the object by distance along an axis in object space.
   *
   * @param axis      Normalized vector in object space.
   * @param	distance  The distance to translate.
   */
  void translateOnAxis(const glm::vec3& axis, float distance);

  /**
   * @brief Translate the object by distance along x axis in object space.
   *
   * @param	distance  The distance to translate.
   */
  void translateX(float distance);

  /**
   * @brief Translate the object by distance along y axis in object space.
   *
   * @param	distance  The distance to translate.
   */
  void translateY(float distance);

  /**
   * @brief Translate the object by distance along z axis in object space.
   *
   * @param	distance  The distance to translate.
   */
  void translateZ(float distance);

  /**
   * @brief Rotate an object along an axis in object space.
   *
   * @param	axis  Normalized vector in object space. 
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

  /**
   * @brief Update object world matrix.
   */
  void updateWorldMatrix();

protected:

	void markLocalMatrixDirty();

	void markWorldMatrixDirty();

private:
	glm::mat4x4 world_matrix_;
	bool world_matrix_dirty_;
	glm::mat4x4 loc_matrix_;
	bool loc_matrix_dirty_;

	glm::vec3 loc_position_;
	glm::quat loc_rotation_;
	glm::vec3 loc_scale_;
};

}

#endif // LSG_COMPONENTS_TRANSFORM_H