export module world.collision.vclip.plane.planes:support;

import util.memory;
import world.collision.vclip.plane.voronoi_plane;
import world.collision.feature.face;
import world.collision.vclip.region.regions;

export class SupportPlane : public VoronoiPlane<FaceRegion> {
  SPtr<Face> face;

  SPtr<Face> getFace();

  Vec3 getNormal() override;
};