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

#ifndef LSG_MATH_RAY_H
#define LSG_MATH_RAY_H

#include <glm/glm.hpp>
#include <optional>

namespace lsg {

template <typename T>
class Ray {
 public:
  Ray(glm::tvec3<T> origin, const glm::tvec3<T>& dir);

  const glm::tvec3<T>& origin() const;

  const glm::tvec3<T>& dir() const;

  bool intersectAABB(const AABB<T>& aabb) const;

  std::optional<glm::tvec3<T>> intersectTriangle(const glm::tvec3<T>& a, const glm::tvec3<T>& b,
                                                 const glm::tvec3<T>& c) const;

 private:
  glm::tvec3<T> origin_;
  glm::tvec3<T> dir_;
};

template <typename T>
Ray<T>::Ray(glm::tvec3<T> origin, const glm::tvec3<T>& dir) : origin_(std::move(origin)), dir_(glm::normalize(dir)) {}

template <typename T>
const glm::tvec3<T>& Ray<T>::origin() const {
  return origin_;
}

template <typename T>
const glm::tvec3<T>& Ray<T>::dir() const {
  return dir_;
}

template <typename T>
bool Ray<T>::intersectAABB(const AABB<T>& aabb) const {
  const glm::tvec3<T>& min = aabb.min();
  const glm::tvec3<T>& max = aabb.max();

  float tmin;
  float tmax;

  if (dir_.x >= 0) {
    tmin = (min.x - origin_.x) / dir_.x;
    tmax = (max.x - origin_.x) / dir_.x;
  } else {
    tmin = (max.x - origin_.x) / dir_.x;
    tmax = (min.x - origin_.x) / dir_.x;
  }

  if (tmax < 0) {
    return false;
  }

  float tymin;
  float tymax;

  if (dir_.y >= 0) {
    tymin = (min.y - origin_.y) / dir_.y;
    tymax = (max.y - origin_.y) / dir_.y;
  } else {
    tymin = (max.y - origin_.y) / dir_.y;
    tymax = (min.y - origin_.y) / dir_.y;
  }

  if ((tmin > tymax) || (tymin > tmax)) {
    return false;
  }

  if (tymin > tmin) {
    tmin = tymin;
  }

  if (tymax < tmax) {
    tmax = tymax;
  }

  float tzmin;
  float tzmax;

  if (dir_.z >= 0) {
    tzmin = (min.z - origin_.z) / dir_.z;
    tzmax = (max.z - origin_.z) / dir_.z;
  } else {
    tzmin = (max.z - origin_.z) / dir_.z;
    tzmax = (min.z - origin_.z) / dir_.z;
  }

  return (tmin <= tzmax) && (tzmin <= tmax);
}

template <typename T>
std::optional<glm::tvec3<T>> Ray<T>::intersectTriangle(const glm::tvec3<T>& a, const glm::tvec3<T>& b,
                                                       const glm::tvec3<T>& c) const {
  glm::tvec3<T> edge1 = b - a;
  glm::tvec3<T> edge2 = c - a;
  glm::tvec3<T> normal = glm::cross(edge1, edge2);

  T DdN = glm::dot(dir_, normal);
  int16_t sign;

  if (DdN > 0) {
    sign = 1;
  } else if (DdN < 0) {
    sign = -1;
    DdN = -DdN;
  } else {
    return std::nullopt;
  }

  glm::tvec3<T> diff = origin_ - a;
  float DdQxE2 = sign * glm::dot(dir_, (glm::cross(diff, edge2)));

  if (DdQxE2 < 0) {
    return std::nullopt;
  }

  float DdE1xQ = sign * glm::dot(dir_, (glm::cross(edge1, diff)));

  if (DdE1xQ < 0) {
    return std::nullopt;
  }

  if (DdQxE2 + DdE1xQ > DdN) {
    return std::nullopt;
  }

  float QdN = -1 * sign * glm::dot(diff, normal);

  if (QdN < 0) {
    return std::nullopt;
  }

  return (QdN / DdN) * dir_ + origin_;
}

} // namespace lsg

#endif // LSG_MATH_RAY_H
