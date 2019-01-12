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

void Object::addChild(const Ref<Object>& obj) {
	obj->parent_ = weak_from_this();
  children_.insert_or_assign(obj->name(), obj);
}

void Object::removeChild(const std::string_view name) {
	auto it = children_.find(name);

  if (it != children_.end()) {
	  it->second->parent_.reset();
	  children_.erase(it);
  }
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

}
