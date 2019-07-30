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
#include <glm/vec2.hpp>
#include <stack>
#include <vector>
#include "lsg/core/Ref.h"
#include "lsg/math/AABB.h"
#include "lsg/math/Ray.h"

namespace lsg {

template <typename T>
class BVH : public RefCounter<BVH<T>> {
 public:
  /**
   * BVH Node.
   */
  struct Node {
    Node(const AABB<T>& bounds, bool is_leaf);

    /**
     * Node bounds.
     */
    AABB<T> bounds;

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
       * Primitive indices range (if leaf node)  [first, last).
       */
      glm::uvec2 indices_range;
    };
  };

  BVH() = default;

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
   * @return
   */
  const std::vector<Node>& getNodes() const;

  /**
   * @brief
   *
   * @return
   */
  const std::vector<uint32_t>& getPrimitiveIndices() const;

  const AABB<T>& getBounds() const;

  std::vector<uint32_t> rayIntersect(const Ray<T>& ray);

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

template <typename T>
BVH<T>::Node::Node(const AABB<T>& bounds, const bool is_leaf) : bounds(bounds), is_leaf(is_leaf) {}

template <typename T>
BVH<T>::BVH(std::vector<Node> nodes, std::vector<uint32_t> prim_indices)
  : nodes_(std::move(nodes)), prim_indices_(std::move(prim_indices)) {}

template <typename T>
const std::vector<typename BVH<T>::Node>& BVH<T>::getNodes() const {
  return nodes_;
}

template <typename T>
const std::vector<uint32_t>& BVH<T>::getPrimitiveIndices() const {
  return prim_indices_;
}

template <typename T>
const AABB<T>& BVH<T>::getBounds() const {
  static AABB<T> zeroBounds;

  if (!nodes_.empty()) {
    return nodes_[0].bounds;
  }

  return zeroBounds;
}

template <typename T>
std::vector<uint32_t> BVH<T>::rayIntersect(const Ray<T>& ray) {
  // If there are no nodes, there are no intersections.
  if (nodes_.empty()) {
    return {};
  }

  // Stack of nodes.
  std::stack<size_t> node_stack;
  node_stack.push(0);

  // Indices of potentially intersected primitives.
  std::vector<uint32_t> potential_isects;

  while (!node_stack.empty()) {
    const Node& node = nodes_[node_stack.top()];
    node_stack.pop();
    if (!ray.intersectAABB(node.bounds)) {
      continue;
    }
    if (!node.is_leaf) {
      node_stack.push(node.child_indices[0]);
      node_stack.push(node.child_indices[1]);
    } else {
      potential_isects.insert(potential_isects.end(), prim_indices_.begin() + node.indices_range[0],
                              prim_indices_.begin() + node.indices_range[1]);
    }
  }

  return potential_isects;
}

} // namespace lsg

#endif // LSG_ACCELERATORS_SBVH_NODE_H