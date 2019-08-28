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

#include "lsg/resources/Sampler.h"

namespace lsg {

Sampler::Sampler(const Filter mag_filter, const Filter min_filter, const Wrapping wrapping_u, const Wrapping wrapping_v,
                 const Wrapping wrapping_w, const MipmapMode mipmap_mode, const float mip_lod_bias,
                 const bool enable_anisotropy, const float max_anisotropy, const bool enable_compare,
                 const CompareOp compare_op, const float min_lod, const float max_lod)
  : Identifiable("Sampler"), mag_filter_(mag_filter), min_filter_(min_filter), wrapping_u_(wrapping_u),
    wrapping_v_(wrapping_v), wrapping_w_(wrapping_w), mipmap_mode_(mipmap_mode), mip_lod_bias_(mip_lod_bias),
    enable_anisotropy_(enable_anisotropy), max_anisotropy_(max_anisotropy), enable_compare_(enable_compare),
    compare_op_(compare_op), min_lod_(min_lod), max_lod_(max_lod) {}


} // namespace lsg
