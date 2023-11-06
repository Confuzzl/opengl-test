export module world.collision.vclip.region.voronoi_region;

import util.vector;
import world.collision.feature.feature;

export template <typename T>
concept IsVoronoiRegion = requires(T t) { t.getParent(); };

export template <IsFeature ParentType> class VoronoiRegion {
  const ParentType &parent;

protected:
  VoronoiRegion(const ParentType &parent) : parent{parent} {}

public:
  ParentType &getParent() { return parent; }

  // bool &pointInRegion(const Vec3 &v) {}
};
