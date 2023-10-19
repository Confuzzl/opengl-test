module;

#include "util/gl_utils.hpp"

export module world.factory.base_factory;

import world.collision.polyhedron;
import world.render.renderable;
import util.polyhedron;
import util.memory;
import wrapper.buffer_object;

export class AbstractFactory {
  const unsigned short vertexCount;
  const unsigned short faceCount;

  const VertexNeighborList veIndices;
  const EdgeNeighborList evIndices;
  const EdgeNeighborList efIndices;
  const FaceNeighborList feIndices;

  const RFaceCoordinateIndexList fvIndices;
  const RFaceUVList defaultUVs;

  const unsigned int rVertexCount;
  Vector<GLuint> eboIndices{};

  void initializeEBO();
  void allocateVBO();

  AbstractFactory(const AbstractFactory &) = delete;
  AbstractFactory(AbstractFactory &&) = delete;

protected:
  constexpr AbstractFactory(
      const unsigned short vertexCount, const unsigned short faceCount,
      const VertexNeighborList &veIndices, const EdgeNeighborList &evIndices,
      const EdgeNeighborList &efIndices, const FaceNeighborList &feIndices,
      const RFaceCoordinateIndexList &fvIndices, const RFaceUVList &defaultUVs,
      const unsigned int rVertexCount);

public:
  EBO ebo{};
  VBO sharedVBO{};

  UPtr<Collider> createCollidable(const Vec3List &coordinates) const;
  UPtr<Renderable> createRenderable(const Vec3List &coordinates) const;
  UPtr<Renderable> createRenderable(const Vec3List &coordinates,
                                    const RFaceUVList &UVs) const;
};