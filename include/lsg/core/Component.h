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

#ifndef LSG_CORE_COMPONENT_H
#define LSG_CORE_COMPONENT_H

#include <memory>
#include <string>
#include "lsg/core/Identifiable.h"

namespace lsg {

class Object;

class Component : public Identifiable, public std::enable_shared_from_this<Component> {
 public:
  explicit Component(const std::string& name, std::weak_ptr<Object> owner);

  ~Component() override;

 protected:
  std::weak_ptr<Object> owner_;
};

} // namespace lsg

#endif // LSG_CORE_COMPONENT_H