/**
 * Project LogiSceneGraph source code
 * Copyright(C) 2019 Primoz Lavric
 *
 * This program is free software : you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#ifndef LSG_RESOURCES_SAMPLER_H
#define LSG_RESOURCES_SAMPLER_H

#include "lsg/core/Identifiable.h"
#include "lsg/core/Ref.h"
#include "lsg/core/VersionTracker.h"

namespace lsg {

#ifndef LSG_VULKAN

enum class Filter { eNearest, eLinear, eCubicIMG };

enum class MipmapMode { eNearest, eLinear };

enum class Wrapping { eRepeat, eMirroredRepeat, eClampToEdge, eClampToBorder, eMirrorClampToEdge };

enum class CompareOp { eNever, eLess, eEqual, eLessOrEqual, eGreater, eNotEqual, eGreaterOrEqual, eAlways };

#else
#include <vulkan/vulkan.hpp>

using Filter = vk::Filter;
using MipmapMode = vk::SamplerMipmapMode;
using Wrapping = vk::SamplerAddressMode;
using CompareOp = vk::CompareOp;

#endif

class Sampler : public Identifiable, public RefCounter<Sampler>, public VersionTracker {
 public:
  explicit Sampler(Filter mag_filter = Filter::eNearest, Filter min_filter = Filter::eNearest,
                   Wrapping wrapping_u = Wrapping::eRepeat, Wrapping wrapping_v = Wrapping::eRepeat,
                   Wrapping wrapping_w = Wrapping::eRepeat, MipmapMode mipmap_mode = MipmapMode::eNearest,
                   float mip_lod_bias = 0.0f, bool enable_anisotropy = false, float max_anisotropy = 0.0f,
                   bool enable_compare = false, CompareOp compare_op = CompareOp::eAlways, float min_lod = 0.0f,
                   float max_lod = 0.0f);

  inline Filter magFilter() const {
    return mag_filter_;
  }

  inline void setMagFilter(const Filter mag_filter) {
    mag_filter_ = mag_filter;
    incrementVersion();
  }

  inline Filter minFilter() const {
    return min_filter_;
  }

  inline void setMinFilter(const Filter min_filter) {
    min_filter_ = min_filter;
    incrementVersion();
  }

  inline Wrapping wrappingU() const {
    return wrapping_u_;
  }

  inline void setWrappingU(const Wrapping wrapping_u) {
    wrapping_u_ = wrapping_u;
    incrementVersion();
  }

  inline Wrapping wrappingV() const {
    return wrapping_v_;
  }

  inline void setWrappingV(const Wrapping wrapping_v) {
    wrapping_v_ = wrapping_v;
    incrementVersion();
  }

  inline Wrapping wrappingW() const {
    return wrapping_w_;
  }

  inline void setWrappingW(const Wrapping wrapping_w) {
    wrapping_w_ = wrapping_w;
    incrementVersion();
  }

  inline MipmapMode mipmapMode() const {
    return mipmap_mode_;
  }

  inline void setMipmapMode(const MipmapMode mipmap_mode) {
    mipmap_mode_ = mipmap_mode;
    incrementVersion();
  }

  inline float mipLodBias() const {
    return mip_lod_bias_;
  }

  inline void setMipLodBias(const float mip_lod_bias) {
    mip_lod_bias_ = mip_lod_bias;
    incrementVersion();
  }

  inline bool enableAnisotropy() const {
    return enable_anisotropy_;
  }

  inline void setEnableAnisotropy(const bool enable_anisotropy) {
    enable_anisotropy_ = enable_anisotropy;
    incrementVersion();
  }

  inline float maxAnisotropy() const {
    return max_anisotropy_;
  }

  inline void setMaxAnisotropy(const float max_anisotropy) {
    max_anisotropy_ = max_anisotropy;
    incrementVersion();
  }

  inline bool enableCompare() const {
    return enable_compare_;
  }

  inline void setEnableCompare(const bool enable_compare) {
    enable_compare_ = enable_compare;
    incrementVersion();
  }

  inline CompareOp compareOp() const {
    return compare_op_;
  }

  inline void setCompareOp(const CompareOp compare_op) {
    compare_op_ = compare_op;
    incrementVersion();
  }

  inline float minLod() const {
    return min_lod_;
  }

  inline void setMinLod(const float min_lod) {
    min_lod_ = min_lod;
    incrementVersion();
  }

  inline float maxLod() const {
    return max_lod_;
  }

  inline void setMaxLod(const float max_lod) {
    max_lod_ = max_lod;
    incrementVersion();
  }

 private:
  Filter mag_filter_;
  Filter min_filter_;
  Wrapping wrapping_u_;
  Wrapping wrapping_v_;
  Wrapping wrapping_w_;
  MipmapMode mipmap_mode_;
  float mip_lod_bias_;
  bool enable_anisotropy_;
  float max_anisotropy_;
  bool enable_compare_;
  CompareOp compare_op_;
  float min_lod_;
  float max_lod_;
};

} // namespace lsg

#endif
