module;

#include "util/gl_utils.hpp"
#include <numeric>

module world.factory.base_factory;

import world.collision.collider;
import rendering.renderable;
import shaders.vertex_formats;
import util.debug;

BaseFactory::BaseFactory(
    const unsigned short vertexCount, const unsigned short faceCount,
    const VEIndexList &veIndices, const EVIndexList &evIndices,
    const EFIndexList &efIndices, const FEIndexList &feIndices,
    const render::IndexList &defaultIndexList,
    const render::ColList &defaultColList,
    const render::TexList &defaultTexList, const unsigned int rVertexCount)
    : vertexCount{vertexCount}, faceCount{faceCount}, veIndices{veIndices},
      evIndices{evIndices}, efIndices{efIndices}, feIndices{feIndices},
      defaultIndexList{defaultIndexList}, defaultColList{defaultColList},
      defaultTexList{defaultTexList}, rVertexCount{rVertexCount} {}
BaseFactory::~BaseFactory() = default;

void BaseFactory::initializeBuffers() const {
  buffersInitialized = true;
  initializeEBO();
  allocateVBO();
}

void BaseFactory::initializeEBO() const {
  eboIndices.resize(rVertexCount);
  std::iota(eboIndices.begin(), eboIndices.end(), 0);
  ebo.allocateBufferObject(rVertexCount * sizeof(GLuint));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, eboIndices.data());
  std::cout << std::format("ebo {} for factory allocated and initialized\n",
                           ebo.ID);
}
void BaseFactory::allocateVBO() const {
  sharedVBO.allocateBufferObject(rVertexCount *
                                 VertexFormats::_3D::ColTex::WIDTH);
  std::cout << std::format("shared vbo {} for factory simplex allocated\n",
                           sharedVBO.ID);
}

CollPtr BaseFactory::createCollidable(const Vec3List &coordinates) const {
  return std::make_unique<Collider>(vertexCount, faceCount, coordinates,
                                    veIndices, evIndices, efIndices, feIndices);
}
RendPtr BaseFactory::createRenderable(const Vec3List &coordinates) const {
  return createRenderable(coordinates, defaultTexList);
}
RendPtr BaseFactory::createRenderable(const Vec3List &coordinates,
                                      const render::TexList &texList) const {
  if (not buffersInitialized)
    initializeBuffers();
  return std::make_unique<Renderable>(ebo, sharedVBO, coordinates,
                                      defaultIndexList, texList);
}

UPtr<RenderableCol> BaseFactory::renCol(const Vec3List &coordinates) const {
  return renCol(coordinates, defaultColList);
}
UPtr<RenderableCol> BaseFactory::renCol(const Vec3List &coordinates,
                                        const render::ColList &colList) const {
  if (not buffersInitialized)
    initializeBuffers();
  UPtr<RenderableCol> out{std::make_unique<RenderableCol>(
      ebo, sharedVBO, coordinates, defaultIndexList, colList)};
  out->finishConstruction();
  return out;
}

UPtr<RenderableTex> BaseFactory::renTex(const Vec3List &coordinates) const {
  return renTex(coordinates, defaultTexList);
}
UPtr<RenderableTex> BaseFactory::renTex(const Vec3List &coordinates,
                                        const render::TexList &texList) const {
  if (not buffersInitialized)
    initializeBuffers();
  UPtr<RenderableTex> out{std::make_unique<RenderableTex>(
      ebo, sharedVBO, coordinates, defaultIndexList, texList)};
  out->finishConstruction();
  return out;
}

UPtr<RenderableColTex>
BaseFactory::renColTex(const Vec3List &coordinates) const {
  return renColTex(coordinates, defaultColList, defaultTexList);
}
UPtr<RenderableColTex>
BaseFactory::renColTex(const Vec3List &coordinates,
                       const render::ColList &colList) const {
  return renColTex(coordinates, colList, defaultTexList);
}
UPtr<RenderableColTex>
BaseFactory::renColTex(const Vec3List &coordinates,
                       const render::TexList &texList) const {
  return renColTex(coordinates, defaultColList, texList);
}
UPtr<RenderableColTex>
BaseFactory::renColTex(const Vec3List &coordinates,
                       const render::ColList &colList,
                       const render::TexList &texList) const {
  if (not buffersInitialized)
    initializeBuffers();
  UPtr<RenderableColTex> out{std::make_unique<RenderableColTex>(
      ebo, sharedVBO, coordinates, defaultIndexList, colList, texList)};
  out->finishConstruction();
  return out;
}
