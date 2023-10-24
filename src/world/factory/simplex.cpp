module;

#include "util/gl_utils.hpp"
#include <numeric>

module world.factory.simplex_factory;

import util.debug;
import wrapper.program.vertex_formats;

const VEIndexList SimplexFactoryA::veIndices{
    {0, 2, 4}, {0, 1, 5}, {1, 2, 3}, {3, 4, 5}};
const EVIndexList SimplexFactoryA::evIndices{{0, 1}, {1, 2}, {2, 0},
                                             {2, 3}, {0, 3}, {1, 3}};
const EFIndexList SimplexFactoryA::efIndices{{0, 2}, {0, 3}, {0, 1},
                                             {1, 3}, {2, 1}, {3, 2}};
const FEIndexList SimplexFactoryA::feIndices{
    {0, 1, 2}, {2, 3, 4}, {0, 4, 5}, {1, 5, 3}};

const RenCoordinateIndexList SimplexFactoryA::fvIndices{
    {{0, 1, 2}}, {{0, 2, 3}}, {{1, 0, 3}}, {{2, 1, 3}}};

UPtr<Collider>
SimplexFactoryA::createCollidableSimplex(const Vec3List &coordinates) {
  return std::make_unique<Collider>(4, 4, coordinates, veIndices, evIndices,
                                    efIndices, feIndices);
}

UPtr<Renderable>
SimplexFactoryA::createRenderableSimplex(const Vec3List &coordinates) {
  if (not buffersInitialized)
    initializeBuffers();

  return std::make_unique<Renderable>(ebo, sharedVBO, coordinates, fvIndices,
                                      UVList{{{{{0, 0}, {1, 0}, {0.5, 1}}}},
                                             {{{{0, 0}, {1, 0}, {0.5, 1}}}},
                                             {{{{0, 0}, {1, 0}, {0.5, 1}}}},
                                             {{{{0, 0}, {1, 0}, {0.5, 1}}}}});
}

GLuint SimplexFactoryA::eboIndices[RVERTEX_COUNT]{};
bool SimplexFactoryA::buffersInitialized = false;
EBO SimplexFactoryA::ebo{};
VBO SimplexFactoryA::sharedVBO{};

void SimplexFactoryA::initializeBuffers() {
  buffersInitialized = true;
  initializeEBO();
  allocateVBO();
}
void SimplexFactoryA::initializeEBO() {
  std::iota(eboIndices, eboIndices + RVERTEX_COUNT, 0);
  ebo.allocateBufferObject(sizeof(eboIndices));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, eboIndices);
  std::cout << std::format("ebo {} for simplex allocated and initialized\n",
                           ebo.ID);
}
void SimplexFactoryA::allocateVBO() {
  sharedVBO.allocateBufferObject(RVERTEX_COUNT * SimpleVertex::WIDTH);
  std::cout << std::format("shared vbo {} for simplex allocated\n",
                           sharedVBO.ID);
}