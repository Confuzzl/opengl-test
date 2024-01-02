module collision.vclip.plane.vertex_ve_plane;

import collision.feature.vertex;
import collision.feature.edge;
import collision.vclip.region.vertex_region;

VertexVEPlane::VertexVEPlane(const VertexRegion &region, const Vertex &vertex,
                             const Edge &edge)
    : VEPlane<Edge, VertexRegion>(region, vertex, edge, edge, &Edge::getHead) {}

UPtr<VertexVEPlane> VertexVEPlane::createPlane(const VertexRegion &region,
                                               const Vertex &vertex,
                                               const Edge &edge) {
  return std::make_unique<VertexVEPlane>(region, vertex, edge);
}