module;

#include "util/gl_utils.hpp"
#include <numeric>

module world.factory.simplex_factory;

import util.debug;

const VertexNeighborList SimplexFactory::veIndices{
    {0, 2, 4}, {0, 1, 5}, {1, 2, 3}, {3, 4, 5}};
const EdgeNeighborList SimplexFactory::evIndices{{0, 1}, {1, 2}, {2, 0},
                                                 {2, 3}, {0, 3}, {1, 3}};
const EdgeNeighborList SimplexFactory::efIndices{{0, 2}, {0, 3}, {0, 1},
                                                 {1, 3}, {2, 1}, {3, 2}};
const FaceNeighborList SimplexFactory::feIndices{
    {0, 1, 2}, {2, 3, 4}, {0, 4, 5}, {1, 5, 3}};

const RFaceCoordinateIndexList SimplexFactory::fvIndices{
    {{0, 1, 2}}, {{0, 2, 3}}, {{1, 0, 3}}, {{2, 1, 3}}};

UPtr<Collider>
SimplexFactory::createCollidableSimplex(const Vec3List &coordinates) {
  return std::make_unique<Collider>(4, 4, coordinates, veIndices, evIndices,
                                    efIndices, feIndices);
}

UPtr<Renderable>
SimplexFactory::createRenderableSimplex(const Vec3List &coordinates) {
  if (not buffersInitialized)
    initializeBuffers();

  return std::make_unique<Renderable>(
      ebo, sharedVBO, coordinates, fvIndices,
      RFaceUVList{{{Vec2{0, 0}, Vec2{1, 0}, Vec2{0.5, 1}}},
                  {{Vec2{0, 0}, Vec2{1, 0}, Vec2{0.5, 1}}},
                  {{Vec2{0, 0}, Vec2{1, 0}, Vec2{0.5, 1}}},
                  {{Vec2{0, 0}, Vec2{1, 0}, Vec2{0.5, 1}}}});
}

GLuint SimplexFactory::eboIndices[RVERTEX_COUNT]{};
bool SimplexFactory::buffersInitialized = false;
EBO SimplexFactory::ebo{};
VBO SimplexFactory::sharedVBO{};

void SimplexFactory::initializeBuffers() {
  buffersInitialized = true;
  initializeEBO();
  allocateVBO();
}
void SimplexFactory::initializeEBO() {
  std::iota(eboIndices, eboIndices + RVERTEX_COUNT, 0);
  ebo.allocateBufferObject(sizeof(eboIndices));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, eboIndices);
  std::cout << std::format("ebo {} for simplex allocated and initialized\n",
                           ebo.ID);
}
void SimplexFactory::allocateVBO() {
  sharedVBO.allocateBufferObject(RVERTEX_COUNT * SimpleVertex::WIDTH);
  std::cout << std::format("shared vbo {} for simplex allocated\n",
                           sharedVBO.ID);
}