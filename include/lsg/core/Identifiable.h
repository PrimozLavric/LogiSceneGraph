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

#ifndef LSG_CORE_IDENTIFIABLE_H
#define LSG_CORE_IDENTIFIABLE_H

#include <string>
#include <atomic>

namespace lsg {

class Identifiable {
public:
  explicit Identifiable(std::string name);
  
  Identifiable(Identifiable&& other) noexcept;

  Identifiable(const Identifiable& other);

  Identifiable& operator=(Identifiable&& rhs) noexcept;

  Identifiable& operator=(const Identifiable& rhs);

  size_t id() const;

  std::string_view name() const;

  void setName(const std::string& name);

  virtual ~Identifiable() = default;

private:
	static std::atomic<size_t> next_id_;

	size_t id_;
  std::string name_;
};

}

#endif  // LSG_CORE_IDENTIFIABLE_H