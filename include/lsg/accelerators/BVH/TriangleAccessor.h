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

#ifndef LSG_RESOURCES_TRIANGLE_ACCESSOR_H
#define LSG_RESOURCES_TRIANGLE_ACCESSOR_H

#include <glm/glm.hpp>

namespace lsg {
namespace bvh {

/**
 * @brief	  Triangle that contains references to its vertices.
 * 
 * @tparam	T Type of the vertex components.
 */
template <typename T>
struct Triangle {
  /**
   * @brief Initializes triangle references.
   * 
   * @param a Vertex a. 
   * @param	b Vertex b.
   * @param	c Vertex c.
   */
  Triangle(const glm::tvec3<T>& a, const glm::tvec3<T>& b, const glm::tvec3<T>& c);

  /**
   * @brief   Retrieve vertex on the give index (a - 0, b - 1, c- 2).
   * 
   * @param   index Vertex index. 
   * @return	Vertex.
   */
  const glm::vec3<T>& operator[](size_t index) {
	  return *(&a + index);
  }

  /**
   * Triangle vertices.
   */
  const glm::tvec3<T>& a;
  const glm::tvec3<T>& b;
  const glm::tvec3<T>& c;
};

/**
 * @brief	  Triangle accessor interface.
 * 
 * @tparam	T Type of triangle vertex components.
 */
template <typename T>
class TriangleAccessor {
public:
  /**
	 * @brief   Retrieve triangle on the given index.
	 * 
	 * @param   index Index of the triangle. 
	 * @return	Triangle.
	 */
	virtual Triangle getTriangle(size_t index) const = 0;

  /**
	 * @brief	  Get number of triangles.
	 * 
	 * @return	Number of triangles.
	 */
	virtual size_t count() const = 0;

  /**
	 * @brief   Retrieve triangle on the given index.
	 * 
	 * @param	  index Index of the triangle. 
	 * @return	Triangle.
	 */
	Triangle operator[](size_t index);

  /**
	 * @brief This is an abstract class.
	 */
	virtual ~TriangleAccessor() = default;
};

template <typename T>
Triangle<T>::Triangle(const glm::tvec3<T>& a, const glm::tvec3<T>& b, const glm::tvec3<T>& c): a(a),
                                                                                               b(b),
                                                                                               c(c) {}

template <typename T>
Triangle TriangleAccessor<T>::operator[](size_t index) {
	return getTriangle();
}

}
}


#endif  // LSG_RESOURCES_TRIANGLE_ACCESSOR_H
