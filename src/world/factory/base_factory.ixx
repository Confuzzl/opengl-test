module;

#include "util/gl_utils.hpp"

export module world.factory.base_factory;

import world.collision.polyhedron;
import world.render.renderable;
import util.polyhedron;
import util.memory;
import wrapper.buffer_object;

export class BaseFactory {
  const unsigned short vertexCount;
  const unsigned short faceCount;

  const VEIndexList veIndices;
  const EVIndexList evIndices;
  const EFIndexList efIndices;
  const FEIndexList feIndices;

  const RenCoordinateIndexList fvIndices;
  const UVList defaultUVs;

  const unsigned int rVertexCount;
  bool buffersInitialized = false;
  Vector<GLuint> eboIndices{};

  void initializeBuffers();
  void initializeEBO();
  void allocateVBO();

  BaseFactory(const BaseFactory &) = delete;
  BaseFactory(BaseFactory &&) = delete;

protected:
  BaseFactory(const unsigned short vertexCount, const unsigned short faceCount,
              const VEIndexList &veIndices, const EVIndexList &evIndices,
              const EFIndexList &efIndices, const FEIndexList &feIndices,
              const RenCoordinateIndexList &fvIndices, const UVList &defaultUVs,
              const unsigned int rVertexCount);

public:
  EBO ebo{};
  VBO sharedVBO{};

  UPtr<Collider> createCollidable(const Vec3List &coordinates);
  UPtr<Renderable> createRenderable(const Vec3List &coordinates);
  UPtr<Renderable> createRenderable(const Vec3List &coordinates,
                                    const UVList &UVs);
};