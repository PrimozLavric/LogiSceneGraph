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

#include <glm/vec3.hpp>
#include <ostream>

namespace lsg {

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
	AABB(const glm::vec3& min, const glm::vec3& max);

  /**
	 * @brief   Computes intersection between this and the given bounding box.
	 * 
	 * @param   aabb  Bounding box with which the intersection will be computed. 
	 * @return	Intersection bounding box.
	 */
	AABB intersect(const AABB& aabb) const;

  /**
	 * @brief Expand bounding box to include the given point.
	 * 
	 * @param point Point to be included.
	 */
	void expand(const glm::vec3& point);

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
	const glm::vec3& min() const;

  /**
	 * @brief   Retrieve maximum bounding box point.
	 * 
	 * @return	Maximum bounding box point.
	 */
	const glm::vec3& max() const;

  /**
	 * @brief	  Compute center of the bounding box.
	 * 
	 * @return	Center of the bounding box.
	 */
	glm::vec3 center() const;

  /**
   * @brief	  Compute volume of the bounding box.
   * 
   * @return	Volume of the bounding box.
   */
  float volume() const;

  /**
   * @brief   Compute area of the bounding box.
   * 
   * @return	Area of the bounding box.
   */
  float area() const;

  /**
   * @brief   Compute dimensions of the bounding box along each axis.
   *
   * @return	Dimensions of the bounding box.
   */
  glm::vec3 dimensions() const;

  /**
   * @brief Reset bounding box.
   */
  void reset();

private:
  /**
	 * Minimum bounding box point.
	 */
	glm::vec3 min_;

	/**
   * Maximum bounding box point.
   */
	glm::vec3 max_;
};

std::ostream& operator<<(std::ostream& stream, const AABB& aabb);

}

#endif // LSG_MATH_AABB_H