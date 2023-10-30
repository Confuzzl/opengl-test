export module world.collision.vclip.plane.voronoi_plane;

import util.memory;
import util.glm;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;
import world.collision.feature.vertex;

export template <IsVoronoiRegion RegionType> class VoronoiPlane {
  SPtr<RegionType> region;
  SPtr<Vertex> referencePoint;

protected:
  VoronoiPlane(const SPtr<RegionType> &region,
               const SPtr<Vertex> referencePoint);

public:
  SPtr<RegionType> &getRegion();

  double signedDistance(Vec3 &v);
  virtual Vec3 getNormal() = 0;
};
