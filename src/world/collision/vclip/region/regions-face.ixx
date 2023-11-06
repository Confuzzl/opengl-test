export module world.collision.vclip.region.regions:face;

import world.collision.feature.face;
import world.collision.vclip.region.voronoi_region;

export class FaceRegion : public VoronoiRegion<Face> {
public:
  using VoronoiRegion<Face>::VoronoiRegion;
};