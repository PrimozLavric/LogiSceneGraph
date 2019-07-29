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

#include <functional>
#include <glm/glm.hpp>

namespace lsg {

/**
 * @brief	  Triangle that contains references to its vertices.
 *
 * @tparam	T Type of the vertex components.
 */
template <typename T>
class Triangle {
 public:
  /**
   * @brief Initializes Triangle with vertex retrieval function.
   *
   * @param	get_vertex_fn Function used to retrieve vertices.
   */
  explicit Triangle(T& a, T& b, T& c) : vertex_data_({a, b, c}) {}

  /**
   * @brief   Retrieve first vertex of the triangle.
   *
   * @return	First triangle vertex.
   */
  const T& a() const {
    return vertex_data_[0u];
  }

  /**
   * @brief   Retrieve second vertex of the triangle.
   *
   * @return	Second triangle vertex.
   */
  const T& b() const {
    return vertex_data_[1u];
  }

  /**
   * @brief   Retrieve third vertex of the triangle.
   *
   * @return	Third triangle vertex.
   */
  const T& c() const {
    return vertex_data_[2u];
  }

  /**
   * @brief   Retrieve vertex on the give index (a - 0, b - 1, c - 2).
   *
   * @param   index Vertex index.
   * @return	Vertex.
   */
  const T& operator[](size_t index) const {
    return vertex_data_[index];
  }

 private:
  std::array<std::reference_wrapper<T>, 3> vertex_data_;
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
  virtual Triangle<T> operator[](size_t index) const = 0;

  /**
   * @brief This is an abstract class.
   */
  virtual ~TriangleAccessor() = default;
};

} // namespace lsg

#endif // LSG_RESOURCES_TRIANGLE_ACCESSOR_H
