export module util.rendering;

import util.glm;
import util.vector;
import <ranges>;
import <algorithm>;
import <stdexcept>;

export namespace render {
export template <typename T> struct RenTri {
  const T a, b, c;

  RenTri(const T &a, const T &b, const T &c) : a{a}, b{b}, c{c} {}
  RenTri(const T &n) : RenTri<T>(n, n, n) {}

  RenTri(const RenTri<T> &) = default;
  RenTri(RenTri<T> &&) = default;
  RenTri<T> &operator=(const RenTri<T> &) = default;
  RenTri<T> &operator=(RenTri<T> &&) = default;

  const T &operator[](const unsigned char i) const {
    switch (i) {
    case 0:
      return a;
    case 1:
      return b;
    case 2:
      return c;
    default:
      throw std::out_of_range{"INVALID TRI INDEX"};
    }
  }
};

export template <typename T> using RenFace = Vector<RenTri<T>>;

export using Index = unsigned short;
export using IndexTri = RenTri<Index>;
export using IndexFace = RenFace<Index>;
export using IndexList = Vector<IndexFace>;

export using Col = glm::u8vec3;
export using ColTri = RenTri<Col>;
export using ColFace = RenFace<Col>;
export using ColList = Vector<ColFace>;

export using Tex = Vec2;
export using TexTri = RenTri<Tex>;
export using TexFace = RenFace<Tex>;
export using TexList = Vector<TexFace>;

export template <typename VertexType>
RenFace<VertexType> repeatTris(const unsigned int n,
                               const RenTri<VertexType> &tri) {
  return vector_util::mapVectorRange<RenTri<VertexType>>(
      0, n, [&tri](const unsigned int &) { return tri; });
}

export template <typename VertexType>
Vector<RenFace<VertexType>> repeatFaces(const unsigned int n,
                                        const RenFace<VertexType> &face) {
  return vector_util::mapVectorRange<RenFace<VertexType>>(
      0, n, [&face](const unsigned int &) { return face; });
}
} // namespace render