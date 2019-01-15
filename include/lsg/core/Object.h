#ifndef LSG_CORE_OBJECT_H
#define LSG_CORE_OBJECT_H

#include <string>
#include <string_view>
#include <map>
#include <unordered_map>
#include <functional>
#include <typeindex>

#include "lsg/core/Identifiable.h"
#include "lsg/core/Component.h"
#include "lsg/core/Common.h"

namespace lsg {

class Object : public Identifiable, public std::enable_shared_from_this<Object> {
public:

  explicit Object(std::string name, bool active = true);

  /**
   * @brief Activate or deactivate the objects.
   *
   * @param	value	Activate - true, Deactivate - false.
   */
  void setActive(bool value);
  
  /**
   * @brief   Search for object with the given name.
   *
   * @tparam  T     Object type. 
   * @param   name  Name of the searched object.
   * @return  Reference to the searched object or null ref if not found.
   */
  template <typename T = Object>
  Ref<T> find(std::string_view name);

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

  /**
   * @brief Sets on parent change callback for the given object.
   * 
   * @param object    Object to which the callback is bound. 
   * @param	callback  Callback.
   */
  void setOnParentChangeCallback(const Ref<Identifiable>& object, const std::function<void(Ref<Object>)>& callback);

  /**
   * @brief Removes on parent change callback registered under the given object.
   * 
   * @param	object  Object to which the callback is bound. 
   */
  void removeOnParentChangeCallback(const Ref<Identifiable>& object);

  /**
   * @brief   Retrieves reference to the parent. If the object has no parent null reference is returned.
   * 
   * @tparam	T Parent type.
   * @return	Reference to the parent or null reference.
   */
  template <typename T = Object>
  Ref<T> getParent() const;

  /**
   * @brief Detach this object from parent if it has one.
   */
  void detach();

  /**
   * @brief   Retrieve child object with the given name.
   *
   * @tparam	T     Type to which the child object will be casted.
   * @param   name	Name of the object to is to be retrieved.
   * @return	Child object with the given name and of the given type or null if no child matches.
   */
  template <typename T = Object>
  Ref<T> getChild(std::string_view name) const;

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
  Ref<T> getComponent() const;

  /**
   * @brief   Retrieve all components of type T
   *
   * @tparam	T	Components type.
   * @return	List of components of the given type.
   */
  template <typename T>
  const std::list<Ref<T>>& getComponents() const;

  /**
   * @brief Default virtual destructor (this object is intended to be inherited).
   */
  virtual ~Object() = default;

protected:

  /**
   * @brief Implementation of detach function.
   */
	void detachInternal();

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
   * Weak reference to the parent.
   */
	WeakRef<Object> parent_;

  /**
   * Holds child objects mapped by their name.
   */
	std::unordered_multimap<std::string_view, Ref<Object>> children_;

  /**
   * Holds components of the object mapped by their type (type index).
   */
	std::unordered_map<std::type_index, std::list<Ref<Component>>> components_;

  /**
   * Callbacks that are invoked once the object parent changes.
   */
	std::unordered_map<size_t, std::function<void(Ref<Object>)>> on_parent_change_callbacks_;
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
Ref<T> Object::getChild(const std::string_view name) const {
  const auto range = children_.equal_range(name);
  for (auto it = range.first; it != range.second; ++it) {
	  Ref<T> ref = std::dynamic_pointer_cast<T>(it->second);
    if (ref) {
		  return ref;
    }
  }

  return nullptr;
}

template <typename T>
Ref<T> Object::find(const std::string_view name) {
	// Check if this object matches the search.
	if (this->name() == name) {
		Ref<T> obj = std::dynamic_pointer_cast<T>(shared_from_this());
	  if (obj) {
		  return obj;
	  }
	}

	// Search in child objects.
	for (auto& child : children_) {
		Ref<T> search_rez = child.second->find<T>(name);
		if (search_rez) {
			return search_rez;
		}
	}

	return nullptr;
}
template <typename T, typename ... Args>
void Object::addComponent(Args... args) {
	components_[std::type_index(typeid(T))].emplace_back(make_ref<T>(this, args...));
}

template <typename T>
Ref<T> Object::getComponent() const {
  const auto it = components_.find(std::type_index(typeid(T)));
	return (it == components_.end() || it->second.empty()) ? nullptr : std::dynamic_pointer_cast<T>(it->second.front());
}

template <typename T>
const std::list<Ref<T>>& Object::getComponents() const {
	const auto it = components_.find(std::type_index(typeid(T)));
	return (it == components_.end()) ? std::vector<Ref<T>>() : it->second;
}

}

#endif  // LSG_CORE_OBJECT_H