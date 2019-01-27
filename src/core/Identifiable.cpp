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

#include "lsg/core/Identifiable.h"

namespace lsg {

std::atomic<size_t> Identifiable::next_id_ = {0};

Identifiable::Identifiable(std::string name)
  : id_(next_id_.fetch_add(1u, std::memory_order::memory_order_relaxed)), name_(std::move(name)) { }

Identifiable::Identifiable(Identifiable&& other) noexcept
  : id_(other.id_), name_(std::move(other.name_)) {}

Identifiable::Identifiable(const Identifiable& other)
  : id_(next_id_.fetch_add(1u, std::memory_order::memory_order_relaxed)),
    name_(other.name_) {}

Identifiable& Identifiable::operator=(Identifiable&& rhs) noexcept {
	id_ = rhs.id_;
	name_ = std::move(rhs.name_);
	return *this;
}

Identifiable& Identifiable::operator=(const Identifiable& rhs) {
	name_ = rhs.name_;
	return *this;
}

size_t Identifiable::id() const {
	return id_;
}

std::string_view Identifiable::name() const {
	return std::string_view(name_.c_str(), name_.size());
}

}
