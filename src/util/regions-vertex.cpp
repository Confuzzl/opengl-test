module world.collision.vclip.region.regions:vertex;

import world.collision.vclip.plane.planes;

VertexRegion::VertexRegion(const Vertex &parent)
    : VoronoiRegion<Vertex>(parent) {
  const SPtrVector<Edge> &neighbors{parent.getNeighbors()};
  planes.reserve(neighbors.size());
  for (const auto &edge : neighbors) {
  }
}

VertexRegion::~VertexRegion() = default;