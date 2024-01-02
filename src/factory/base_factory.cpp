module;

#include "util/gl_utils.hpp"
#include <numeric>

module factory.base_factory;

import collision.collider;
import rendering.vertex_formats.types;
import util.debug;

Factory::Base::Base(const unsigned short vertexCount,
                    const unsigned short faceCount,
                    const VEIndexList &veIndices, const EVIndexList &evIndices,
                    const EFIndexList &efIndices, const FEIndexList &feIndices,
                    const render::IndexList &defaultIndexList,
                    const render::ColList &defaultColList,
                    const render::TexList &defaultTexList,
                    const unsigned int rVertexCount)
    : vertexCount{vertexCount}, faceCount{faceCount}, veIndices{veIndices},
      evIndices{evIndices}, efIndices{efIndices}, feIndices{feIndices},
      defaultIndexList{defaultIndexList}, defaultColList{defaultColList},
      defaultTexList{defaultTexList}, rVertexCount{rVertexCount} {}

void Factory::Base::initializeBuffers() const {
  buffersInitialized = true;
  initializeEBO();
  allocateVBO();
}

void Factory::Base::initializeEBO() const {
  eboIndices.resize(rVertexCount);
  std::iota(eboIndices.begin(), eboIndices.end(), 0);
  ebo.allocateBufferObject(rVertexCount * sizeof(GLuint));
  glNamedBufferSubData(ebo.GLid, 0, ebo.size, eboIndices.data());
  std::cout << std::format("ebo {} for factory allocated and initialized\n",
                           ebo.GLid);
}
void Factory::Base::allocateVBO() const {
  sharedVBO.allocateBufferObject(rVertexCount *
                                 VertexFormats::_3D::ColTex::WIDTH);
  std::cout << std::format("shared vbo {} for factory simplex allocated\n",
                           sharedVBO.GLid);
}

// CollPtr Factory::Base::createCollidable(const Vec3List &coordinates) const {
//   return std::make_unique<Collider>(vertexCount, faceCount, coordinates,
//                                     veIndices, evIndices, efIndices,
//                                     feIndices);
// }