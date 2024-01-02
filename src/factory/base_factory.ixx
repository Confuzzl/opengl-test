module;

#include "util/gl_utils.hpp"

export module factory.base_factory;

import util.polyhedron;
import util.rendering;
// import util.memory;
import wrapper.buffer_object;
// import world.game_object;
// import collision.collider;

// import rendering.shaders.global;
// import rendering.vertex_formats.types;
// import rendering.base;

import app.texture_tile;

export namespace Factory {
class Base {

  const unsigned int rVertexCount;
  mutable bool buffersInitialized = false;
  mutable Vector<GLuint> eboIndices{};

  void initializeBuffers() const;
  void initializeEBO() const;
  void allocateVBO() const;

protected:
  Base(const unsigned short vertexCount, const unsigned short faceCount,
       const VEIndexList &veIndices, const EVIndexList &evIndices,
       const EFIndexList &efIndices, const FEIndexList &feIndices,
       const render::IndexList &defaultIndexList,
       const render::ColList &defaultColList,
       const render::TexList &defaultTexList, const unsigned int rVertexCount);

public:
  const unsigned short vertexCount;
  const unsigned short faceCount;

  const VEIndexList veIndices;
  const EVIndexList evIndices;
  const EFIndexList efIndices;
  const FEIndexList feIndices;

  const render::IndexList defaultIndexList;
  const render::ColList defaultColList;
  const render::TexList defaultTexList;

  mutable EBO ebo{};
  mutable VBO sharedVBO{};

  // CollPtr createCollidable(const Vec3List &coordinates) const;
};
} // namespace Factory
