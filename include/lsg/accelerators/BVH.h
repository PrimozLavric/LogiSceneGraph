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

#ifndef LSG_ACCELERATORS_SBVH_NODE_H
#define LSG_ACCELERATORS_SBVH_NODE_H
#include "lsg/math/AABB.h"
#include <vector>
#include <glm/vec2.hpp>

namespace lsg {

class BVH {
public:
  /**
   * BVH Node.
   */
	struct Node {
    
		Node(const AABB& bounds, bool is_leaf);

    /**
     * Node bounds.
     */
	  AABB bounds;

    /**
     * True if node is a leaf.
     */
	  bool is_leaf;

	  union {
		  /**
		   * Indices of child nodes (if inner node).
		   */
		  glm::uvec2 child_indices;

		  /**
		   * Primitive indices range (if leaf node)
		   */
		  glm::uvec2 indices_range;
	  };
	};

  /**
	 * @brief 
	 *
	 * @param	nodes	
	 * @param	prim_indices	
	 */
	BVH(std::vector<Node> nodes, std::vector<uint32_t> prim_indices);

  /**
	 * @brief 
	 *
	 * @param	nodes	
	 * @param	prim_indices	
	 */
	BVH(std::vector<Node>&& nodes, std::vector<uint32_t>&& prim_indices);

  /**
	 * @brief 
	 *
	 * @return	
	 */
	const std::vector<Node>& getNodes() const;

  /**
	 * @brief 
	 *
	 * @return	
	 */
	const std::vector<uint32_t>& getPrimitiveIndices() const;
  
private:
  /**
   * BVH tree nodes.
   */
	std::vector<Node> nodes_;

  /**
   * Primitive indices.
   */
	std::vector<uint32_t> prim_indices_;
};

}

#endif  // LSG_ACCELERATORS_SBVH_NODE_H