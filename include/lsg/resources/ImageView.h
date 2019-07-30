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

#ifndef CPUPATHTRACER_IMAGEVIEW_H
#define CPUPATHTRACER_IMAGEVIEW_H

namespace lsg {

template <typename T>
class ImageView {
 public:
  explicit ImageView(Image& image);

  explicit ImageView(const lsg::Ref<Image>& image);

  size_t width() const;

  size_t height() const;

  size_t depth() const;

  T& at(size_t x, size_t y = 0u, size_t z = 0u);

  const T& at(size_t x, size_t y = 0u, size_t z = 0u) const;

 private:
  std::reference_wrapper<Image> image_;
};

template <typename T>
ImageView<T>::ImageView(Image& image) : image_(image) {
  throwIf<InvalidArgument>(image_.get().pixelSize() != sizeof(T),
                           util::strCat("Pixel size [", image_.get().pixelSize(),
                                        "] does not match the size of the type T [", sizeof(T), "]."));
}

template <typename T>
ImageView<T>::ImageView(const lsg::Ref<Image>& image) : image_(*image) {
  throwIf<InvalidArgument>(image_.get().pixelSize() != sizeof(T),
                           util::strCat("Pixel size [", image_.get().pixelSize(),
                                        "] does not match the size of the type T [", sizeof(T), "]."));
}

template <typename T>
size_t ImageView<T>::width() const {
  return image_.get().width();
}

template <typename T>
size_t ImageView<T>::height() const {
  return image_.get().height();
}

template <typename T>
size_t ImageView<T>::depth() const {
  return image_.get().depth();
}

template <typename T>
T& ImageView<T>::at(size_t x, size_t y, size_t z) {
  return reinterpret_cast<T&>(*image_.get().at(x, y, z));
}

template <typename T>
const T& ImageView<T>::at(size_t x, size_t y, size_t z) const {
  return reinterpret_cast<const T&>(*image_.get().at(x, y, z));
}

} // namespace lsg

#endif // CPUPATHTRACER_IMAGEVIEW_H
