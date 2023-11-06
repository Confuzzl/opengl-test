export module world.collision.vclip.region.regions:edge;

import world.collision.feature.edge;
import world.collision.vclip.region.voronoi_region;

class EdgeVEPlane;
class EdgeFEPlane;

export class EdgeRegion : public VoronoiRegion<Edge> {
  UPtr<EdgeVEPlane> ve1, ve2;
  UPtr<EdgeFEPlane> fe1, fe2;

public:
  EdgeRegion(const Edge &parent);
  ~EdgeRegion();
};