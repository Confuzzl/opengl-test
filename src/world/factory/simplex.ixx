module;

#include "util/gl_utils.hpp"

export module world.factory.simplex_factory;

import world.collision.polyhedron;
import world.render.renderable;
import util.polyhedron;
import util.memory;
import wrapper.buffer_object;

export class SimplexFactory {
  const static VertexNeighborList veIndices;
  const static EdgeNeighborList evIndices;
  const static EdgeNeighborList efIndices;
  const static FaceNeighborList feIndices;

  const static FaceVertexList fvIndices;

  SimplexFactory() = delete;
  SimplexFactory(const SimplexFactory &) = delete;
  SimplexFactory(SimplexFactory &&) = delete;

  const static unsigned int RVERTEX_COUNT = 12;
  static GLuint eboIndices[RVERTEX_COUNT];
  static bool buffersInitialized;
  static void initializeBuffers();
  static void initializeEBO();
  static void allocateVBO();

public:
  static EBO ebo;
  static VBO sharedVBO;

  static UPtr<Collider> createCollidableSimplex(const Vec3List &coordinates);
  static UPtr<Renderable> createRenderableSimplex(const Vec3List &coordinates);
};