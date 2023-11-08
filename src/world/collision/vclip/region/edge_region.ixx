export module world.collision.vclip.region.edge_region;

import world.collision.vclip.region.voronoi_region;
// import world.collision.feature.edge;
import util.memory;

export class Edge;
export class EdgeVEPlane;
export class EdgeFEPlane;

export class EdgeRegion : public VoronoiRegion<Edge> {
  const UPtr<EdgeVEPlane> ve1, ve2;
  const UPtr<EdgeFEPlane> fe1, fe2;

public:
  EdgeRegion(const Edge &parent);
  ~EdgeRegion();
};