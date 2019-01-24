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
	return active_ && (!parent_ || parent_->isActiveInHierarchy());
}

void Object::addChild(const Shared<Object>& obj) {
	obj->detachInternal();
	obj->parent_ = Ref<Object>(this);
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

void Object::traverseDown(const std::function<bool(Ref<Object>)>& traversal_fn) const {
	if (!traversal_fn(Ref<Object>(const_cast<Object*>(this)))) {
		return;
	}

  for (const auto& child : children_) {
	  child.second->traverseDown(traversal_fn);
  }
}

void Object::traverseDownExcl(const std::function<bool(Ref<Object>)>& traversal_fn) const {
	for (const auto& child : children_) {
		if (traversal_fn(child.second)) {
			child.second->traverseDownExcl(traversal_fn);
		}
	}
}

void Object::traverseUp(const std::function<bool(Ref<Object>)>& traversal_fn) const {
	if (!traversal_fn(Ref<Object>(const_cast<Object*>(this)))) {
		return;
	}

  if (parent_) {
	  parent_->traverseUp(traversal_fn);
  }
}

void Object::traverseUpExcl(const std::function<bool(Ref<Object>)>& traversal_fn) const {
  if (parent_ && traversal_fn(parent_)) {
	  parent_->traverseUpExcl(traversal_fn);
	}
}

void Object::detachInternal() {
	// Proceed if the object has parent
	if (parent_) {
		// Find the object among parent children.
		const auto child_range = parent_->children_.equal_range(name());
		for (auto it = child_range.first; it != child_range.second; ++it) {
			// Remove this object form parent children.
			if (it->second.get() == this) {
				parent_->children_.erase(it);
				parent_.reset();
				return;
			}
		}

		static_assert("Child object was not found among parent object children.");
	}
}

void Object::notifyParentChange() {
  for (const auto& callback : on_parent_change_callbacks_) {
	  callback.second(parent_);
  }
}

}
