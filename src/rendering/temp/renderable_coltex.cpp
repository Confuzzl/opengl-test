module;

#include "util/gl_utils.hpp"

module rendering.renderable_coltex;

import app.texture_tile;
import app.app;

// import wrapper.program.global_programs;
import shaders.global;

RenderableColTex::RenderableColTex(const EBO &ebo, const VBO &vbo,
                                   const Vec3List &coordinates,
                                   const render::IndexList &indexList,
                                   const render::ColList &colList,
                                   const render::TexList &texList)
    : BaseRenderable<VertexFormats::_3D::ColTex>(Shaders::_3D::COLTEX, ebo, vbo,
                                                 coordinates, indexList),
      colList{colList}, texList{texList} {}

bool RenderableColTex::exceptionCondition() {
  return not(indexList.size() == colList.size() &&
             colList.size() == texList.size());
}

void RenderableColTex::specializeConstruction() {
  for (auto f = 0; f < indexList.size(); f++) {
    const render::IndexFace &indexFace = indexList[f];

    const TexTile &texture{TexTile::getRandomTile(*mainApp.atlas)};

    for (auto t = 0; t < indexFace.size(); t++) {
      const render::IndexTri &indexTri = indexFace[t];
      for (auto v = 0; v < 3; v++) {
        const render::Index indexVertex = indexTri[v];
        const Vec3 &coordinate = coordinates[indexVertex];

        const render::Col &colVertex = colList[f][t][v];

        const render::Tex &texVertex = texList[f][t][v];
        const TexTile::IntUV intUV{texture.globalIntUV(texVertex)};

        vertexInfo.emplace_back(VertexFormats::_3D::ColTex{
            coordinate[0], coordinate[1], coordinate[2], colVertex[0],
            colVertex[1], colVertex[2], intUV[0], intUV[1]});
      }
    }
  }
}