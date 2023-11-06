export module world.collision.vclip.plane.planes:support;

import util.memory;
import world.collision.vclip.plane.voronoi_plane;
import world.collision.feature.face;
import world.collision.vclip.region.regions;

export class SupportPlane : public VoronoiPlane<FaceRegion> {
  const Face &face;

public:
  SupportPlane(const FaceRegion &region, const Vertex &referencePoint,
               const Face &face);

  Vec3 getNormal() const override;

  static UPtr<SupportPlane> createPlane(const FaceRegion &region,
                                        const Face &face);
};