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
#include "lsg/core/VersionTracker.h"

namespace lsg {


#ifndef LSG_VULKAN

enum class Filter {
  eNearest,
  eLinear,
  eCubicIMG
};

enum class MipmapMode {
  eNearest,
  eLinear
};

enum class Wrapping {
  eRepeat,
  eMirroredRepeat,
  eClampToEdge,
  eClampToBorder,
  eMirrorClampToEdge
};

enum class CompareOp {
  eNever,
  eLess,
  eEqual,
  eLessOrEqual,
  eGreater,
  eNotEqual,
  eGreaterOrEqual,
  eAlways
};

#else
#include <vulkan/vulkan.hpp>

using Filter = vk::Filter;
using MipmapMode = vk::SamplerMipmapMode;
using Wrapping = vk::SamplerAddressMode;
using CompareOp = vk::CompareOp;

#endif

class Sampler : public Identifiable, public VersionTracker {
public:
  explicit Sampler(Filter mag_filter = Filter::eNearest, Filter min_filter = Filter::eNearest,
                   Wrapping wrapping_u = Wrapping::eRepeat,
                   Wrapping wrapping_v = Wrapping::eRepeat, Wrapping wrapping_w = Wrapping::eRepeat,
                   MipmapMode mipmap_mode = MipmapMode::eNearest,
                   float mip_lod_bias = 0.0f, bool enable_anisotropy = false, float max_anisotropy = 0.0f,
                   bool enable_compare = false,
                   CompareOp compare_op = CompareOp::eAlways, float min_lod = 0.0f, float max_lod = 0.0f);


  Filter magFilter() const;

  void setMagFilter(Filter mag_filter);

  Filter minFilter() const;

  void setMinFilter(Filter min_filter);

  Wrapping wrappingU() const;

  void setWrappingU(Wrapping wrapping_u);

  Wrapping wrappingV() const;

  void setWrappingV(Wrapping wrapping_v);

  Wrapping wrappingW() const;

  void setWrappingW(Wrapping wrapping_w);

  MipmapMode mipmapMode() const;

  void setMipmapMode(MipmapMode mipmap_mode);

  float mipLodBias() const;

  void setMipLodBias(float mip_lod_bias);

  bool enableAnisotropy() const;

  void setEnableAnisotropy(bool enable_anisotropy);

  float maxAnisotropy() const;

  void setMaxAnisotropy(float max_anisotropy);

  bool enableCompare() const;

  void setEnableCompare(bool enable_compare);

  CompareOp compareOp() const;

  void setCompareOp(CompareOp compare_op);

  float minLod() const;

  void setMinLod(float min_lod);

  float maxLod() const;

  void setMaxLod(float max_lod);

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

}

#endif
