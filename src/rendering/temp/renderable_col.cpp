module;

#include "util/gl_utils.hpp"

module rendering.renderable_col;

import wrapper.program.global_programs;

RenderableCol::RenderableCol(const EBO &ebo, const VBO &vbo,
                             const Vec3List &coordinates,
                             const render::IndexList &indexList,
                             const render::ColList &colList)
    : BaseRenderable<VertexFormats::_3D::Colored>(Programs::COL_PROGRAM, ebo,
                                                  vbo, coordinates, indexList),
      colList{colList} {}

bool RenderableCol::exceptionCondition() {
  return indexList.size() != colList.size();
}

void RenderableCol::specializeConstruction() {
  for (auto f = 0; f < indexList.size(); f++) {
    const render::IndexFace &indexFace = indexList[f];
    for (auto t = 0; t < indexFace.size(); t++) {
      const render::IndexTri &indexTri = indexFace[t];
      for (auto v = 0; v < 3; v++) {
        const render::Index indexVertex = indexTri[v];
        const Vec3 &coordinate = coordinates[indexVertex];

        const render::Col &colVertex = colList[f][t][v];

        vertexInfo.emplace_back(VertexFormats::_3D::Colored{
            coordinate[0], coordinate[1], coordinate[2], colVertex[0],
            colVertex[1], colVertex[2]});
      }
    }
  }
}

// void RenderableCol::specializeFaceInfo(const unsigned short f) {
//
// }
// void RenderableCol::specializeTriInfo(const unsigned short f,
//                                       const unsigned short t) {}
// void RenderableCol::specializeVertexInfo(const unsigned short f,
//                                          const unsigned short t,
//                                          const unsigned short v) {}