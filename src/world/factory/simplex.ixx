module;

#include "util/gl_utils.hpp"

export module world.factory.simplex_factory;

import world.collision.polyhedron;
import world.render.renderable;
import util.polyhedron;
import util.memory;
import wrapper.buffer_object;

export class SimplexFactoryA {
  const static VEIndexList veIndices;
  const static EVIndexList evIndices;
  const static EFIndexList efIndices;
  const static FEIndexList feIndices;

  const static RenCoordinateIndexList fvIndices;

  SimplexFactoryA() = delete;
  SimplexFactoryA(const SimplexFactoryA &) = delete;
  SimplexFactoryA(SimplexFactoryA &&) = delete;

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