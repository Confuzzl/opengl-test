module world.collision.vclip.region.regions:face;

import world.collision.vclip.plane.planes;

FaceRegion::FaceRegion(const Face &parent) : VoronoiRegion<Face>(parent) {}
FaceRegion::~FaceRegion() = default;