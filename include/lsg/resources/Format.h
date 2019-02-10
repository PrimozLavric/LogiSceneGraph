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

#ifndef LSG_RESOURCES_FORMAT_H
#define LSG_RESOURCES_FORMAT_H

#include <unordered_map>

namespace lsg {

struct FormatInfo {
  size_t size = 0;
  size_t channel_count = 0;
};

struct EnumClassHash {
	template <typename T>
	size_t operator()(const T& value) const {
		return static_cast<size_t>(value);
	}
};

#ifndef LSG_VULKAN

enum class Format {
	eUndefined,
	eR4G4UnormPack8,
	eR4G4B4A4UnormPack16,
	eB4G4R4A4UnormPack16,
	eR5G6B5UnormPack16,
	eB5G6R5UnormPack16,
	eR5G5B5A1UnormPack16,
	eB5G5R5A1UnormPack16,
	eA1R5G5B5UnormPack16,
	eR8Unorm,
	eR8Snorm,
	eR8Uscaled,
	eR8Sscaled,
	eR8Uint,
	eR8Sint,
	eR8Srgb,
	eR8G8Unorm,
	eR8G8Snorm,
	eR8G8Uscaled,
	eR8G8Sscaled,
	eR8G8Uint,
	eR8G8Sint,
	eR8G8Srgb,
	eR8G8B8Unorm,
	eR8G8B8Snorm,
	eR8G8B8Uscaled,
	eR8G8B8Sscaled,
	eR8G8B8Uint,
	eR8G8B8Sint,
	eR8G8B8Srgb,
	eB8G8R8Unorm,
	eB8G8R8Snorm,
	eB8G8R8Uscaled,
	eB8G8R8Sscaled,
	eB8G8R8Uint,
	eB8G8R8Sint,
	eB8G8R8Srgb,
	eR8G8B8A8Unorm,
	eR8G8B8A8Snorm,
	eR8G8B8A8Uscaled,
	eR8G8B8A8Sscaled,
	eR8G8B8A8Uint,
	eR8G8B8A8Sint,
	eR8G8B8A8Srgb,
	eB8G8R8A8Unorm,
	eB8G8R8A8Snorm,
	eB8G8R8A8Uscaled,
	eB8G8R8A8Sscaled,
	eB8G8R8A8Uint,
	eB8G8R8A8Sint,
	eB8G8R8A8Srgb,
	eA8B8G8R8UnormPack32,
	eA8B8G8R8SnormPack32,
	eA8B8G8R8UscaledPack32,
	eA8B8G8R8SscaledPack32,
	eA8B8G8R8UintPack32,
	eA8B8G8R8SintPack32,
	eA8B8G8R8SrgbPack32,
	eA2R10G10B10UnormPack32,
	eA2R10G10B10SnormPack32,
	eA2R10G10B10UscaledPack32,
	eA2R10G10B10SscaledPack32,
	eA2R10G10B10UintPack32,
	eA2R10G10B10SintPack32,
	eA2B10G10R10UnormPack32,
	eA2B10G10R10SnormPack32,
	eA2B10G10R10UscaledPack32,
	eA2B10G10R10SscaledPack32,
	eA2B10G10R10UintPack32,
	eA2B10G10R10SintPack32,
	eR16Unorm,
	eR16Snorm,
	eR16Uscaled,
	eR16Sscaled,
	eR16Uint,
	eR16Sint,
	eR16Sfloat,
	eR16G16Unorm,
	eR16G16Snorm,
	eR16G16Uscaled,
	eR16G16Sscaled,
	eR16G16Uint,
	eR16G16Sint,
	eR16G16Sfloat,
	eR16G16B16Unorm,
	eR16G16B16Snorm,
	eR16G16B16Uscaled,
	eR16G16B16Sscaled,
	eR16G16B16Uint,
	eR16G16B16Sint,
	eR16G16B16Sfloat,
	eR16G16B16A16Unorm,
	eR16G16B16A16Snorm,
	eR16G16B16A16Uscaled,
	eR16G16B16A16Sscaled,
	eR16G16B16A16Uint,
	eR16G16B16A16Sint,
	eR16G16B16A16Sfloat,
	eR32Uint,
	eR32Sint,
	eR32Sfloat,
	eR32G32Uint,
	eR32G32Sint,
	eR32G32Sfloat,
	eR32G32B32Uint,
	eR32G32B32Sint,
	eR32G32B32Sfloat,
	eR32G32B32A32Uint,
	eR32G32B32A32Sint,
	eR32G32B32A32Sfloat,
	eR64Uint,
	eR64Sint,
	eR64Sfloat,
	eR64G64Uint,
	eR64G64Sint,
	eR64G64Sfloat,
	eR64G64B64Uint,
	eR64G64B64Sint,
	eR64G64B64Sfloat,
	eR64G64B64A64Uint,
	eR64G64B64A64Sint,
	eR64G64B64A64Sfloat,
	eB10G11R11UfloatPack32,
	eE5B9G9R9UfloatPack32,
	eD16Unorm,
	eX8D24UnormPack32,
	eD32Sfloat,
	eS8Uint,
	eD16UnormS8Uint,
	eD24UnormS8Uint,
	eD32SfloatS8Uint,
	eBc1RgbUnormBlock,
	eBc1RgbSrgbBlock,
	eBc1RgbaUnormBlock,
	eBc1RgbaSrgbBlock,
	eBc2UnormBlock,
	eBc2SrgbBlock,
	eBc3UnormBlock,
	eBc3SrgbBlock,
	eBc4UnormBlock,
	eBc4SnormBlock,
	eBc5UnormBlock,
	eBc5SnormBlock,
	eBc6HUfloatBlock,
	eBc6HSfloatBlock,
	eBc7UnormBlock,
	eBc7SrgbBlock,
	eEtc2R8G8B8UnormBlock,
	eEtc2R8G8B8SrgbBlock,
	eEtc2R8G8B8A1UnormBlock,
	eEtc2R8G8B8A1SrgbBlock,
	eEtc2R8G8B8A8UnormBlock,
	eEtc2R8G8B8A8SrgbBlock,
	eEacR11UnormBlock,
	eEacR11SnormBlock,
	eEacR11G11UnormBlock,
	eEacR11G11SnormBlock,
	eAstc4x4UnormBlock,
	eAstc4x4SrgbBlock,
	eAstc5x4UnormBlock,
	eAstc5x4SrgbBlock,
	eAstc5x5UnormBlock,
	eAstc5x5SrgbBlock,
	eAstc6x5UnormBlock,
	eAstc6x5SrgbBlock,
	eAstc6x6UnormBlock,
	eAstc6x6SrgbBlock,
	eAstc8x5UnormBlock,
	eAstc8x5SrgbBlock,
	eAstc8x6UnormBlock,
	eAstc8x6SrgbBlock,
	eAstc8x8UnormBlock,
	eAstc8x8SrgbBlock,
	eAstc10x5UnormBlock,
	eAstc10x5SrgbBlock,
	eAstc10x6UnormBlock,
	eAstc10x6SrgbBlock,
	eAstc10x8UnormBlock,
	eAstc10x8SrgbBlock,
	eAstc10x10UnormBlock,
	eAstc10x10SrgbBlock,
	eAstc12x10UnormBlock,
	eAstc12x10SrgbBlock,
	eAstc12x12UnormBlock,
	eAstc12x12SrgbBlock,
	eG8B8G8R8422Unorm,
	eG8B8G8R8422UnormKHR,
	eB8G8R8G8422Unorm,
	eB8G8R8G8422UnormKHR,
	eG8B8R83Plane420Unorm,
	eG8B8R83Plane420UnormKHR,
	eG8B8R82Plane420Unorm,
	eG8B8R82Plane420UnormKHR,
	eG8B8R83Plane422Unorm,
	eG8B8R83Plane422UnormKHR,
	eG8B8R82Plane422Unorm,
	eG8B8R82Plane422UnormKHR,
	eG8B8R83Plane444Unorm,
	eG8B8R83Plane444UnormKHR,
	eR10X6UnormPack16,
	eR10X6UnormPack16KHR,
	eR10X6G10X6Unorm2Pack16,
	eR10X6G10X6Unorm2Pack16KHR,
	eR10X6G10X6B10X6A10X6Unorm4Pack16,
	eR10X6G10X6B10X6A10X6Unorm4Pack16KHR,
	eG10X6B10X6G10X6R10X6422Unorm4Pack16,
	eG10X6B10X6G10X6R10X6422Unorm4Pack16KHR,
	eB10X6G10X6R10X6G10X6422Unorm4Pack16,
	eB10X6G10X6R10X6G10X6422Unorm4Pack16KHR,
	eG10X6B10X6R10X63Plane420Unorm3Pack16,
	eG10X6B10X6R10X63Plane420Unorm3Pack16KHR,
	eG10X6B10X6R10X62Plane420Unorm3Pack16,
	eG10X6B10X6R10X62Plane420Unorm3Pack16KHR,
	eG10X6B10X6R10X63Plane422Unorm3Pack16,
	eG10X6B10X6R10X63Plane422Unorm3Pack16KHR,
	eG10X6B10X6R10X62Plane422Unorm3Pack16,
	eG10X6B10X6R10X62Plane422Unorm3Pack16KHR,
	eG10X6B10X6R10X63Plane444Unorm3Pack16,
	eG10X6B10X6R10X63Plane444Unorm3Pack16KHR,
	eR12X4UnormPack16,
	eR12X4UnormPack16KHR,
	eR12X4G12X4Unorm2Pack16,
	eR12X4G12X4Unorm2Pack16KHR,
	eR12X4G12X4B12X4A12X4Unorm4Pack16,
	eR12X4G12X4B12X4A12X4Unorm4Pack16KHR,
	eG12X4B12X4G12X4R12X4422Unorm4Pack16,
	eG12X4B12X4G12X4R12X4422Unorm4Pack16KHR,
	eB12X4G12X4R12X4G12X4422Unorm4Pack16,
	eB12X4G12X4R12X4G12X4422Unorm4Pack16KHR,
	eG12X4B12X4R12X43Plane420Unorm3Pack16,
	eG12X4B12X4R12X43Plane420Unorm3Pack16KHR,
	eG12X4B12X4R12X42Plane420Unorm3Pack16,
	eG12X4B12X4R12X42Plane420Unorm3Pack16KHR,
	eG12X4B12X4R12X43Plane422Unorm3Pack16,
	eG12X4B12X4R12X43Plane422Unorm3Pack16KHR,
	eG12X4B12X4R12X42Plane422Unorm3Pack16,
	eG12X4B12X4R12X42Plane422Unorm3Pack16KHR,
	eG12X4B12X4R12X43Plane444Unorm3Pack16,
	eG12X4B12X4R12X43Plane444Unorm3Pack16KHR,
	eG16B16G16R16422Unorm,
	eG16B16G16R16422UnormKHR,
	eB16G16R16G16422Unorm,
	eB16G16R16G16422UnormKHR,
	eG16B16R163Plane420Unorm,
	eG16B16R163Plane420UnormKHR,
	eG16B16R162Plane420Unorm,
	eG16B16R162Plane420UnormKHR,
	eG16B16R163Plane422Unorm,
	eG16B16R163Plane422UnormKHR,
	eG16B16R162Plane422Unorm,
	eG16B16R162Plane422UnormKHR,
	eG16B16R163Plane444Unorm,
	eG16B16R163Plane444UnormKHR,
	ePvrtc12BppUnormBlockIMG,
	ePvrtc14BppUnormBlockIMG,
	ePvrtc22BppUnormBlockIMG,
	ePvrtc24BppUnormBlockIMG,
	ePvrtc12BppSrgbBlockIMG,
	ePvrtc14BppSrgbBlockIMG,
	ePvrtc22BppSrgbBlockIMG,
	ePvrtc24BppSrgbBlockIMG
};

#else 

#include <vulkan/vulkan.hpp>
// Use Vulkan format.
using Format = vk::Format;

#endif

const std::unordered_map<Format, FormatInfo, EnumClassHash> kFormatTable = {
  {Format::eUndefined, {0u, 0u}},
  {Format::eR4G4UnormPack8, {1u, 2u}},
  {Format::eR4G4B4A4UnormPack16, {2u, 4u}},
  {Format::eB4G4R4A4UnormPack16, {2u, 4u}},
  {Format::eR5G6B5UnormPack16, {2, 3}},
  {Format::eB5G6R5UnormPack16, {2, 3}},
  {Format::eR5G5B5A1UnormPack16, {2, 4}},
  {Format::eB5G5R5A1UnormPack16, {2, 4}},
  {Format::eA1R5G5B5UnormPack16, {2, 4}},
  {Format::eR8Unorm, {1u, 1u}},
  {Format::eR8Snorm, {1u, 1u}},
  {Format::eR8Uscaled, {1u, 1u}},
  {Format::eR8Sscaled, {1u, 1u}},
  {Format::eR8Uint, {1u, 1u}},
  {Format::eR8Sint, {1u, 1u}},
  {Format::eR8Srgb, {1u, 1u}},
  {Format::eR8G8Unorm, {2u, 2u}},
  {Format::eR8G8Snorm, {2u, 2u}},
  {Format::eR8G8Uscaled, {2u, 2u}},
  {Format::eR8G8Sscaled, {2u, 2u}},
  {Format::eR8G8Uint, {2u, 2u}},
  {Format::eR8G8Sint, {2u, 2u}},
  {Format::eR8G8Srgb, {2u, 2u}},
  {Format::eR8G8B8Unorm, {3u, 3u}},
  {Format::eR8G8B8Snorm, {3u, 3u}},
  {Format::eR8G8B8Uscaled, {3u, 3u}},
  {Format::eR8G8B8Sscaled, {3u, 3u}},
  {Format::eR8G8B8Uint, {3u, 3u}},
  {Format::eR8G8B8Sint, {3u, 3u}},
  {Format::eR8G8B8Srgb, {3u, 3u}},
  {Format::eB8G8R8Unorm, {3u, 3u}},
  {Format::eB8G8R8Snorm, {3u, 3u}},
  {Format::eB8G8R8Uscaled, {3u, 3u}},
  {Format::eB8G8R8Sscaled, {3u, 3u}},
  {Format::eB8G8R8Uint, {3u, 3u}},
  {Format::eB8G8R8Sint, {3u, 3u}},
  {Format::eB8G8R8Srgb, {3u, 3u}},
  {Format::eR8G8B8A8Unorm, {4u, 4u}},
  {Format::eR8G8B8A8Snorm, {4u, 4u}},
  {Format::eR8G8B8A8Uscaled, {4u, 4u}},
  {Format::eR8G8B8A8Sscaled, {4u, 4u}},
  {Format::eR8G8B8A8Uint, {4u, 4u}},
  {Format::eR8G8B8A8Sint, {4u, 4u}},
  {Format::eR8G8B8A8Srgb, {4u, 4u}},
  {Format::eB8G8R8A8Unorm, {4u, 4u}},
  {Format::eB8G8R8A8Snorm, {4u, 4u}},
  {Format::eB8G8R8A8Uscaled, {4u, 4u}},
  {Format::eB8G8R8A8Sscaled, {4u, 4u}},
  {Format::eB8G8R8A8Uint, {4u, 4u}},
  {Format::eB8G8R8A8Sint, {4u, 4u}},
  {Format::eB8G8R8A8Srgb, {4u, 4u}},
  {Format::eA8B8G8R8UnormPack32, {4u, 4u}},
  {Format::eA8B8G8R8SnormPack32, {4u, 4u}},
  {Format::eA8B8G8R8UscaledPack32, {4u, 4u}},
  {Format::eA8B8G8R8SscaledPack32, {4u, 4u}},
  {Format::eA8B8G8R8UintPack32, {4u, 4u}},
  {Format::eA8B8G8R8SintPack32, {4u, 4u}},
  {Format::eA8B8G8R8SrgbPack32, {4u, 4u}},
  {Format::eA2R10G10B10UnormPack32, {4u, 4u}},
  {Format::eA2R10G10B10SnormPack32, {4u, 4u}},
  {Format::eA2R10G10B10UscaledPack32, {4u, 4u}},
  {Format::eA2R10G10B10SscaledPack32, {4u, 4u}},
  {Format::eA2R10G10B10UintPack32, {4u, 4u}},
  {Format::eA2R10G10B10SintPack32, {4u, 4u}},
  {Format::eA2B10G10R10UnormPack32, {4u, 4u}},
  {Format::eA2B10G10R10SnormPack32, {4u, 4u}},
  {Format::eA2B10G10R10UscaledPack32, {4u, 4u}},
  {Format::eA2B10G10R10SscaledPack32, {4u, 4u}},
  {Format::eA2B10G10R10UintPack32, {4u, 4u}},
  {Format::eA2B10G10R10SintPack32, {4u, 4u}},
  {Format::eR16Unorm, {2u, 1u}},
  {Format::eR16Snorm, {2u, 1u}},
  {Format::eR16Uscaled, {2u, 1u}},
  {Format::eR16Sscaled, {2u, 1u}},
  {Format::eR16Uint, {2u, 1u}},
  {Format::eR16Sint, {2u, 1u}},
  {Format::eR16Sfloat, {2u, 1u}},
  {Format::eR16G16Unorm, {4u, 2u}},
  {Format::eR16G16Snorm, {4u, 2u}},
  {Format::eR16G16Uscaled, {4u, 2u}},
  {Format::eR16G16Sscaled, {4u, 2u}},
  {Format::eR16G16Uint, {4u, 2u}},
  {Format::eR16G16Sint, {4u, 2u}},
  {Format::eR16G16Sfloat, {4u, 2u}},
  {Format::eR16G16B16Unorm, {6u, 3u}},
  {Format::eR16G16B16Snorm, {6u, 3u}},
  {Format::eR16G16B16Uscaled, {6u, 3u}},
  {Format::eR16G16B16Sscaled, {6u, 3u}},
  {Format::eR16G16B16Uint, {6u, 3u}},
  {Format::eR16G16B16Sint, {6u, 3u}},
  {Format::eR16G16B16Sfloat, {6u, 3u}},
  {Format::eR16G16B16A16Unorm, {8u, 4u}},
  {Format::eR16G16B16A16Snorm, {8u, 4u}},
  {Format::eR16G16B16A16Uscaled, {8u, 4u}},
  {Format::eR16G16B16A16Sscaled, {8u, 4u}},
  {Format::eR16G16B16A16Uint, {8u, 4u}},
  {Format::eR16G16B16A16Sint, {8u, 4u}},
  {Format::eR16G16B16A16Sfloat, {8u, 4u}},
  {Format::eR32Uint, {4u, 1u}},
  {Format::eR32Sint, {4u, 1u}},
  {Format::eR32Sfloat, {4u, 1u}},
  {Format::eR32G32Uint, {8u, 2u}},
  {Format::eR32G32Sint, {8u, 2u}},
  {Format::eR32G32Sfloat, {8u, 2u}},
  {Format::eR32G32B32Uint, {12u, 3u}},
  {Format::eR32G32B32Sint, {12u, 3u}},
  {Format::eR32G32B32Sfloat, {12u, 3u}},
  {Format::eR32G32B32A32Uint, {16u, 4u}},
  {Format::eR32G32B32A32Sint, {16u, 4u}},
  {Format::eR32G32B32A32Sfloat, {16u, 4u}},
  {Format::eR64Uint, {8u, 1u}},
  {Format::eR64Sint, {8u, 1u}},
  {Format::eR64Sfloat, {8u, 1u}},
  {Format::eR64G64Uint, {16u, 2u}},
  {Format::eR64G64Sint, {16u, 2u}},
  {Format::eR64G64Sfloat, {16u, 2u}},
  {Format::eR64G64B64Uint, {24u, 3u}},
  {Format::eR64G64B64Sint, {24u, 3u}},
  {Format::eR64G64B64Sfloat, {24u, 3u}},
  {Format::eR64G64B64A64Uint, {32u, 4u}},
  {Format::eR64G64B64A64Sint, {32u, 4u}},
  {Format::eR64G64B64A64Sfloat, {32u, 4u}},
  {Format::eB10G11R11UfloatPack32, {4u, 3u}},
  {Format::eE5B9G9R9UfloatPack32, {4u, 3u}},
  {Format::eD16Unorm, {2u, 1u}},
  {Format::eX8D24UnormPack32, {4u, 1u}},
  {Format::eD32Sfloat, {4u, 1u}},
  {Format::eS8Uint, {1u, 1u}},
  {Format::eD16UnormS8Uint, {3u, 2u}},
  {Format::eD24UnormS8Uint, {4u, 2u}},
  {Format::eD32SfloatS8Uint, {5u, 2u}},
  {Format::eBc1RgbUnormBlock, {8u, 3u}},
  {Format::eBc1RgbSrgbBlock, {8u, 3u}},
  {Format::eBc1RgbaUnormBlock, {8u, 4u}},
  {Format::eBc1RgbaSrgbBlock, {8u, 4u}},
  {Format::eBc2UnormBlock, {16u, 4u}},
  {Format::eBc2SrgbBlock, {16u, 4u}},
  {Format::eBc3UnormBlock, {16u, 4u}},
  {Format::eBc3SrgbBlock, {16u, 4u}},
  {Format::eBc4UnormBlock, {8u, 1u}},
  {Format::eBc4SnormBlock, {8u, 1u}},
  {Format::eBc5UnormBlock, {16u, 2u}},
  {Format::eBc5SnormBlock, {16u, 2u}},
  {Format::eBc6HUfloatBlock, {16u, 3u}},
  {Format::eBc6HSfloatBlock, {16u, 3u}},
  {Format::eBc7UnormBlock, {16u, 4u}},
  {Format::eBc7SrgbBlock, {16u, 4u}},
  {Format::eEtc2R8G8B8UnormBlock, {8u, 3u}},
  {Format::eEtc2R8G8B8SrgbBlock, {8u, 3u}},
  {Format::eEtc2R8G8B8A1UnormBlock, {8u, 4u}},
  {Format::eEtc2R8G8B8A1SrgbBlock, {8u, 4u}},
  {Format::eEtc2R8G8B8A8UnormBlock, {8u, 4u}},
  {Format::eEtc2R8G8B8A8SrgbBlock, {8u, 4u}},
  {Format::eEacR11UnormBlock, {8u, 1u}},
  {Format::eEacR11SnormBlock, {8u, 1u}},
  {Format::eEacR11G11UnormBlock, {16u, 2u}},
  {Format::eEacR11G11SnormBlock, {16u, 2u}},
  {Format::eAstc4x4UnormBlock, {16u, 4u}},
  {Format::eAstc4x4SrgbBlock, {16u, 4u}},
  {Format::eAstc5x4UnormBlock, {16u, 4u}},
  {Format::eAstc5x4SrgbBlock, {16u, 4u}},
  {Format::eAstc5x5UnormBlock, {16u, 4u}},
  {Format::eAstc5x5SrgbBlock, {16u, 4u}},
  {Format::eAstc6x5UnormBlock, {16u, 4u}},
  {Format::eAstc6x5SrgbBlock, {16u, 4u}},
  {Format::eAstc6x6UnormBlock, {16u, 4u}},
  {Format::eAstc6x6SrgbBlock, {16u, 4u}},
  {Format::eAstc8x5UnormBlock, {16u, 4u}},
  {Format::eAstc8x5SrgbBlock, {16u, 4u}},
  {Format::eAstc8x6UnormBlock, {16u, 4u}},
  {Format::eAstc8x6SrgbBlock, {16u, 4u}},
  {Format::eAstc8x8UnormBlock, {16u, 4u}},
  {Format::eAstc8x8SrgbBlock, {16u, 4u}},
  {Format::eAstc10x5UnormBlock, {16u, 4u}},
  {Format::eAstc10x5SrgbBlock, {16u, 4u}},
  {Format::eAstc10x6UnormBlock, {16u, 4u}},
  {Format::eAstc10x6SrgbBlock, {16u, 4u}},
  {Format::eAstc10x8UnormBlock, {16u, 4u}},
  {Format::eAstc10x8SrgbBlock, {16u, 4u}},
  {Format::eAstc10x10UnormBlock, {16u, 4u}},
  {Format::eAstc10x10SrgbBlock, {16u, 4u}},
  {Format::eAstc12x10UnormBlock, {16u, 4u}},
  {Format::eAstc12x10SrgbBlock, {16u, 4u}},
  {Format::eAstc12x12UnormBlock, {16u, 4u}},
  {Format::eAstc12x12SrgbBlock, {16u, 4u}},
  {Format::eG8B8G8R8422Unorm, {4u, 4u}},
  {Format::eG8B8G8R8422UnormKHR, {4u, 4u}},
  {Format::eB8G8R8G8422Unorm, {4u, 4u}},
  {Format::eB8G8R8G8422UnormKHR, {4u, 4u}},
  {Format::eG8B8R83Plane420Unorm, {3u, 3u}},
  {Format::eG8B8R83Plane420UnormKHR, {3u, 3u}},
  {Format::eG8B8R82Plane420Unorm, {3u, 2u}},
  {Format::eG8B8R82Plane420UnormKHR, {3u, 2u}},
  {Format::eG8B8R83Plane422Unorm, {3u, 3u}},
  {Format::eG8B8R83Plane422UnormKHR, {3u, 3u}},
  {Format::eG8B8R82Plane422Unorm, {3u, 2u}},
  {Format::eG8B8R82Plane422UnormKHR, {3u, 2u}},
  {Format::eG8B8R83Plane444Unorm, {3u, 3u}},
  {Format::eG8B8R83Plane444UnormKHR, {3u, 3u}},
  {Format::eR10X6UnormPack16, {2u, 1u}},
  {Format::eR10X6UnormPack16KHR, {2u, 1u}},
  {Format::eR10X6G10X6Unorm2Pack16, {4u, 2u}},
  {Format::eR10X6G10X6Unorm2Pack16KHR, {4u, 2u}},
  {Format::eR10X6G10X6B10X6A10X6Unorm4Pack16, {8u, 4u}},
  {Format::eR10X6G10X6B10X6A10X6Unorm4Pack16KHR, {8u, 4u}},
  {Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16, {8u, 4u}},
  {Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16KHR, {8u, 4u}},
  {Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16, {8u, 4u}},
  {Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16KHR, {8u, 4u}},
  {Format::eG10X6B10X6R10X63Plane420Unorm3Pack16, {6u, 3u}},
  {Format::eG10X6B10X6R10X63Plane420Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG10X6B10X6R10X62Plane420Unorm3Pack16, {6u, 3u}},
  {Format::eG10X6B10X6R10X62Plane420Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG10X6B10X6R10X63Plane422Unorm3Pack16, {6u, 3u}},
  {Format::eG10X6B10X6R10X63Plane422Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG10X6B10X6R10X62Plane422Unorm3Pack16, {6u, 3u}},
  {Format::eG10X6B10X6R10X62Plane422Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG10X6B10X6R10X63Plane444Unorm3Pack16, {6u, 3u}},
  {Format::eG10X6B10X6R10X63Plane444Unorm3Pack16KHR, {6u, 3u}},
  {Format::eR12X4UnormPack16, {2u, 1u}},
  {Format::eR12X4UnormPack16KHR, {2u, 1u}},
  {Format::eR12X4G12X4Unorm2Pack16, {4u, 2u}},
  {Format::eR12X4G12X4Unorm2Pack16KHR, {4u, 2u}},
  {Format::eR12X4G12X4B12X4A12X4Unorm4Pack16, {8u, 4u}},
  {Format::eR12X4G12X4B12X4A12X4Unorm4Pack16KHR, {8u, 4u}},
  {Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16, {8u, 4u}},
  {Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16KHR, {8u, 4u}},
  {Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16, {8u, 4u}},
  {Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16KHR, {8u, 4u}},
  {Format::eG12X4B12X4R12X43Plane420Unorm3Pack16, {6u, 3u}},
  {Format::eG12X4B12X4R12X43Plane420Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG12X4B12X4R12X42Plane420Unorm3Pack16, {6u, 3u}},
  {Format::eG12X4B12X4R12X42Plane420Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG12X4B12X4R12X43Plane422Unorm3Pack16, {6u, 3u}},
  {Format::eG12X4B12X4R12X43Plane422Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG12X4B12X4R12X42Plane422Unorm3Pack16, {6u, 3u}},
  {Format::eG12X4B12X4R12X42Plane422Unorm3Pack16KHR,{6u, 3u}},
  {Format::eG12X4B12X4R12X43Plane444Unorm3Pack16, {6u, 3u}},
  {Format::eG12X4B12X4R12X43Plane444Unorm3Pack16KHR, {6u, 3u}},
  {Format::eG16B16G16R16422Unorm, {8u, 4u}},
  {Format::eG16B16G16R16422UnormKHR, {8u, 4u}},
  {Format::eB16G16R16G16422Unorm, {8u, 4u}},
  {Format::eB16G16R16G16422UnormKHR, {8u, 4u}},
  {Format::eG16B16R163Plane420Unorm, {6u, 3u}},
  {Format::eG16B16R163Plane420UnormKHR, {6u, 3u}},
  {Format::eG16B16R162Plane420Unorm, {6u, 2u}},
  {Format::eG16B16R162Plane420UnormKHR, {6u, 2u}},
  {Format::eG16B16R163Plane422Unorm, {6u, 3u}},
  {Format::eG16B16R163Plane422UnormKHR, {6u, 3u}},
  {Format::eG16B16R162Plane422Unorm, {6u, 2u}},
  {Format::eG16B16R162Plane422UnormKHR, {6u, 2u}},
  {Format::eG16B16R163Plane444Unorm, {6u, 3u}},
  {Format::eG16B16R163Plane444UnormKHR, {6u, 3u}},
  {Format::ePvrtc12BppUnormBlockIMG, {8u, 4u}},
  {Format::ePvrtc14BppUnormBlockIMG, {8u, 4u}},
  {Format::ePvrtc22BppUnormBlockIMG, {8u, 4u}},
  {Format::ePvrtc24BppUnormBlockIMG, {8u, 4u}},
  {Format::ePvrtc12BppSrgbBlockIMG, {8u, 4u}},
  {Format::ePvrtc14BppSrgbBlockIMG, {8u, 4u}},
  {Format::ePvrtc22BppSrgbBlockIMG, {8u, 4u}},
  {Format::ePvrtc24BppSrgbBlockIMG, {8u, 4u}}
};

}

#endif // LSG_RESOURCES_TABLE_H
