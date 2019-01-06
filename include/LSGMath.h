#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/matrix_decompose.hpp>

namespace lsg {

inline void composeMatrix(glm::mat4x4& mat, const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale) {
	mat = glm::mat4_cast(rot);

	// Local position.
	mat[3][0] += pos[0];
	mat[3][1] += pos[1];
	mat[3][2] += pos[2];

	// Scale.
	for (size_t i = 0; i < 3; i++) {
		mat[i][0] *= scale[0];
		mat[i][1] *= scale[1];
		mat[i][2] *= scale[2];
	}
}


inline void decomposeMatrix(const glm::mat4x4& mat, glm::vec3& pos, glm::quat& rot, glm::vec3& scale) {
	static glm::vec3 skew;
	static glm::vec4 perspective;
	glm::decompose(mat, scale, rot, pos, skew, perspective);
}

}
