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

#include "lsg/resources/Geometry.h"

namespace lsg {

Geometry::Geometry() : Identifiable("Geometry") {}

void Geometry::setIndices(const BufferAccessor& indices) {
  throwIf<InvalidArgument>(indices.count() % 3u != 0u, "Tried to set triangle indices that are not multiple of 3.");
  indices_ = indices;
}

void Geometry::setVertices(const TBufferAccessor<glm::vec3>& vertices) {
  vertices_ = vertices;

  bounding_box_.reset();

  for (size_t i = 0; i < vertices_->count(); i++) {
    bounding_box_.expand((*vertices_)[i]);
  }
}

void Geometry::setNormals(const TBufferAccessor<glm::vec3>& normals) {
  normals_ = normals;
}

void Geometry::setTangents(const TBufferAccessor<glm::vec4>& tangents) {
  tangents_ = tangents;
}

void Geometry::setColors(const BufferAccessor& colors) {
  colors_ = colors;
}

void Geometry::setUv(size_t index, const BufferAccessor& uv) {
  throwIf<OutOfRange>(index > uv_.size(), "Cannot bind uv-s on index (" + std::to_string(index) + "). Max index is " +
                                            std::to_string(uv_.size() - 1) + ".");
  uv_[index] = uv;
}

const BufferAccessor& Geometry::getIndices() const {
  return indices_.value();
}

const TBufferAccessor<glm::vec3>& Geometry::getVertices() const {
  return vertices_.value();
}

const TBufferAccessor<glm::vec3>& Geometry::getNormals() const {
  return normals_.value();
}

const TBufferAccessor<glm::vec4>& Geometry::getTangents() const {
  return tangents_.value();
}

const BufferAccessor& Geometry::getColors() const {
  return colors_.value();
}

const BufferAccessor& Geometry::getUv(const size_t index) const {
  return uv_[index].value();
}

const AABB<float>& Geometry::getBoundingBox() const {
  return bounding_box_;
}

void Geometry::clearVertices() {
  vertices_.reset();
  bounding_box_.reset();
}

void Geometry::clearNormals() {
  normals_.reset();
}

void Geometry::clearIndices() {
  indices_.reset();
}

void Geometry::clearTangents() {
  tangents_.reset();
}

void Geometry::clearColors() {
  colors_.reset();
}

void Geometry::clearUv(const size_t index) {
  throwIf<OutOfRange>(index > uv_.size(), "Cannot bind uv-s on index (" + std::to_string(index) + "). Max index is " +
                                            std::to_string(uv_.size() - 1) + ".");
  uv_[index].reset();
}

bool Geometry::hasVertices() const {
  return vertices_.has_value();
}

bool Geometry::hasNormals() const {
  return normals_.has_value();
}

bool Geometry::hasIndices() const {
  return indices_.has_value();
}

bool Geometry::hasTangents() const {
  return tangents_.has_value();
}

bool Geometry::hasColors() const {
  return colors_.has_value();
}

bool Geometry::hasUv(const size_t index) const {
  throwIf<OutOfRange>(index > uv_.size(), "Cannot bind uv-s on index (" + std::to_string(index) + "). Max index is " +
                                            std::to_string(uv_.size() - 1) + ".");
  return uv_[index].has_value();
}

std::shared_ptr<TriangleAccessor<glm::vec3>> Geometry::getTrianglePositionAccessor() const {
  throwIf<IllegalInvocation>(!vertices_.has_value(),
                             "Tried to create TriangleAccessor for geometry without vertex positions.");

  if (indices_.has_value()) {
    if (indices_.value().elementSize() == sizeof(uint16_t)) {
      return std::make_shared<IndexedTriAccessor<uint16_t, glm::vec3>>(vertices_.value(),
                                                                       TBufferAccessor<uint16_t>(indices_.value()));
    }

    if (indices_.value().elementSize() == sizeof(uint32_t)) {
      return std::make_shared<IndexedTriAccessor<uint32_t, glm::vec3>>(vertices_.value(),
                                                                       TBufferAccessor<uint32_t>(indices_.value()));
    }

    throw IllegalInvocation("Unknown index type.");
  }

  return std::make_shared<TriAccessor<glm::vec3>>(vertices_.value());
}

std::shared_ptr<TriangleAccessor<glm::vec3>> Geometry::getTriangleNormalAccessor() const {
  throwIf<IllegalInvocation>(!normals_.has_value(),
                             "Tried to create TriangleAccessor for geometry without vertex normals.");

  if (indices_.has_value()) {
    if (indices_.value().elementSize() == sizeof(uint16_t)) {
      return std::make_shared<IndexedTriAccessor<uint16_t, glm::vec3>>(normals_.value(),
                                                                       TBufferAccessor<uint16_t>(indices_.value()));
    }

    if (indices_.value().elementSize() == sizeof(uint32_t)) {
      return std::make_shared<IndexedTriAccessor<uint32_t, glm::vec3>>(normals_.value(),
                                                                       TBufferAccessor<uint32_t>(indices_.value()));
    }

    throw IllegalInvocation("Unknown index type.");
  }

  return std::make_shared<TriAccessor<glm::vec3>>(normals_.value());
}

std::shared_ptr<TriangleAccessor<glm::vec4>> Geometry::getTriangleTangentAccessor() const {
  throwIf<IllegalInvocation>(!tangents_.has_value(),
                             "Tried to create TriangleAccessor for geometry without vertex tangents.");

  if (indices_.has_value()) {
    if (indices_.value().elementSize() == sizeof(uint16_t)) {
      return std::make_shared<IndexedTriAccessor<uint16_t, glm::vec4>>(tangents_.value(),
                                                                       TBufferAccessor<uint16_t>(indices_.value()));
    }

    if (indices_.value().elementSize() == sizeof(uint32_t)) {
      return std::make_shared<IndexedTriAccessor<uint32_t, glm::vec4>>(tangents_.value(),
                                                                       TBufferAccessor<uint32_t>(indices_.value()));
    }

    throw IllegalInvocation("Unknown index type.");
  }

  return std::make_shared<TriAccessor<glm::vec4>>(tangents_.value());
}

} // namespace lsg
