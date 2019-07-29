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

Filter Sampler::magFilter() const {
  return mag_filter_;
}

void Sampler::setMagFilter(const Filter mag_filter) {
  mag_filter_ = mag_filter;
  incrementVersion();
}

Filter Sampler::minFilter() const {
  return min_filter_;
}

void Sampler::setMinFilter(const Filter min_filter) {
  min_filter_ = min_filter;
  incrementVersion();
}

Wrapping Sampler::wrappingU() const {
  return wrapping_u_;
}

void Sampler::setWrappingU(const Wrapping wrapping_u) {
  wrapping_u_ = wrapping_u;
  incrementVersion();
}

Wrapping Sampler::wrappingV() const {
  return wrapping_v_;
}

void Sampler::setWrappingV(const Wrapping wrapping_v) {
  wrapping_v_ = wrapping_v;
  incrementVersion();
}

Wrapping Sampler::wrappingW() const {
  return wrapping_w_;
}

void Sampler::setWrappingW(const Wrapping wrapping_w) {
  wrapping_w_ = wrapping_w;
  incrementVersion();
}

MipmapMode Sampler::mipmapMode() const {
  return mipmap_mode_;
}

void Sampler::setMipmapMode(const MipmapMode mipmap_mode) {
  mipmap_mode_ = mipmap_mode;
  incrementVersion();
}

float Sampler::mipLodBias() const {
  return mip_lod_bias_;
}

void Sampler::setMipLodBias(const float mip_lod_bias) {
  mip_lod_bias_ = mip_lod_bias;
  incrementVersion();
}

bool Sampler::enableAnisotropy() const {
  return enable_anisotropy_;
}

void Sampler::setEnableAnisotropy(const bool enable_anisotropy) {
  enable_anisotropy_ = enable_anisotropy;
  incrementVersion();
}

float Sampler::maxAnisotropy() const {
  return max_anisotropy_;
}

void Sampler::setMaxAnisotropy(const float max_anisotropy) {
  max_anisotropy_ = max_anisotropy;
  incrementVersion();
}

bool Sampler::enableCompare() const {
  return enable_compare_;
}

void Sampler::setEnableCompare(const bool enable_compare) {
  enable_compare_ = enable_compare;
  incrementVersion();
}

CompareOp Sampler::compareOp() const {
  return compare_op_;
}

void Sampler::setCompareOp(const CompareOp compare_op) {
  compare_op_ = compare_op;
  incrementVersion();
}

float Sampler::minLod() const {
  return min_lod_;
}

void Sampler::setMinLod(const float min_lod) {
  min_lod_ = min_lod;
  incrementVersion();
}

float Sampler::maxLod() const {
  return max_lod_;
}

void Sampler::setMaxLod(const float max_lod) {
  max_lod_ = max_lod;
  incrementVersion();
}
} // namespace lsg
