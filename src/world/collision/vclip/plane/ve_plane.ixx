module;

#include <functional>

export module world.collision.vclip.plane.ve_plane;

import world.collision.vclip.plane.feature_plane;
// import world.collision.feature.feature;
// import world.collision.vclip.region.voronoi_region;
import world.collision.feature.vertex;
import world.collision.feature.edge;
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
  Vec3 getNormal() const override {
    return (this->referencePoint == edgeEndMethod(&(this->edge)) ? +1.0f
                                                                 : -1.0f) *
           static_cast<Vec3>(this->edge);
  }
};