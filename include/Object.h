#pragma once
#include <string>
#include <string_view>
#include <map>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include "Identifiable.h"
#include "Component.h"
#include "Common.h"

namespace lsg {

class Object : public Identifiable, std::enable_shared_from_this<Object> {
public:

  explicit Object(std::string name, bool active = true);

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
   * @brief Add child object to this object.
   *
   * @param	obj Child object.
   */
  void addChild(const Ref<Object>& obj);

  /**
   * @brief   Retrieves reference to the parent. If the object has no parent null reference is returned.
   * 
   * @tparam	T Parent type.
   * @return	Reference to the parent or null reference.
   */
  template <typename T = Object>
  Ref<T> getParent() const;

  /**
   * @brief Remove child object with the given name
   *
   * @param	name  Name of the object that is to be removed.
   */
  void removeChild(std::string_view name);

  /**
   * @brief   Retrieve child object with the given name.
   *
   * @tparam	T     Type to which the child object will be casted.
   * @param   name	Name of the object to is to be retrieved.
   * @return	Child object with the given name and of the given type or null if no child matches.
   */
  template <typename T = Object>
  const Ref<T>& getChild(std::string_view name) const;

  /**
   * @brief Traverse the hierarchy passing this and all descendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseDown(const std::function<bool(Ref<Object>)>& traversal_fn);

  /**
   * @brief Traverse the hierarchy passing all descendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseDownExcl(const std::function<bool(Ref<Object>)>& traversal_fn);

  /**
   * @brief Traverse the hierarchy passing this and all ascendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseUp(const std::function<bool(Ref<Object>)>& traversal_fn);

  /**
   * @brief Traverse the hierarchy passing all ascendant object to the traversal function.
   *        Traversal can be stopped by returning false in traversal function.
   *
   * @param	traversal_fn  Traversal function.
   */
  void traverseUpExcl(const std::function<bool(Ref<Object>)>& traversal_fn);

  /**
   * @brief   Add the component to the object.
   *
   * @tparam	T     Type of the component.
   * @param   args  Arguments used for component construction.
   */
  template <typename T, typename... Args>
  void addComponent(Args... args);

  /**
   * @brief   Retrieve first component of the given type T.
   *
   * @tparam	T Component type.
   * @return	First component of type T or null if there is no component of the given type T.
   */
  template <typename T>
  const Ref<T>& getComponent() const;

  /**
   * @brief   Retrieve all components of type T
   *
   * @tparam	T	Components type.
   * @return	Vector of components of the given type.
   */
  template <typename T>
  const std::vector<Ref<T>>& getComponents() const;

  /**
   * @brief Default virtual destructor (this object is intended to be inherited).
   */
  virtual ~Object() = default;

private:
  /**
   * Active flag.
   */
	bool active_;

  /**
   * Weak reference to the parent.
   */
	WeakRef<Object> parent_;

  /**
   * Holds child objects mapped by their name.
   */
	std::map<std::string_view, Ref<Object>> children_;

  /**
   * Holds components of the object mapped by their type (type index).
   */
	std::unordered_map<std::type_index, std::vector<Ref<Component>>> components_;
};

template <typename T>
Ref<T> Object::getParent() const {
	if constexpr (std::is_same<Object, T>()) {
		return parent_.lock();
	} else {
		return std::dynamic_pointer_cast<T>(parent_.lock());
	}
}

template <typename T>
const Ref<T>& Object::getChild(const std::string_view name) const {
  const auto it = children_.find(name);
  return (it == children_.end()) ? nullptr : std::dynamic_pointer_cast<T>(*it);
}

template <typename T, typename ... Args>
void Object::addComponent(Args... args) {
	components_[std::type_index(typeid(T))].emplace_back(make_ref<T>(this, args...));
}

template <typename T>
const Ref<T>& Object::getComponent() const {
  const auto it = components_.find(std::type_index(typeid(T)));
	return (it == components_.end() || it->second.empty()) ? nullptr : it->second[0];
}

template <typename T>
const std::vector<Ref<T>>& Object::getComponents() const {
	const auto it = components_.find(std::type_index(typeid(T)));
	return (it == components_.end()) ? std::vector<Ref<T>>() : it->second;
}

}
