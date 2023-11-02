module;

#include "util/gl_utils.hpp"

export module world.factory.base_factory;

export class Collider;
export class Renderable;

import util.polyhedron;
import util.memory;
import wrapper.buffer_object;
import world.game_object;
import world.collision.collider;
import world.render.renderable;

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
  BaseFactory &operator=(const BaseFactory &) = delete;
  BaseFactory &operator=(BaseFactory &&) = delete;

protected:
  BaseFactory(const unsigned short vertexCount, const unsigned short faceCount,
              const VEIndexList &veIndices, const EVIndexList &evIndices,
              const EFIndexList &efIndices, const FEIndexList &feIndices,
              const RenCoordinateIndexList &fvIndices, const UVList &defaultUVs,
              const unsigned int rVertexCount);

public:
  ~BaseFactory();

  EBO ebo{};
  VBO sharedVBO{};

  CollPtr createCollidable(const Vec3List &coordinates);
  RendPtr createRenderable(const Vec3List &coordinates);
  RendPtr createRenderable(const Vec3List &coordinates, const UVList &UVs);
};