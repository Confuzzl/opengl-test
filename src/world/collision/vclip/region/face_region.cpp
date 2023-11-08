module world.collision.vclip.region.face_region;

import world.collision.feature.face;
import world.collision.vclip.plane.face_fe_plane;
import world.collision.vclip.plane.support_plane;

FaceRegion::FaceRegion(const Face &parent)
    : VoronoiRegion<Face>(parent),
      supportPlane{std::move(SupportPlane::createPlane(*this, parent))} {
  const RefVector<const Edge> &edges{parent.getEdges()};
  planes.reserve(edges.size());
  for (const auto &edge : edges) {
    planes.emplace_back(FaceFEPlane::createPlane(*this, edge, parent));
  }
}
FaceRegion::~FaceRegion() = default;