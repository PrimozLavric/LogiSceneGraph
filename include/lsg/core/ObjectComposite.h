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

#ifndef LSG_CORE_OBJECT_COMPOSITE_H
#define LSG_CORE_OBJECT_COMPOSITE_H

#include <functional>
#include <glm/gtx/dual_quaternion.inl>
#include <map>
#include <memory>
#include <type_traits>

namespace lsg {

template <typename ChildType>
class Composite {
 public:
  /**
   * @brief Traverse the hierarchy passing this and all descendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseDown(const std::function<bool(const std::shared_ptr<ChildType>&)>& traversal_fn);

  /**
   * @brief Traverse the hierarchy passing all descendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseDownExcl(const std::function<bool(const std::shared_ptr<ChildType>&)>& traversal_fn) const;

 protected:
};

template <typename ChildType>
void Composite<ChildType>::addChild(const std::shared_ptr<ChildType>& obj) {
  children_.emplace_back(obj);
}

template <typename ChildType>
const std::shared_ptr<ChildType>& Composite<ChildType>::getChild(const std::string_view name) const {
  static std::shared_ptr<ChildType> null = nullptr;

  // Try to find child with the given name.
  auto it = std::find_if(children_.begin(), children_.end(),
                         [&name](const std::shared_ptr<ChildType>& child) { return child->name() == name; });

  if (it != children_.end()) {
    return *it;
  } else {
    return null;
  }
}

template <typename ChildType>
std::shared_ptr<ChildType> Composite<ChildType>::find(const std::string_view hierarchy_path) const {
  // Search in child objects.
  std::shared_ptr<ChildType> search_rez;

  traverseDown([](const std::shared_ptr<ChildType>& obj) {
    // traverseUp
  });

  return search_rez;
}

template <typename ChildType>
void Composite<ChildType>::traverseDown(const std::function<bool(const std::shared_ptr<ChildType>&)>& traversal_fn) {
  auto* t_ptr = dynamic_cast<ChildType*>(const_cast<Composite<ChildType>*>(this));

  if (t_ptr == nullptr || !traversal_fn(t_ptr->shared_from_this())) {
    return;
  }

  traverseDownExcl(traversal_fn);
}

template <typename ChildType>
void Composite<ChildType>::traverseDownExcl(
  const std::function<bool(const std::shared_ptr<ChildType>&)>& traversal_fn) const {
  for (const auto& child : children_) {
    if (traversal_fn(child)) {
      child.second->traverseDownExcl(traversal_fn);
    }
  }
}

} // namespace lsg

#endif // LSG_CORE_OBJECT_COMPOSITE_H
