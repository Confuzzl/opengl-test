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
  //for (unsigned char faceIndex = 0; const auto &face : faceVertexIndices) {
  //  const auto &texture = TexTile::getRandomTexture();
  //  for (unsigned char vertexIndex = 0; const auto &vertex : face) {
  //    const Vec3 &pos = coordinates[vertex];

  //    const auto &uvLocal = UVs[faceIndex][vertexIndex];
  //    const TexTile tex = TexTile::getTile(texture, app.atlas);
  //    const glm::lowp_u16vec2 uvGlobal = {
  //        tex.coordinates +
  //        (glm::lowp_u16vec2)((Vec2)tex.dimensions * uvLocal)};

  //    std::cout << vertexInfo.emplace_back(pos[0], pos[1], pos[2], UCHAR_MAX,
  //                                         UCHAR_MAX, UCHAR_MAX, uvGlobal[0],
  //                                         uvGlobal[1])
  //              << "\n";
  //    vertexIndex++;
  //  }
  //  faceIndex++;
  //}

  for (unsigned short faceIndex = 0; const auto &face : UVs) {
    for (unsigned short triIndex = 0; const auto &tri : face.tris) {
      for (unsigned char triVertexIndex = 0; triVertexIndex < 3;
           triVertexIndex++) {
        /*const Vec3 &pos = coordinates[faceVertexIndices[faceIndex]]*/

        const auto &uvLocal = tri[triVertexIndex];
      }
      triIndex++;
    }
    faceIndex++;
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