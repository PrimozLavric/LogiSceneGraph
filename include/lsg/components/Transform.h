#ifndef LSG_COMPONENTS_TRANSFORM_H
#define LSG_COMPONENTS_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "lsg/core/Component.h"

namespace lsg {

class Transform : public Component {
public:
  explicit Transform(Object* owner);

  void applyMatrix(const glm::mat4x4& matrix);

  void applyQuaternion(const glm::quat& quat);

  glm::mat4x4 matrix() const;

  glm::vec3 position() const;

  void setPosition(const glm::vec3& position);

  void rotateX(float angle);

  void rotateY(float angle);

  void rotateZ(float angle);

  void rotateOnAxis(float angle, const glm::vec3& axis);

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