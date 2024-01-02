module collision.vclip.plane.edge_ve_plane;

import collision.feature.vertex;
import collision.feature.edge;
import collision.vclip.region.edge_region;

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