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

export template <typename T> RenTri<T> triFromList(const Vector<T> &t) {
  return {t[0], t[1], t[2]};
}

export template <typename VertexType>
RenFace<VertexType> fromTris(const Vector<Vector<VertexType>> &tris) {
  return vector_util::mapVector<Vector<VertexType>, RenTri<VertexType>>(
      tris, [](const auto &triList) { return triFromList(triList); });
}

export template <typename VertexType>
Vector<RenFace<VertexType>> fromFace(const unsigned int n,
                                     const Vector<Vector<VertexType>> &tris) {
  using namespace vector_util;
  const RenFace<VertexType> face = fromTris(tris);
  return vector_util::mapVector<unsigned int, RenFace<VertexType>>(
      vector_util::range(0, n), [&face](const unsigned int &) { return face; });
}
} // namespace render