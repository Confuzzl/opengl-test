module;

#include "util/gl_utils.hpp"
#include <numeric>

module world.factory.abstract_factory;

import wrapper.program.vertex_formats;
import util.debug;

AbstractFactory::AbstractFactory(
    const unsigned short vertexCount, const unsigned short faceCount,
    const VertexNeighborList &veIndices, const EdgeNeighborList &evIndices,
    const EdgeNeighborList &efIndices, const FaceNeighborList &feIndices,
    const RFaceCoordinateIndexList &fvIndices, const RFaceUVList &defaultUVs,
    const unsigned int rVertexCount)
    : vertexCount{vertexCount}, faceCount{faceCount}, veIndices{veIndices},
      evIndices{evIndices}, efIndices{efIndices}, feIndices{feIndices},
      fvIndices{fvIndices}, defaultUVs{defaultUVs}, rVertexCount{rVertexCount} {
  initializeEBO();
  allocateVBO();
}

void AbstractFactory::initializeEBO() {
  eboIndices.resize(rVertexCount);
  std::iota(eboIndices.begin(), eboIndices.end(), 0);
  ebo.allocateBufferObject(sizeof(eboIndices));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, eboIndices.data());
  std::cout << std::format("ebo {} for factory allocated and initialized\n",
                           ebo.ID);
}
void AbstractFactory::allocateVBO() {
  sharedVBO.allocateBufferObject(rVertexCount * SimpleVertex::WIDTH);
  std::cout << std::format("shared vbo {} for factory simplex allocated\n",
                           sharedVBO.ID);
}

UPtr<Collider>
AbstractFactory::createCollidable(const Vec3List &coordinates) const {
  return std::make_unique<Collider>(vertexCount, faceCount, coordinates,
                                    veIndices, evIndices, efIndices, feIndices);
}
UPtr<Renderable>
AbstractFactory::createRenderable(const Vec3List &coordinates) const {
  // return createRenderable(coordinates, defaultUVs);
}
// UPtr<Renderable>
// AbstractFactory::createRenderable(const Vec3List &coordinates,
//                                   const RFaceUVList &UVs) const {
//   return std::make_unique<Renderable>(ebo, sharedVBO, coordinates, fvIndices,
//                                       UVs);
// }
