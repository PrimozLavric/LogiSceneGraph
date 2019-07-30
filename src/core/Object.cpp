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
#include <utility>

namespace lsg {

Object::Object(std::string name, const bool active)
  : Identifiable(std::move(name)), active_(active), parent_(nullptr) {}

void Object::setActive(const bool value) {
  active_ = value;
}

bool Object::isActive() const {
  return active_;
}

bool Object::isActiveInHierarchy() const {
  if (parent_ != nullptr) {
    return active_ && parent_->isActiveInHierarchy();
  } else {
    return active_;
  }
}

void Object::addChild(const Ref<Object>& obj) {
  if (obj->parent_ != nullptr) {
    removeChildSilently(obj->id());
  }

  children_.emplace_back(obj);
  obj->changeParent(this);
}

void Object::addChildren(const std::vector<Ref<Object>>& objs) {
  children_.reserve(children_.size() + objs.size());

  for (const auto& child : objs) {
    addChild(child);
  }
}

void Object::removeChild(std::string_view name) {
  for (auto it = children_.begin(); it < children_.end(); it++) {
    if ((*it)->name() == name) {
      Ref<Object> deleted_child = *it;
      children_.erase(it);
      deleted_child->changeParent(nullptr);
    }
  }
}

void Object::removeChild(size_t id) {
  for (auto it = children_.begin(); it < children_.end(); it++) {
    if ((*it)->id() == id) {
      Ref<Object> deleted_child = *it;
      children_.erase(it);
      deleted_child->changeParent(nullptr);
    }
  }
}

Ref<Object> Object::find(std::string_view hierarchy_path) const {
  Ref<Object> match;

  traverseDown([&](const Ref<Object>& obj) {
    if (obj->matchesHierarchyPath(hierarchy_path)) {
      match = obj;
      return false;
    } else {
      return true;
    }
  });

  return match;
}

std::vector<Ref<Object>> Object::findAll(std::string_view hierarchy_path) const {
  std::vector<Ref<Object>> matches;

  traverseDown([&](const Ref<Object>& obj) {
    if (obj->matchesHierarchyPath(hierarchy_path)) {
      matches.emplace_back(obj);
    }
    return true;
  });

  return matches;
}

bool Object::matchesHierarchyPath(std::string_view hierarchy_path) const {
  std::string_view this_name = name();

  // Hierarchy path must be at least the length of name in order to match.
  if (hierarchy_path.size() < this_name.size()) {
    return false;
  }

  // Lengths match.
  if (hierarchy_path.size() == this_name.size()) {
    return hierarchy_path == this_name;
  }

  // Check if the top level matches.
  if (!hierarchy_path.compare(hierarchy_path.size() - this_name.size(), this_name.size(), this_name) ||
      hierarchy_path[hierarchy_path.size() - this_name.size() - 1] != '/') {
    return false;
  }

  std::string_view remaining_path = hierarchy_path.substr(0, hierarchy_path.size() - this_name.size() - 1);
  // This object should be root if the remaining path is empty.
  if (remaining_path.empty()) {
    return parent_ == nullptr;
  } else {
    return parent_->matchesHierarchyPath(remaining_path);
  }
}

void Object::setOnParentChangeCallback(const Identifiable& object,
                                       const std::function<void(const Ref<Object>& parent)>& callback) {
  on_parent_change_callbacks_.insert_or_assign(object.id(), callback);
}

void Object::removeOnParentChangeCallback(const Identifiable& object) {
  on_parent_change_callbacks_.erase(object.id());
}

const std::vector<Ref<Object>>& Object::children() const {
  return children_;
}

void Object::detach() {
  if (parent_ != nullptr) {
    parent_->removeChild(id());
  }
}

void Object::traverseUp(const std::function<bool(const Ref<Object>&)>& traversal_fn) const {
  if (traversal_fn(Ref<Object>(const_cast<Object*>(this)))) {
    traverseUpExcl(traversal_fn);
  }
}

void Object::traverseUpExcl(const std::function<bool(const Ref<Object>&)>& traversal_fn) const {
  if (parent_ != nullptr && traversal_fn(Ref<Object>(parent_))) {
    parent_->traverseUpExcl(traversal_fn);
  }
}

void Object::traverseDown(const std::function<bool(const Ref<Object>&)>& traversal_fn) const {
  if (traversal_fn(Ref<Object>(const_cast<Object*>(this)))) {
    traverseDownExcl(traversal_fn);
  }
}

void Object::traverseDownExcl(const std::function<bool(const Ref<Object>&)>& traversal_fn) const {
  for (const auto& child : children_) {
    if (traversal_fn(child)) {
      child->traverseDownExcl(traversal_fn);
    }
  }
}

void Object::removeChildSilently(size_t id) {
  for (auto it = children_.begin(); it < children_.end(); it++) {
    if ((*it)->id() == id) {
      Ref<Object> deleted_child = *it;
      children_.erase(it);
    }
  }
}

void Object::changeParent(Object* new_parent) {
  if (parent_ != new_parent) {
    parent_ = new_parent;
    notifyParentChange();
  }
}

void Object::notifyParentChange() {
  Ref<Object> parent_ref(parent_);
  for (const auto& callback : on_parent_change_callbacks_) {
    callback.second(parent_ref);
  }
}

} // namespace lsg
