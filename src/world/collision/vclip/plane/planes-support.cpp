module world.collision.vclip.plane.planes:support;

SupportPlane::SupportPlane(const FaceRegion &region,
                           const Vertex &referencePoint, const Face &face)
    : VoronoiPlane<FaceRegion>(region, referencePoint), face{face} {}

Vec3 SupportPlane::getNormal() const { return face.getNormal(); }