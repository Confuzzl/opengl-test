export module collision.vclip.region.vertex_region;

import collision.vclip.region.voronoi_region;
// import collision.feature.vertex;
import util.memory;

export class Vertex;
export class VertexVEPlane;

export class VertexRegion : public VoronoiRegion<Vertex> {
  UPtrVector<VertexVEPlane> planes;

public:
  VertexRegion(const Vertex &parent);
  ~VertexRegion();
};