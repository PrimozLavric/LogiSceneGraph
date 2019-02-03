#include "lsg/math/AABB.h"
#include <limits>
#include <algorithm>

namespace lsg {

AABB::AABB()
	: min_(std::numeric_limits<float>::max()),
	  max_(std::numeric_limits<float>::lowest()) {}


AABB::AABB(const glm::vec3& min, const glm::vec3& max)
	: min_(min),
	  max_(max) {}

AABB AABB::intersect(const AABB& aabb) const {
	const glm::vec3 min(std::max(aabb.min_.x, min_.x), std::max(aabb.min_.y, min_.y), std::max(aabb.min_.z, min_.z));
	const glm::vec3 max(std::min(aabb.max_.x, max_.x), std::min(aabb.max_.y, max_.y), std::min(aabb.max_.z, max_.z));

	return { min, max };
}

void AABB::expand(const glm::vec3& point) {
	min_ = glm::vec3(std::min(point.x, min_.x), std::min(point.y, min_.y), std::min(point.z, min_.z));
	max_ = glm::vec3(std::max(point.x, max_.x), std::max(point.y, max_.y), std::max(point.z, max_.z));
}


void AABB::expand(const AABB& aabb) {
	expand(aabb.min_);
	expand(aabb.max_);
}

bool AABB::valid() const {
	return min_.x <= max_.x && min_.y <= max_.y && min_.z <= max_.z;
}

const glm::vec3& AABB::min() const {
	return min_;
}

const glm::vec3& AABB::max() const {
	return max_;
}

glm::vec3 AABB::center() const {
	return (max_ + min_) / 2.0f;
}

float AABB::volume() const {
  if (!valid()) {
    return 0.0f;
  }

  return (max_.x - min_.x) * (max_.y - min_.y) * (max_.z - min_.z);
}

float AABB::area() const {
  if (!valid()) {
    return 0.0f;
  }

  const glm::vec3 d = max_ - min_;
  return (d.x * d.y + d.y * d.z + d.z * d.x) * 2.0f;
}

glm::vec3 AABB::dimensions() const {
	return max_ - min_;
}

void AABB::reset() {
	min_ = glm::vec3(std::numeric_limits<float>::max());
	max_ = glm::vec3(std::numeric_limits<float>::lowest());
}

std::ostream& operator<<(std::ostream& stream, const AABB& aabb) {
  const glm::vec3& min = aabb.min();
  const glm::vec3& max = aabb.max();

  return stream << "[(" << min.x << ", " << min.y << ", " << min.z
    << "), (" << max.x << ", " << max.y << ", " << max.z << ")]";
}

}
