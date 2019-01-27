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

#ifndef LSG_CORE_STRING_UTIL_H
#define LSG_CORE_STRING_UTIL_H

#include <string>
#include <sstream>

namespace lsg {
namespace util {
namespace detail {

/**
 * @brief Append object to the stream
 *
 * @tparam LastArg - type
 * @param stream - output stream
 * @param arg - const reference to the argument
 * @return std::ostream& output stream
 */
template<typename LastArg>
std::ostream& streamAppend(std::ostream& stream, const LastArg& arg) {
	return (stream << arg);
}

/**
 * @brief Append arguments to the stream.
 *
 * @tparam FirstArg first argument type
 * @tparam SecondArg second argument type
 * @tparam Args other arguments
 * @param stream output stream
 * @param arg1 first argument
 * @param arg2 second argument
 * @param args other arguments
 * @return std::ostream& output stream
 */
template<typename FirstArg, typename SecondArg, typename... Args>
std::ostream& streamAppend(std::ostream& stream, const FirstArg& arg1, const SecondArg& arg2, const Args& ... args) {
	stream << arg1;
	return streamAppend(stream, arg2, args...);
}

}

/**
 * @brief String concatenation function.
 */
template<typename... Args>
std::string generateString(const Args& ... args) {
	std::stringstream stream{};
	detail::streamAppend(stream, args...);
	return stream.str();
}

}
}

#endif // LSG_CORE_STRING_UTIL_H