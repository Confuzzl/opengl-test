export module world.collision.simplex_factory;

import world.collision.polyhedron;
import world.render.renderable;
import util.polyhedron;
import util.memory;

export class SimplexFactory {
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