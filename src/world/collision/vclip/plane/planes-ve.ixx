export module world.collision.vclip.plane.planes:ve;

import world.collision.vclip.plane.feature_plane;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;

import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.region.regions;

import <functional>;

export template <IsFeature NeighborType, IsVoronoiRegion RegionType>
class VEPlane : public FeaturePlane<NeighborType, RegionType> {
protected:
  using EndComparatorFunction = std::function<SPtr<Vertex>()>;

private:
  EndComparatorFunction endComparator;

protected:
  SPtr<Edge> edge;

  VEPlane(const SPtr<RegionType> &region, const SPtr<Vertex> &vertex,
          const SPtr<Edge> &edge, const EndComparatorFunction &endComparator);

public:
  SPtr<Edge> getEdge();
  Vec3 getNormal() override;
};

export class VertexVEPlane : public VEPlane<Edge, VertexRegion> {
  using VEPlane::VEPlane;

  //Vec3 getNormal() override;
};
export class EdgeVEPlane : public VEPlane<Vertex, EdgeRegion> {
  using VEPlane::VEPlane;

  //Vec3 getNormal() override;
};