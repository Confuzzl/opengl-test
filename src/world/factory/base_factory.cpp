module;

#include "util/gl_utils.hpp"
#include <numeric>

module world.factory.base_factory;

import wrapper.program.vertex_formats;
import util.debug;

BaseFactory::BaseFactory(
    const unsigned short vertexCount, const unsigned short faceCount,
    const VEIndexList &veIndices, const EVIndexList &evIndices,
    const EFIndexList &efIndices, const FEIndexList &feIndices,
    const RenCoordinateIndexList &fvIndices, const UVList &defaultUVs,
    const unsigned int rVertexCount)
    : vertexCount{vertexCount}, faceCount{faceCount}, veIndices{veIndices},
      evIndices{evIndices}, efIndices{efIndices}, feIndices{feIndices},
      fvIndices{fvIndices}, defaultUVs{defaultUVs}, rVertexCount{rVertexCount} {
}
BaseFactory::~BaseFactory() = default;

void BaseFactory::initializeBuffers() {
  buffersInitialized = true;
  initializeEBO();
  allocateVBO();
}

void BaseFactory::initializeEBO() {
  eboIndices.resize(rVertexCount);
  std::iota(eboIndices.begin(), eboIndices.end(), 0);
  ebo.allocateBufferObject(rVertexCount * sizeof(GLuint));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, eboIndices.data());
  std::cout << std::format("ebo {} for factory allocated and initialized\n",
                           ebo.ID);
}
void BaseFactory::allocateVBO() {
  sharedVBO.allocateBufferObject(rVertexCount * SimpleVertex::WIDTH);
  std::cout << std::format("shared vbo {} for factory simplex allocated\n",
                           sharedVBO.ID);
}

UPtr<Collider> BaseFactory::createCollidable(const Vec3List &coordinates) {
  return std::make_unique<Collider>(vertexCount, faceCount, coordinates,
                                    veIndices, evIndices, efIndices, feIndices);
}
UPtr<Renderable> BaseFactory::createRenderable(const Vec3List &coordinates) {
  return createRenderable(coordinates, defaultUVs);
}
UPtr<Renderable> BaseFactory::createRenderable(const Vec3List &coordinates,
                                               const UVList &UVs) {
  if (not buffersInitialized)
    initializeBuffers();
  return std::make_unique<Renderable>(ebo, sharedVBO, coordinates, fvIndices,
                                      UVs);
}
