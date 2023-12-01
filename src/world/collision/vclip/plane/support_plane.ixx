export module world.collision.vclip.plane.support_plane;

import world.collision.vclip.plane.voronoi_plane;
// import world.collision.vclip.region.face_region;
import util.memory;
import util.glm;

export class Vertex;
export class Face;
export class FaceRegion;

export class SupportPlane : public VoronoiPlane<FaceRegion> {
  const Face &face;

  friend UPtr<SupportPlane>
  std::make_unique<SupportPlane, const FaceRegion &, const Vertex &,
                   const Face &>(const FaceRegion &, const Vertex &,
                                 const Face &);

  SupportPlane(const FaceRegion &region, const Vertex &referencePoint,
               const Face &face);

public:
  Vec3 getNormal() const override;

  static UPtr<SupportPlane> createPlane(const FaceRegion &region,
                                        const Face &face);
};