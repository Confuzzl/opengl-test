module;

#include "util/gl_utils.hpp"
#include <limits>

module rendering.renderable;

import app.app;
import app.texture_tile;
import util.math;
import util.debug;

Renderable::Renderable(const EBO &ebo, const VBO &sharedVBO,
                       const Vec3List &coordinates,
                       const render::IndexList &faceVertexIndices,
                       const render::TexList &UVs)
    : BasePolyhedron(coordinates), ebo{ebo}, sharedVBO{sharedVBO},
      faceVertexIndices{faceVertexIndices}, UVs{UVs} {
  if (faceVertexIndices.size() != UVs.size())
    throw FaceUVMismatchException{
        std::format("UV LIST SIZE DOES NOT MATCH FACE COUNT ({} != {})\n",
                    faceVertexIndices.size(), UVs.size())};

  initializeVertexInfo();
}

void Renderable::initializeVertexInfo() {
  for (unsigned short f = 0; f < UVs.size(); f++) {
    const auto &indexFace = faceVertexIndices[f];
    const auto &uvFace = UVs[f];

    const auto &texture = TexTile::getRandomTexture();
    const TexTile tex{TexTile::getTile(texture, *mainApp.atlas)};

    for (unsigned short t = 0; t < UVs[f].size(); t++) {
      const auto &indexTri = faceVertexIndices[f][t];
      const auto &uvTri = UVs[f][t];
      for (unsigned char v = 0; v < 3; v++) {
        const unsigned short &indexVertex = faceVertexIndices[f][t][v];
        const Vec2 &uvVertex = UVs[f][t][v];

        const Vec3 &pos = coordinates[indexVertex];

        const glm::lowp_u16vec2 uvGlobal{
            tex.coordinates +
            static_cast<glm::lowp_u16vec2>(static_cast<Vec2>(tex.dimensions) *
                                           uvVertex)};

        vertexInfo.emplace_back(pos[0], pos[1], pos[2], UCHAR_MAX, UCHAR_MAX,
                                UCHAR_MAX, uvGlobal[0], uvGlobal[1]);
      }
    }
  }
}

void Renderable::writeToSharedVBO() const {
  GLintptr offset = 0;
  for (const VertexFormats::_3D::ColTex &vertex : vertexInfo) {
    glNamedBufferSubData(sharedVBO.ID, offset,
                         VertexFormats::_3D::ColTex::POS_WIDTH,
                         vertex.posInfo.data());
    offset += VertexFormats::_3D::ColTex::POS_WIDTH;
    glNamedBufferSubData(sharedVBO.ID, offset,
                         VertexFormats::_3D::ColTex::COL_WIDTH,
                         vertex.colInfo.data());
    offset += VertexFormats::_3D::ColTex::COL_WIDTH;
    glNamedBufferSubData(sharedVBO.ID, offset,
                         VertexFormats::_3D::ColTex::TEX_WIDTH,
                         vertex.texInfo.data());
    offset += VertexFormats::_3D::ColTex::TEX_WIDTH;
  }
}