module;

#include <functional>

export module collision.vclip.plane.ve_plane;

import collision.vclip.plane.feature_plane;
import collision.vclip.plane.voronoi_plane;
// import collision.feature.feature;
// import collision.vclip.region.voronoi_region;
import collision.feature.vertex;
import collision.feature.edge;
import util.glm;

export template </*IsFeature*/ typename NeighborType,
                 /*IsVoronoiRegion*/ typename RegionType>
class VEPlane : public FeaturePlane<NeighborType, RegionType> {
  using EdgeEndMethod = std::function<const Vertex &(const Edge *)>;
  const EdgeEndMethod edgeEndMethod;

protected:
  VEPlane(const RegionType &region, const Vertex &vertex,
          const NeighborType &neighbor, const Edge &edge,
          EdgeEndMethod &&edgeEndMethod)
      : FeaturePlane<NeighborType, RegionType>(region, vertex, neighbor, edge),
        edgeEndMethod{std::move(edgeEndMethod)} {}

public:
  using VoronoiPlane<RegionType>::referencePoint;
  using FeaturePlane<NeighborType, RegionType>::edge;
  Vec3 getNormal() const override {
    return (referencePoint == edgeEndMethod(&edge) ? +1.0f : -1.0f) *
           static_cast<Vec3>(edge);
  }
};