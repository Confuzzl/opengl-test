export module world.collision.vclip.plane.voronoi_plane;

import util.memory;
import util.glm;
import world.collision.vclip.region.voronoi_region;
import world.collision.feature.vertex;

export template <IsVoronoiRegion RegionType> class VoronoiPlane {
  VoronoiPlane(const VoronoiPlane &) = delete;
  VoronoiPlane(VoronoiPlane &&) = delete;
  VoronoiPlane &operator=(const VoronoiPlane &) = delete;
  VoronoiPlane &operator=(VoronoiPlane &&) = delete;

protected:
  const RegionType &region;
  const Vertex &referencePoint;

  VoronoiPlane(const RegionType &region, const Vertex &referencePoint)
      : region{region}, referencePoint{referencePoint} {}

public:
  const RegionType &getRegion() const { return region; }

  double signedDistance(const Vec3 &v) const {
    return glm::dot(getNormal(), v - referencePoint.asGlobalCoordinate());
  }
  virtual Vec3 getNormal() const = 0;
};
