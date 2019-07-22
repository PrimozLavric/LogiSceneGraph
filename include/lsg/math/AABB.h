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

#ifndef LSG_MATH_AABB_H
#define LSG_MATH_AABB_H

#include <algorithm>
#include <glm/glm.hpp>
#include <ostream>

namespace lsg {

template <typename T>
class AABB {
 public:
  /**
   * @brief Initializes max point to minimum values and min point to maximum float values.
   */
  AABB();

  /**
   * @brief	Initializes min and max points with the given min and max.
   *
   * @param	min Minimum bounding box point.
   * @param	max Maximum bounding box point
   */
  AABB(const glm::tvec3<T>& min, const glm::tvec3<T>& max);

  /**
   * @brief   AABB conversion constructor.
   *
   * @tparam	U     Component type of other AABB
   * @param	  other Other AABB object.
   */
  template <typename U>
  explicit AABB(const AABB<U>& other);

  /**
   * @brief   AABB conversion assignment operator.
   *
   * @tparam	U   Component type of right hand side AABB
   * @param	  rhs Right hand side AABB
   * @return	Reference to this AABB.
   */
  template <typename U>
  AABB<T>& operator=(const AABB& rhs);

  /**
   * @brief   Computes intersection between this and the given bounding box.
   *
   * @param   aabb  Bounding box with which the intersection will be computed.
   * @return	Intersection bounding box.
   */
  AABB<T> intersect(const AABB<T>& aabb) const;

  /**
   * @brief   Returns AABB transformed with the given matrix.
   *
   * @param   matrix  Matrix that will be used to transform AABB.
   * @return  Transformed AABB.
   */
  AABB<T> transform(const glm::tmat4x4<T>& matrix) const;

  /**
   * @brief Expand bounding box to include the given point.
   *
   * @param point Point to be included.
   */
  void expand(const glm::tvec3<T>& point);

  /**
   * @brief Expand bounding box to include the given bounding box.
   *
   * @param	aabb  Bounding box to be included.
   */
  void expand(const AABB& aabb);

  /**
   * @brief	  Check if the bounding box is valid (if all components in min are lower than components in max).
   *
   * @return	True if the bounding box is valid.
   */
  bool valid() const;

  /**
   * @brief   Retrieve minimum bounding box point.
   *
   * @return	Minimum bounding box point.
   */
  const glm::tvec3<T>& min() const;

  /**
   * @brief   Retrieve maximum bounding box point.
   *
   * @return	Maximum bounding box point.
   */
  const glm::tvec3<T>& max() const;

  /**
   * @brief	  Compute center of the bounding box.
   *
   * @return	Center of the bounding box.
   */
  glm::tvec3<T> center() const;

  /**
   * @brief	  Compute volume of the bounding box.
   *
   * @return	Volume of the bounding box.
   */
  T volume() const;

  /**
   * @brief   Compute area of the bounding box.
   *
   * @return	Area of the bounding box.
   */
  T area() const;

  /**
   * @brief   Compute dimensions of the bounding box along each axis.
   *
   * @return	Dimensions of the bounding box.
   */
  glm::tvec3<T> dimensions() const;

  /**
   * @brief Reset bounding box.
   */
  void reset();

 private:
  /**
   * Minimum bounding box point.
   */
  glm::tvec3<T> min_;

  /**
   * Maximum bounding box point.
   */
  glm::tvec3<T> max_;
};

template <typename T>
template <typename U>
AABB<T>::AABB(const AABB<U>& other) : min_(other.min()), max_(other.max()) {}

template <typename T>
template <typename U>
AABB<T>& AABB<T>::operator=(const AABB& rhs) {
  min_ = rhs.min();
  max_ = rhs.max();
  return *this;
}

template <typename T>
AABB<T>::AABB() : min_(std::numeric_limits<T>::max()), max_(std::numeric_limits<T>::lowest()) {}

template <typename T>
AABB<T>::AABB(const glm::tvec3<T>& min, const glm::tvec3<T>& max) : min_(min), max_(max) {}

template <typename T>
AABB<T> AABB<T>::intersect(const AABB<T>& aabb) const {
  const glm::tvec3<T> min(std::max(aabb.min_.x, min_.x), std::max(aabb.min_.y, min_.y), std::max(aabb.min_.z, min_.z));
  const glm::tvec3<T> max(std::min(aabb.max_.x, max_.x), std::min(aabb.max_.y, max_.y), std::min(aabb.max_.z, max_.z));

  return {min, max};
}

template <typename T>
AABB<T> AABB<T>::transform(const glm::tmat4x4<T>& matrix) const {
  return AABB<T>(matrix * glm::vec4(min_, 1.0), matrix * glm::vec4(max_, 1.0));
}

template <typename T>
void AABB<T>::expand(const glm::tvec3<T>& point) {
  min_ = glm::tvec3<T>(std::min(point.x, min_.x), std::min(point.y, min_.y), std::min(point.z, min_.z));
  max_ = glm::tvec3<T>(std::max(point.x, max_.x), std::max(point.y, max_.y), std::max(point.z, max_.z));
}

template <typename T>
void AABB<T>::expand(const AABB& aabb) {
  expand(aabb.min_);
  expand(aabb.max_);
}

template <typename T>
bool AABB<T>::valid() const {
  return min_.x <= max_.x && min_.y <= max_.y && min_.z <= max_.z;
}

template <typename T>
const glm::tvec3<T>& AABB<T>::min() const {
  return min_;
}

template <typename T>
const glm::tvec3<T>& AABB<T>::max() const {
  return max_;
}

template <typename T>
glm::tvec3<T> AABB<T>::center() const {
  return (max_ + min_) * 0.5;
}

template <typename T>
T AABB<T>::volume() const {
  if (!valid()) {
    return 0;
  }

  return (max_.x - min_.x) * (max_.y - min_.y) * (max_.z - min_.z);
}

template <typename T>
T AABB<T>::area() const {
  if (!valid()) {
    return 0;
  }

  const glm::tvec3<T> d = max_ - min_;
  return (d.x * d.y + d.y * d.z + d.z * d.x) * 2.0f;
}

template <typename T>
glm::tvec3<T> AABB<T>::dimensions() const {
  return max_ - min_;
}

template <typename T>
void AABB<T>::reset() {
  min_ = glm::tvec3<T>(std::numeric_limits<float>::max());
  max_ = glm::tvec3<T>(std::numeric_limits<float>::lowest());
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const AABB<T>& aabb) {
  const glm::tvec3<T>& min = aabb.min();
  const glm::tvec3<T>& max = aabb.max();

  return stream << "[(" << min.x << ", " << min.y << ", " << min.z << "), (" << max.x << ", " << max.y << ", " << max.z
                << ")]";
}

} // namespace lsg

#endif // LSG_MATH_AABB_H