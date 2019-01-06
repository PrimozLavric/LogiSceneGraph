#include "Object.h"

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
  children_.insert_or_assign(obj->name(), obj);
}

void Object::removeChild(const std::string_view name) {
  children_.erase(name);
}

void Object::traverse(const std::function<void(Ref<Object>)>& traversal_fn) {
	traversal_fn(shared_from_this());

  for (const auto& child : children_) {
	  child.second->traverse(traversal_fn);
  }
}

}
