module world.collision.vclip.plane.support_plane;

import world.collision.feature.vertex;
import world.collision.feature.face;
import world.collision.vclip.region.face_region;

SupportPlane::SupportPlane(const FaceRegion &region,
                           const Vertex &referencePoint, const Face &face)
    : VoronoiPlane<FaceRegion>(region, referencePoint), face{face} {}

Vec3 SupportPlane::getNormal() const { return face.getNormal(); }

UPtr<SupportPlane> SupportPlane::createPlane(const FaceRegion &region,
                                             const Face &face) {
  return std::make_unique<SupportPlane>(region, face.getSampleVertex(), face);
}