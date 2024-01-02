module collision.vclip.plane.edge_fe_plane;

import collision.feature.edge;
import collision.feature.face;
import collision.vclip.region.edge_region;

EdgeFEPlane::EdgeFEPlane(const EdgeRegion &region, const Edge &edge,
                         const Face &face, const bool reversed)
    : FEPlane<Face, EdgeRegion>(region, face, edge, face), reversed{reversed} {}

Vec3 EdgeFEPlane::getNormal() const {
  return glm::cross((reversed ? -1.0f : +1.0f) * static_cast<Vec3>(edge),
                    face.getNormal());
}

UPtr<EdgeFEPlane> EdgeFEPlane::createLeftPlane(const EdgeRegion &region,
                                               const Edge &edge) {
  return std::make_unique<EdgeFEPlane>(region, edge, edge.getLeft(), false);
}
UPtr<EdgeFEPlane> EdgeFEPlane::createRightPlane(const EdgeRegion &region,
                                                const Edge &edge) {
  return std::make_unique<EdgeFEPlane>(region, edge, edge.getRight(), true);
}