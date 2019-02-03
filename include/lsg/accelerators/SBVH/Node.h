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

#ifndef LSG_ACCELERATORS_SBVH_NODE_H
#define LSG_ACCELERATORS_SBVH_NODE_H
#include "lsg/math/AABB.h"

namespace lsg {
namespace sbvh {

class Node {
public:

	virtual bool isLeaf() const = 0;

private:
	AABB bounds_;
};

}
}

#endif  // LSG_ACCELERATORS_SBVH_NODE_H

