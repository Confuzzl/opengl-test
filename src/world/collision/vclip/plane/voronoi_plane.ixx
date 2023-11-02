export module world.collision.vclip.plane.voronoi_plane;

import util.memory;
import util.glm;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;
import world.collision.feature.vertex;

export template <IsVoronoiRegion RegionType> class VoronoiPlane {
protected:
  SPtr<RegionType> region;
  SPtr<Vertex> referencePoint;

  VoronoiPlane(const SPtr<RegionType> &region,
               const SPtr<Vertex> &referencePoint);

public:
  SPtr<RegionType> getRegion();
  SPtr<Vertex> getPoint();

  double signedDistance(Vec3 &v);
  virtual Vec3 getNormal() = 0;
};
