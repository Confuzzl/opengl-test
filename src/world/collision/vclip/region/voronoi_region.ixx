export module world.collision.vclip.region.voronoi_region;

import world.collision.feature.feature;
import util.vector;

export template <typename T>
concept IsVoronoiRegion = requires(T t) { t.getParent(); };

export template <IsFeature ParentType> class VoronoiRegion {
  ParentType parent;

public:
  ParentType &getParent() { return parent; }

  // bool &pointInRegion(const Vec3 &v) {}
};
