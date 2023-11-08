module world.collision.vclip.region.vertex_region;

import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.plane.vertex_ve_plane;

VertexRegion::VertexRegion(const Vertex &parent)
    : VoronoiRegion<Vertex>(parent) {
  const RefVector<const Edge> &neighbors{parent.getNeighbors()};
  planes.reserve(neighbors.size());
  for (const auto &edge : neighbors) {
    planes.emplace_back(VertexVEPlane::createPlane(*this, parent, edge));
  }
}
VertexRegion::~VertexRegion() = default;