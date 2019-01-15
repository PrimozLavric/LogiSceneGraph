#include "lsg/core/Object.h"

namespace lsg {

Object::Object(std::string name, const bool active)
  : Identifiable(std::move(name)), active_(active) {}

void Object::setActive(const bool value) {
	active_ = value;
}

bool Object::isActive() const {
	return active_;
}

bool Object::isActiveInHierarchy() const {
	const auto parent = parent_.lock();
	return active_ && (!parent || parent->isActiveInHierarchy());
}

void Object::addChild(const Ref<Object>& obj) {
	obj->detachInternal();
	obj->parent_ = weak_from_this();
  children_.emplace(obj->name(), obj);
  obj->notifyParentChange();
}

void Object::setOnParentChangeCallback(const Ref<Identifiable>& object,
  const std::function<void(Ref<Object>)>& callback) {
	on_parent_change_callbacks_.insert_or_assign(object->id(), callback);
}

void Object::removeOnParentChangeCallback(const Ref<Identifiable>& object) {
	on_parent_change_callbacks_.erase(object->id());
}

void Object::detach() {
	detachInternal();
	notifyParentChange();
}

void Object::traverseDown(const std::function<bool(Ref<Object>)>& traversal_fn) {
	if (!traversal_fn(shared_from_this())) {
		return;
	}

  for (const auto& child : children_) {
	  child.second->traverseDown(traversal_fn);
  }
}

void Object::traverseDownExcl(const std::function<bool(Ref<Object>)>& traversal_fn) {
	for (const auto& child : children_) {
		if (traversal_fn(child.second)) {
			child.second->traverseDownExcl(traversal_fn);
		}
	}
}

void Object::traverseUp(const std::function<bool(Ref<Object>)>& traversal_fn) {
	if (!traversal_fn(shared_from_this())) {
		return;
	}

  auto parent_ref = parent_.lock();
  if (parent_ref) {
	  parent_ref->traverseUp(traversal_fn);
  }
}

void Object::traverseUpExcl(const std::function<bool(Ref<Object>)>& traversal_fn) {
  auto parent_ref = parent_.lock();
  if (parent_ref && traversal_fn(parent_ref)) {
		parent_ref->traverseUpExcl(traversal_fn);
	}
}

void Object::detachInternal() {
	auto parent_ref = parent_.lock();

	// Proceed if the object has parent
	if (parent_ref) {
		// Find the object among parent children.
		const auto child_range = parent_ref->children_.equal_range(name());
		for (auto it = child_range.first; it != child_range.second; ++it) {
			// Remove this object form parent children.
			if (it->second.get() == this) {
				parent_ref->children_.erase(it);
				parent_.reset();
				return;
			}
		}

		static_assert("Child object was not found among parent object children.");
	}
}

void Object::notifyParentChange() {
  const auto parent_ref = parent_.lock();

  for (auto callback : on_parent_change_callbacks_) {
	  callback.second(parent_ref);
  }
}

}
