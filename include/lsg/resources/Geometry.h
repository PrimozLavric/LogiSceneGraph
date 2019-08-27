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

#ifndef LSG_RESOURCES_GEOMETRY_H
#define LSG_RESOURCES_GEOMETRY_H

#include <array>
#include <optional>
#include "lsg/core/Ref.h"
#include "lsg/math/AABB.h"
#include "lsg/resources/BufferAccessor.h"
#include "lsg/resources/Triangle.h"

namespace lsg {

class Geometry : public Identifiable, public RefCounter<Geometry> {
 public:
  Geometry();

  void setIndices(const BufferAccessor& indices);

  void setVertices(const TBufferAccessor<glm::tvec3<float>>& vertices);

  void setNormals(const TBufferAccessor<glm::tvec3<float>>& normals);

  void setTangents(const TBufferAccessor<glm::tvec4<float>>& tangents);

  void setColors(const BufferAccessor& colors);

  void setUv(size_t index, const BufferAccessor& uv);

  const BufferAccessor& getIndices() const;

  const TBufferAccessor<glm::vec3>& getVertices() const;

  const TBufferAccessor<glm::vec3>& getNormals() const;

  const TBufferAccessor<glm::vec4>& getTangents() const;

  const BufferAccessor& getColors() const;

  const BufferAccessor& getUv(size_t index) const;

  const AABB<float>& getBoundingBox() const;

  void clearVertices();

  void clearNormals();

  void clearIndices();

  void clearTangents();

  void clearColors();

  void clearUv(size_t index);

  bool hasVertices() const;

  bool hasNormals() const;

  bool hasIndices() const;

  bool hasTangents() const;

  bool hasColors() const;

  bool hasUv(size_t index) const;

  Ref<TriangleAccessor<glm::vec3>> getTrianglePositionAccessor() const;

  Ref<TriangleAccessor<glm::vec3>> getTriangleNormalAccessor() const;

  Ref<TriangleAccessor<glm::vec2>> getTriangleUVAccessor(size_t index) const;

  Ref<TriangleAccessor<glm::vec4>> getTriangleTangentAccessor() const;

 protected:
  template <typename IndexT, typename T>
  class IndexedTriAccessor : public TriangleAccessor<T> {
   public:
    IndexedTriAccessor(TBufferAccessor<T> vertex_data, TBufferAccessor<IndexT> indices)
      : vertex_data_(std::move(vertex_data)), indices_(std::move(indices)) {}

    size_t count() const override {
      return indices_.count() / 3;
    }

    Triangle<T> operator[](size_t index) const override {
      return Triangle<T>(vertex_data_[indices_[index * 3u]], vertex_data_[indices_[index * 3u + 1u]],
                         vertex_data_[indices_[index * 3u + 2u]]);
    }

   private:
    TBufferAccessor<T> vertex_data_;
    TBufferAccessor<IndexT> indices_;
  };

  template <typename T>
  class TriAccessor : public TriangleAccessor<T> {
   public:
    explicit TriAccessor(TBufferAccessor<T> vertex_data) : vertex_data_(std::move(vertex_data)) {}

    size_t count() const override {
      return vertex_data_.count() / 3;
    }

    Triangle<T> operator[](size_t index) const override {
      return Triangle<T>(vertex_data_[index * 3u], vertex_data_[index * 3u + 1u], vertex_data_[index * 3u + 2u]);
    }

   private:
    TBufferAccessor<T> vertex_data_;
  };

 private:
  /**
   * Indices. Must be unsigned short or unsigned int scalars.
   */
  std::optional<BufferAccessor> indices_;

  /**
   * Vertices.
   */
  std::optional<TBufferAccessor<glm::tvec3<float>>> vertices_;

  /**
   * Normals.
   */
  std::optional<TBufferAccessor<glm::tvec3<float>>> normals_;

  /**
   * Tangents.
   */
  std::optional<TBufferAccessor<glm::tvec4<float>>> tangents_;

  /**
   * Vertex colors. Must have vec3 or vec4 structure and float or normalized component type.
   */
  std::optional<BufferAccessor> colors_;

  /**
   * Uv coordinates. Must have components of float or normalized type.
   */
  std::array<std::optional<BufferAccessor>, 8u> uv_;

  /**
   * Bounding box that tightly encapsulates geometry vertices.
   */
  AABB<float> bounding_box_;
};

} // namespace lsg

#endif // LSG_RESOURCES_GEOMETRY_H
