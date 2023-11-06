module world.collision.vclip.region.regions:edge;

import world.collision.vclip.plane.planes;

EdgeRegion::EdgeRegion(const Edge &parent)
    : VoronoiRegion<Edge>(parent),
      ve1{EdgeVEPlane::createTailPlane(*this, parent)},
      ve2{EdgeVEPlane::createHeadPlane(*this, parent)},
      fe1{EdgeFEPlane::createLeftPlane(*this, parent)},
      fe2{EdgeFEPlane::createRightPlane(*this, parent)} {}
EdgeRegion::~EdgeRegion() = default;