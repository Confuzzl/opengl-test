export module world.collision.vclip.voronoi_region;

import <concepts>;
import util.glm;
import world.collision.feature.feature;

export template <typename T>
concept IsVoronoiPlane = requires(T t) {
  t.getRegion();
  t.getNeighbor();
  { t.getNormal() } -> std::same_as<Vec3>;
};

export template <IsFeature NeighborType, IsVoronoiPlane PlaneType>
class VoronoiRegion {};