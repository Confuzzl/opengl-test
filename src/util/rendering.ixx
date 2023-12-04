export module util.rendering;

import util.glm;
import util.vector;
import <ranges>;
import <algorithm>;

export namespace render {
export template <typename T> using RenTri = Array<T, 3>;
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
RenTri<VertexType> tri(VertexType a, VertexType b, VertexType c) {
  return {a, b, c};
}

export template <typename T> RenTri<T> tri(const std::initializer_list<T> &t) {
  static_assert(t.size() == 3);
  return {t};
}

export template <typename VertexType>
Vector<RenFace<VertexType>> fromFace(const std::size_t n,
                                     const RenFace<VertexType> &face) {
  Vector<RenFace<VertexType>> out{};
  out.reserve(n);
  for (std::size_t i = 0; i < n; i++)
    out.emplace_back(face);
  return out;
}

export /*template <typename VertexType>*/
    RenFace<int>
    fromTris(const Vector<std::initializer_list<int>> &tris) {
  RenFace<int> out;
  out.reserve(tris.size());
  for (const auto tri : tris) {
    out.emplace_back(render::tri(tri));
  }
  const auto a =
      std::ranges::views::transform(tris, [](const auto &e) { return e });
  return out;
}

} // namespace render