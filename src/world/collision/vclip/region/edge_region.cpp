module world.collision.vclip.region.edge_region;

import world.collision.feature.edge;
import world.collision.vclip.plane.edge_ve_plane;
import world.collision.vclip.plane.edge_fe_plane;

EdgeRegion::EdgeRegion(const Edge &parent)
    : VoronoiRegion<Edge>(parent),
      ve1{std::move(EdgeVEPlane::createTailPlane(*this, parent))},
      ve2{std::move(EdgeVEPlane::createHeadPlane(*this, parent))},
      fe1{std::move(EdgeFEPlane::createLeftPlane(*this, parent))},
      fe2{std::move(EdgeFEPlane::createRightPlane(*this, parent))} {}
EdgeRegion::~EdgeRegion() = default;