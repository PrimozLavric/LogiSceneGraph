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

#ifndef LSG_CORE_EXCEPTIONS_H
#define LSG_CORE_EXCEPTIONS_H

#include <stdexcept>
#include "lsg/util/String.h"

namespace lsg {

template <typename Exception, typename... Args>
void throwIf(const bool condition, Args... args) {
  if (condition) {
	  throw Exception(util::strCat(args...));
  }
}

class LSGException : public std::runtime_error {
	using std::runtime_error::runtime_error;
};

class OutOfRange final : public LSGException {
	using LSGException::LSGException;
};

class InitializationError final : public LSGException {
	using LSGException::LSGException;
};

class InvalidArgument final : public LSGException {
	using LSGException::LSGException;
};

class IllegalInvocation final : public LSGException {
	using LSGException::LSGException;
};

class LoaderError final : public LSGException {
	using LSGException::LSGException;
};

}

#endif // LSG_CORE_EXCEPTIONS_H