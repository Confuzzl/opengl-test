export module collision.vclip.plane.edge_ve_plane;

import collision.vclip.plane.ve_plane;
// import collision.feature.vertex;
// import collision.vclip.region.edge_region;
import util.memory;

export class Vertex;
export class Edge;
export class EdgeRegion;

export class EdgeVEPlane : public VEPlane<Vertex, EdgeRegion> {
  friend UPtr<EdgeVEPlane>
  std::make_unique<EdgeVEPlane, const EdgeRegion &, const Vertex &,
                   const Edge &>(const EdgeRegion &, const Vertex &,
                                 const Edge &);

  EdgeVEPlane(const EdgeRegion &region, const Vertex &vertex, const Edge &edge);

public:
  static UPtr<EdgeVEPlane> createTailPlane(const EdgeRegion &region,
                                           const Edge &edge);
  static UPtr<EdgeVEPlane> createHeadPlane(const EdgeRegion &region,
                                           const Edge &edge);
};