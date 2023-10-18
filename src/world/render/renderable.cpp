module;

#include "util/gl_utils.hpp"
#include <limits>

module world.render.renderable;

import app.app;
import app.texture_tile;
import util.math;
import util.debug;

Renderable::Renderable(EBO &ebo, VBO &sharedVBO, const Vec3List &coordinates,
                       const RFaceCoordinateIndexList &faceVertexIndices,
                       const RFaceUVList &UVs)
    : BasePolyhedron(coordinates), ebo{ebo}, sharedVBO{sharedVBO},
      faceVertexIndices{faceVertexIndices}, UVs{UVs} {
  if (faceVertexIndices.size() != UVs.size())
    throw FaceUVMismatchException{
        std::format("UV LIST SIZE DOES NOT MATCH FACE COUNT ({} != {})\n",
                    faceVertexIndices.size(), UVs.size())};

  initializeVertexInfo();
}

void Renderable::initializeVertexInfo() {
  // for (unsigned char f = 0; const auto &face : faceVertexIndices) {
  //   const auto &texture = TexTile::getRandomTexture();
  //   for (unsigned char v = 0; const auto &vertex : face) {
  //     const Vec3 &pos = coordinates[vertex];

  //    const auto &uvLocal = UVs[f][v];
  //    const TexTile tex = TexTile::getTile(texture, app.atlas);
  //    const glm::lowp_u16vec2 uvGlobal = {
  //        tex.coordinates +
  //        (glm::lowp_u16vec2)((Vec2)tex.dimensions * uvLocal)};

  //    std::cout << vertexInfo.emplace_back(pos[0], pos[1], pos[2], UCHAR_MAX,
  //                                         UCHAR_MAX, UCHAR_MAX, uvGlobal[0],
  //                                         uvGlobal[1])
  //              << "\n";
  //    v++;
  //  }
  //  f++;
  //}

  for (unsigned short f = 0; f < UVs.size(); f++) {
    const auto &indexFace = faceVertexIndices[f];
    const auto &uvFace = UVs[f];

    const auto &texture = TexTile::getRandomTexture();
    for (unsigned short t = 0; t < UVs[f].size(); t++) {
      const auto &indexTri = faceVertexIndices[f][t];
      const auto &uvTri = UVs[f][t];
      for (unsigned short v = 0; v < UVs[f][t].size(); v++) {
        const unsigned short &indexVertex = faceVertexIndices[f][t][v];
        const Vec2 &uvVertex = UVs[f][t][v];

        const Vec3 &pos = coordinates[indexVertex];
        const TexTile tex = TexTile::getTile(texture, app.atlas);
        const glm::lowp_u16vec2 uvGlobal =
            tex.coordinates + static_cast<glm::lowp_u16vec2>(
                                  static_cast<Vec2>(tex.dimensions) * uvVertex);

        vertexInfo.emplace_back(pos[0], pos[1], pos[2], UCHAR_MAX, UCHAR_MAX,
                                UCHAR_MAX, uvGlobal[0], uvGlobal[1]);
      }
    }
  }
}

void Renderable::writeToSharedVBO() {
  GLintptr offset = 0;
  for (const SimpleVertex &vertex : vertexInfo) {
    glNamedBufferSubData(sharedVBO.ID, offset, SimpleVertex::POS_WIDTH,
                         vertex.posInfo);
    offset += SimpleVertex::POS_WIDTH;
    glNamedBufferSubData(sharedVBO.ID, offset, SimpleVertex::COL_WIDTH,
                         vertex.colInfo);
    offset += SimpleVertex::COL_WIDTH;
    glNamedBufferSubData(sharedVBO.ID, offset, SimpleVertex::TEX_WIDTH,
                         vertex.texInfo);
    offset += SimpleVertex::TEX_WIDTH;
  }
}