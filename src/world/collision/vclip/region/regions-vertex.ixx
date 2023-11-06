export module world.collision.vclip.region.regions:vertex;

import world.collision.feature.vertex;
import world.collision.vclip.region.voronoi_region;

class VertexVEPlane;

export class VertexRegion : public VoronoiRegion<Vertex> {
  UPtrVector<VertexVEPlane> planes;

public:
  VertexRegion(const Vertex &parent);
  ~VertexRegion();
};