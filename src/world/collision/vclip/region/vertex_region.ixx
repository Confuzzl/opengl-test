export module world.collision.vclip.region.vertex_region;

import world.collision.vclip.region.voronoi_region;
// import world.collision.feature.vertex;
import util.memory;

export class Vertex;
export class VertexVEPlane;

export class VertexRegion : public VoronoiRegion<Vertex> {
  UPtrVector<VertexVEPlane> planes;

public:
  VertexRegion(const Vertex &parent);
  ~VertexRegion();
};