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

#ifndef LSG_CORE_SCENE_H
#define LSG_CORE_SCENE_H

#include <vector>
#include "lsg/core/Identifiable.h"
#include "lsg/core/Object.h"

namespace lsg {

class Scene : public Identifiable, public std::enable_shared_from_this<Scene> {
 public:
  explicit Scene(std::vector<std::shared_ptr<Object>> root_objects = {});

  explicit Scene(const std::string& name, std::vector<std::shared_ptr<Object>> root_objects = {});

  const std::vector<std::shared_ptr<Object>>& rootObjects() const;

  void addObject(const std::shared_ptr<Object>& object);

 private:
  std::vector<std::shared_ptr<Object>> root_objects_;
};

} // namespace lsg

#endif // LSG_CORE_SCENE_H