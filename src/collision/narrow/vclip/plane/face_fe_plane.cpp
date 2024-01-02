module collision.vclip.plane.face_fe_plane;

import collision.feature.edge;
import collision.feature.face;
import collision.vclip.region.face_region;

FaceFEPlane::FaceFEPlane(const FaceRegion &region, const Edge &edge,
                         const Face &face)
    : FEPlane<Edge, FaceRegion>(region, edge, edge, face) {}

Vec3 FaceFEPlane::getNormal() const {
  return glm::cross(face.getNormal(), edge.getProperDirectionFrom(face));
}

UPtr<FaceFEPlane> FaceFEPlane::createPlane(const FaceRegion &region,
                                           const Edge &edge, const Face &face) {
  return std::make_unique<FaceFEPlane>(region, edge, face);
}