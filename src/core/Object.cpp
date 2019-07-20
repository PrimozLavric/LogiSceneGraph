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

#include "lsg/core/Object.h"

namespace lsg {

Object::Object(std::string name, const bool active) : Identifiable(std::move(name)), active_(active) {}

void Object::setActive(const bool value) {
  active_ = value;
}

bool Object::isActive() const {
  return active_;
}

bool Object::isActiveInHierarchy() const {
  if (auto locked_parent = parent_.lock()) {
    return active_ && locked_parent->isActiveInHierarchy();
  } else {
    return active_;
  }
}

void Object::addChild(const std::shared_ptr<Object>& obj) {
  obj->detachInternal();
  obj->parent_ = weak_from_this();
  children_.emplace(obj->name(), obj);
  obj->notifyParentChange();
}

void Object::setOnParentChangeCallback(const Identifiable& object,
                                       const std::function<void(const std::shared_ptr<Object>& parent)>& callback) {
  on_parent_change_callbacks_.insert_or_assign(object.id(), callback);
}

void Object::removeOnParentChangeCallback(const Identifiable& object) {
  on_parent_change_callbacks_.erase(object.id());
}

void Object::detach() {
  detachInternal();
  notifyParentChange();
}

void Object::traverseDown(const std::function<bool(const std::shared_ptr<Object>&)>& traversal_fn) const {
  if (!traversal_fn(const_cast<Object*>(this)->shared_from_this())) {
    return;
  }

  traverseDownExcl(traversal_fn);
}

void Object::traverseDownExcl(const std::function<bool(const std::shared_ptr<Object>&)>& traversal_fn) const {
  for (const auto& child : children_) {
    if (traversal_fn(child.second)) {
      child.second->traverseDownExcl(traversal_fn);
    }
  }
}

void Object::traverseUp(const std::function<bool(const std::shared_ptr<Object>&)>& traversal_fn) const {
  if (!traversal_fn(const_cast<Object*>(this)->shared_from_this())) {
    return;
  }

  if (auto locked_parent = parent_.lock()) {
    locked_parent->traverseUp(traversal_fn);
  }
}

void Object::traverseUpExcl(const std::function<bool(const std::shared_ptr<Object>&)>& traversal_fn) const {
  auto locked_parent = parent_.lock();
  if (locked_parent && traversal_fn(locked_parent)) {
    locked_parent->traverseUpExcl(traversal_fn);
  }
}

void Object::detachInternal() {
  // Proceed if the object has parent
  if (auto locked_parent = parent_.lock()) {
    // Find the object among parent children.
    const auto child_range = locked_parent->children_.equal_range(name());
    for (auto it = child_range.first; it != child_range.second; ++it) {
      // Remove this object form parent children.
      if (it->second.get() == this) {
        locked_parent->children_.erase(it);
        parent_.reset();
        return;
      }
    }

    static_assert("Child object was not found among parent object children.");
  }
}

void Object::notifyParentChange() {
  auto locked_parent = parent_.lock();
  for (const auto& callback : on_parent_change_callbacks_) {
    callback.second(locked_parent);
  }
}

} // namespace lsg
