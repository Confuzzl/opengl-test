module;

#include "util/gl_utils.hpp"

module rendering.renderable_tex;

import app.texture_tile;
import app.app;

import wrapper.program.global_programs;

RenderableTex::RenderableTex(const EBO &ebo, const VBO &vbo,
                             const Vec3List &coordinates,
                             const render::IndexList &indexList,
                             const render::TexList &texList)
    : BaseRenderable<VertexFormats::_3D::Textured>(Programs::TEX_PROGRAM, ebo,
                                                   vbo, coordinates, indexList),
      texList{texList} {}

bool RenderableTex::exceptionCondition() {
  return indexList.size() != texList.size();
}

void RenderableTex::specializeConstruction() {
  for (auto f = 0; f < indexList.size(); f++) {
    const render::IndexFace &indexFace = indexList[f];

    const TexTile &texture{TexTile::getRandomTile(*mainApp.atlas)};

    for (auto t = 0; t < indexFace.size(); t++) {
      const render::IndexTri &indexTri = indexFace[t];
      for (auto v = 0; v < 3; v++) {
        const render::Index indexVertex = indexTri[v];
        const Vec3 &coordinate = coordinates[indexVertex];

        const render::Tex &texVertex = texList[f][t][v];
        const TexTile::IntUV intUV{texture.globalIntUV(texVertex)};

        vertexInfo.emplace_back(VertexFormats::_3D::Textured{
            coordinate[0], coordinate[1], coordinate[2], intUV[0], intUV[1]});
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