export module world.collision.vclip.region.voronoi_region;

import util.vector;
import util.glm;
import world.collision.feature.feature;

// export template <typename T>
// concept IsVoronoiRegion = requires(T t) { t.getParent(); };

export template </*IsFeature*/ typename ParentType> class VoronoiRegion {
  const ParentType &parent;

protected:
  VoronoiRegion(const ParentType &parent) : parent{parent} {}

public:
  const ParentType &getParent() const { return parent; }

  const bool pointInRegion(const Vec3 &v) const { return true; }
};
