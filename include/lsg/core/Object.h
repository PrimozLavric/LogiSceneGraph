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

#ifndef LSG_CORE_OBJECT_H
#define LSG_CORE_OBJECT_H

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include "lsg/core/Component.h"
#include "lsg/core/Identifiable.h"
#include "lsg/core/Ref.h"

namespace lsg {

class Object : public Identifiable, public RefCounter<Object> {
 public:
  explicit Object(std::string name, bool active = true);

  Object(const Object& other) = delete;
  Object(Object&& other) = delete;

  /**
   * @brief Activate or deactivate the objects.
   *
   * @param	value	Activate - true, Deactivate - false.
   */
  void setActive(bool value);

  /**
   * @brief   Check if the object is active.
   *
   * @return	True if the object is active.
   */
  bool isActive() const;

  /**
   * @brief   Check if the object and all its ancestors are active.
   *
   * @return	True if the object and all its ancestors are active.
   */
  bool isActiveInHierarchy() const;

  /**
   * @brief Add child object to this object.
   *
   * @param	obj Child object.
   */
  void addChild(const Ref<Object>& obj);

  void addChildren(const std::vector<Ref<Object>>& objs);

  void removeChild(std::string_view name);

  void removeChild(size_t id);

  /**
   * @brief   Retrieve child object with the given name.
   *
   * @tparam	T     Type to which the child object will be casted.
   * @param   name	Name of the object that is to be retrieved.
   * @return	Child object with the given name and of the given type or null if no child matches.
   */
  template <typename T = Object>
  Ref<Object> getChild(std::string_view name) const;

  /**
   * @brief   Search for object with the given name.
   *
   * @tparam  T     Object type.
   * @param   name  Name of the searched object.
   * @return  Shared pointer that points to the searched child or nullptr if not found.
   */
  Ref<Object> find(std::string_view hierarchy_path) const;

  std::vector<Ref<Object>> findAll(std::string_view hierarchy_path) const;

  bool matchesHierarchyPath(std::string_view hierarchy_path) const;

  /**
   * @brief Sets on parent change callback for the given object.
   *
   * @param object    Object to which the callback is bound.
   * @param	callback  Callback.
   */
  void setOnParentChangeCallback(const Identifiable& object, const std::function<void(const Ref<Object>&)>& callback);

  /**
   * @brief Removes on parent change callback registered under the given object.
   *
   * @param	object  Object to which the callback is bound.
   */
  void removeOnParentChangeCallback(const Identifiable& object);

  /**
   * @brief   Retrieves reference to the parent. If the object has no parent null reference is returned.
   *
   * @tparam	T Parent type.
   * @return	Reference to the parent or null reference.
   */
  template <typename T = Object>
  Ref<T> parent() const;

  const std::vector<Ref<Object>>& children() const;

  /**
   * @brief Detach this object from parent if it has one.
   */
  void detach();

  /**
   * @brief Traverse the hierarchy passing this and all ascendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseUp(const std::function<bool(const Ref<Object>&)>& traversal_fn) const;

  /**
   * @brief Traverse the hierarchy passing all ascendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseUpExcl(const std::function<bool(const Ref<Object>&)>& traversal_fn) const;

  /**
   * @brief Traverse the hierarchy passing this and all descendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseDown(const std::function<bool(const Ref<Object>&)>& traversal_fn) const;

  /**
   * @brief Traverse the hierarchy passing all descendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseDownExcl(const std::function<bool(const Ref<Object>&)>& traversal_fn) const;

  /**
   * @brief   Add the component to the object.
   *
   * @tparam	T     Type of the component.
   * @param   args  Arguments used for component construction.
   * @return  Reference to the component.
   */
  template <typename T, typename... Args>
  Ref<T> addComponent(Args... args);

  /**
   * @brief   Retrieve first component of the given type T.
   *
   * @tparam	T Component type.
   * @return	First component of type T or null if there is no component of the given type T.
   */
  template <typename T>
  Ref<T> getComponent();

  /**
   * @brief   Retrieve all components of type T
   *
   * @tparam	T	Components type.
   * @return	Vector of components of the given type.
   */
  template <typename T>
  std::vector<Ref<T>> getComponents();

  ~Object() override = default;

 protected:
  void removeChildSilently(size_t id);

  /**
   * @brief
   * @param new_parent
   */
  void changeParent(Object* new_parent);

  /**
   * @brief Invoke on parent change callbacks.
   */
  void notifyParentChange();

 private:
  /**
   * Active flag.
   */
  bool active_;

  /**
   * Pointer to parent
   */
  Object* parent_;

  /**
   * Holds child objects.
   */
  std::vector<Ref<Object>> children_;

  /**
   * Holds components of the object.
   */
  std::vector<Ref<Component>> components_;

  /**
   * Callbacks that are invoked once the object parent changes.
   */
  std::unordered_map<size_t, std::function<void(const Ref<Object>&)>> on_parent_change_callbacks_;
};

template <typename T>
Ref<T> Object::parent() const {
  if constexpr (std::is_same<Object, T>()) {
    return Ref<T>(parent_);
  } else {
    return Ref<T>(dynamic_cast<T>(parent_));
  }
}

template <typename T>
Ref<Object> Object::getChild(std::string_view name) const {
  for (const auto& child : children_) {
    if (child->name() == name) {
      if constexpr (std::is_same_v<T, Object>) {
        return child;
      } else {
        Ref<T> casted = dynamicRefCast<T>(child);
        if (casted) {
          return casted;
        }
      }
    }
  }

  return nullptr;
}

template <typename T, typename... Args>
Ref<T> Object::addComponent(Args... args) {
  components_.emplace_back(makeRef<T>(*this, args...));
  return Ref<T>(staticRefCast<T>(components_.back()));
}

template <typename T>
Ref<T> Object::getComponent() {
  for (const auto& component : components_) {
    Ref<T> casted = dynamicRefCast<T>(component);
    if (casted) {
      return casted;
    }
  }

  return nullptr;
}

template <typename T>
std::vector<Ref<T>> Object::getComponents() {
  std::vector<Ref<T>> matches;
  for (const auto& component : components_) {
    Ref<T> casted = dynamicRefCast<T>(&component);
    if (casted != nullptr) {
      matches.emplace_back(casted);
    }
  }

  return matches;
}

} // namespace lsg

#endif // LSG_CORE_OBJECT_H