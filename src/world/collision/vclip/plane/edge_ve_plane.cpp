module world.collision.vclip.plane.edge_ve_plane;

import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.region.edge_region;

EdgeVEPlane::EdgeVEPlane(const EdgeRegion &region, const Vertex &vertex,
                         const Edge &edge)
    : VEPlane<Vertex, EdgeRegion>(region, vertex, vertex, edge,
                                  &Edge::getTail) {}

UPtr<EdgeVEPlane> EdgeVEPlane::createTailPlane(const EdgeRegion &region,
                                               const Edge &edge) {
  return std::make_unique<EdgeVEPlane>(region, edge.getTail(), edge);
}
UPtr<EdgeVEPlane> EdgeVEPlane::createHeadPlane(const EdgeRegion &region,
                                               const Edge &edge) {
  return std::make_unique<EdgeVEPlane>(region, edge.getHead(), edge);
}