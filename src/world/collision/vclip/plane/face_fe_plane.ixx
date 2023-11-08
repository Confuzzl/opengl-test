export module world.collision.vclip.plane.face_fe_plane;

import world.collision.vclip.plane.fe_plane;
// import world.collision.feature.edge;
// import world.collision.vclip.region.face_region;
import util.memory;
import util.glm;

export class Edge;
export class Face;
export class FaceRegion;

export class FaceFEPlane : public FEPlane<Edge, FaceRegion> {
  friend UPtr<FaceFEPlane>
  std::make_unique<FaceFEPlane, const FaceRegion &, const Edge &, const Face &>(
      const FaceRegion &, const Edge &, const Face &);

  FaceFEPlane(const FaceRegion &region, const Edge &edge, const Face &face);

public:
  Vec3 getNormal() const override;

  static UPtr<FaceFEPlane> createPlane(const FaceRegion &region,
                                       const Edge &edge, const Face &face);
};