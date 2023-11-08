export module world.collision.vclip.plane.edge_fe_plane;

import world.collision.vclip.plane.fe_plane;
// import world.collision.feature.face;
// import world.collision.vclip.region.edge_region;
import util.memory;
import util.glm;

export class Edge;
export class Face;
export class EdgeRegion;

export class EdgeFEPlane : public FEPlane<Face, EdgeRegion> {
  friend UPtr<EdgeFEPlane>
  std::make_unique<EdgeFEPlane, const EdgeRegion &, const Edge &, const Face &,
                   bool>(const EdgeRegion &, const Edge &, const Face &,
                         bool &&);

  bool reversed;

  EdgeFEPlane(const EdgeRegion &region, const Edge &edge, const Face &face,
              const bool reversed);

public:
  Vec3 getNormal() const override;

  static UPtr<EdgeFEPlane> createLeftPlane(const EdgeRegion &region,
                                           const Edge &edge);
  static UPtr<EdgeFEPlane> createRightPlane(const EdgeRegion &region,
                                            const Edge &edge);
};