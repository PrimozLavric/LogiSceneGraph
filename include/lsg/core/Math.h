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

#ifndef LSG_CORE_MATH_H
#define LSG_CORE_MATH_H

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

#endif  // LSG_CORE_MATH_H