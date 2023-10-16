module;

#include "util/gl_utils.hpp"
#include <limits>

module world.collision.prism;

import app.app;
import app.texture_tile;
import util.debug;
import util.math;

bool Prism::buffersInitialized = false;
EBO Prism::ebo{};
VBO Prism::sharedVBO{};
void Prism::initializeBuffers() {
  buffersInitialized = true;
  allocateVBO();
  initializeEBO();
}
void Prism::initializeEBO() {
  ebo.allocateBufferObject(sizeof(indices));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, indices);
  std::cout << std::format("ebo {} for prism allocated and initialized\n",
                           ebo.ID);
}

void Prism::allocateVBO() {
  sharedVBO.allocateBufferObject(36 * SimpleVertex::WIDTH);
  std::cout << std::format("shared vbo {} for prism allocated\n", sharedVBO.ID);
}

void Prism::writeToVBO() {
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
  // std::cout << std::format("shared vbo {} for prism initialized\n",
  //                          sharedVBO.ID);
}

const GLuint Prism::indices[36] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
const Vec3 Prism::maps[6][2][3]{{{{-1, -1, +1}, {+1, -1, +1}, {+1, +1, +1}},
                                 {{-1, -1, +1}, {+1, +1, +1}, {-1, +1, +1}}},
                                {{{+1, -1, +1}, {+1, -1, -1}, {+1, +1, -1}},
                                 {{+1, -1, +1}, {+1, +1, -1}, {+1, +1, +1}}},
                                {{{+1, -1, -1}, {-1, -1, -1}, {-1, +1, -1}},
                                 {{+1, -1, -1}, {-1, +1, -1}, {+1, +1, -1}}},
                                {{{-1, -1, -1}, {-1, -1, +1}, {-1, +1, +1}},
                                 {{-1, -1, -1}, {-1, +1, +1}, {-1, +1, -1}}},
                                {{{+1, +1, +1}, {+1, +1, -1}, {-1, +1, -1}},
                                 {{+1, +1, +1}, {-1, +1, -1}, {-1, +1, +1}}},
                                {{{-1, -1, +1}, {-1, -1, -1}, {+1, -1, -1}},
                                 {{-1, -1, +1}, {+1, -1, -1}, {+1, -1, +1}}}};

unsigned int Prism::COUNT = 0;
Prism::Prism(const float width, const float height, const float depth)
    : halfsize{width / 2, height / 2, depth / 2}, ID{COUNT++} {
  if (not buffersInitialized)
    initializeBuffers();

  for (int i = 0; i < 6; i++)
    setFace(Direction(i), TexTile::getRandomTexture());

  app.scene.objects.insert(this);
}
Prism::~Prism() {
  app.scene.objects.erase(this);
  std::cout << std::format("prism {} destroyed\n", ID);
}

void Prism::printVertices() {
  for (int i = 0; i < 36; i++)
    printVertex(i);
}
void Prism::printVertex(const int index) {
  std::cout << std::format(
      "vertex {}: ({},{},{}),({},{},{}),({},{})\n", index,
      vertexInfo[index].posInfo[0], vertexInfo[index].posInfo[1],
      vertexInfo[index].posInfo[2], vertexInfo[index].colInfo[0],
      vertexInfo[index].colInfo[1], vertexInfo[index].colInfo[2],
      vertexInfo[index].texInfo[0], vertexInfo[index].texInfo[1]);
}
void Prism::setFace(const Direction direction, std::string texture) {
  setTri(direction, 0, texture);
  setTri(direction, 1, texture);
}
void Prism::setTri(const Direction direction, const int tri,
                   std::string texture) {
  setVertexInfo(direction, tri, 0, texture);
  setVertexInfo(direction, tri, 1, texture);
  setVertexInfo(direction, tri, 2, texture);
}
void Prism::setVertexInfo(const Direction direction, const int tri,
                          const int vertex, std::string texture) {
  const int absolute = direction * 6 + tri * 3 + vertex;
  const Vec3 pos = maps[direction][tri][vertex] * halfsize;

  const TexTile tex = TexTile::getTile(texture, app.atlas);
  const glm::lowp_u16vec2 coordinate{tex.coordinates +
                                     tex.dimensions * QUAD_UVS[tri][vertex]};

  vertexInfo[absolute] = {pos[0],    pos[1],    pos[2],        UCHAR_MAX,
                          UCHAR_MAX, UCHAR_MAX, coordinate[0], coordinate[1]};
}