module world.collision.vclip.plane.vertex_ve_plane;

import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.region.vertex_region;

VertexVEPlane::VertexVEPlane(const VertexRegion &region, const Vertex &vertex,
                             const Edge &edge)
    : VEPlane<Edge, VertexRegion>(region, vertex, edge, edge, &Edge::getHead) {}

UPtr<VertexVEPlane> VertexVEPlane::createPlane(const VertexRegion &region,
                                               const Vertex &vertex,
                                               const Edge &edge) {
  return std::make_unique<VertexVEPlane>(region, vertex, edge);
}