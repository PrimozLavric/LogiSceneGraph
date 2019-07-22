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
  float x = rot.x, y = rot.y, z = rot.z, w = rot.w;
  float x2 = x + x, y2 = y + y, z2 = z + z;
  float xx = x * x2, xy = x * y2, xz = x * z2;
  float yy = y * y2, yz = y * z2, zz = z * z2;
  float wx = w * x2, wy = w * y2, wz = w * z2;

  float sx = scale.x, sy = scale.y, sz = scale.z;

  mat[0][0] = (1 - (yy + zz)) * sx;
  mat[0][1] = (xy + wz) * sx;
  mat[0][2] = (xz - wy) * sx;
  mat[0][3] = 0;

  mat[1][0] = (xy - wz) * sy;
  mat[1][1] = (1 - (xx + zz)) * sy;
  mat[1][2] = (yz + wx) * sy;
  mat[1][3] = 0;

  mat[2][0] = (xz + wy) * sz;
  mat[2][1] = (yz - wx) * sz;
  mat[2][2] = (1 - (xx + yy)) * sz;
  mat[2][3] = 0;

  mat[3][0] = pos.x;
  mat[3][1] = pos.y;
  mat[3][2] = pos.z;
  mat[3][3] = 1;
}

inline void decomposeMatrix(const glm::mat4x4& mat, glm::vec3& pos, glm::quat& rot, glm::vec3& scale) {
  static glm::vec3 skew;
  static glm::vec4 perspective;
  glm::decompose(mat, scale, rot, pos, skew, perspective);
}

} // namespace lsg

#endif // LSG_CORE_MATH_H