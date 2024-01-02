export module collision.vclip.plane.vertex_ve_plane;

import collision.vclip.plane.ve_plane;
// import collision.feature.edge;
//  import collision.vclip.region.vertex_region;
import util.memory;

export class Vertex;
export class Edge;
export class VertexRegion;

export class VertexVEPlane : public VEPlane<Edge, VertexRegion> {
  friend UPtr<VertexVEPlane>
  std::make_unique<VertexVEPlane, const VertexRegion &, const Vertex &,
                   const Edge &>(const VertexRegion &, const Vertex &,
                                 const Edge &);

  VertexVEPlane(const VertexRegion &region, const Vertex &vertex,
                const Edge &edge);

public:
  static UPtr<VertexVEPlane> createPlane(const VertexRegion &region,
                                         const Vertex &vertex,
                                         const Edge &edge);
};