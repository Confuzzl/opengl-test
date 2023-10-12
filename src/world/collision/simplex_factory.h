#pragma once
#include "polyhedron.h"
#include "util/polyhedron_utils.h"
#include "world/render/renderable.h"

class SimplexFactory {
  const static VertexNeighborList veIndices;
  const static EdgeNeighborList evIndices;
  const static EdgeNeighborList efIndices;
  const static FaceNeighborList feIndices;

  const static FaceVertexList fvIndices;

  SimplexFactory() = delete;
  SimplexFactory(const SimplexFactory &) = delete;
  SimplexFactory(SimplexFactory &&) = delete;

public:
  static UPtr<Polyhedron> createCollidableSimplex(const Vec3List &coordinates);
  static UPtr<Renderable> createRenderableSimplex(const Vec3List &coordinates);
};