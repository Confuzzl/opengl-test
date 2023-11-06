module;

#include <functional>

export module world.collision.vclip.plane.planes:ve;

import util.glm;

import world.collision.vclip.plane.feature_plane;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;

import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.region.regions;

export template <IsFeature NeighborType, IsVoronoiRegion RegionType>
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

export class VertexVEPlane : public VEPlane<Edge, VertexRegion> {
  friend UPtr<VertexVEPlane>
  std::make_unique<VertexVEPlane, const VertexRegion &, const Vertex &,
                   const Edge &>(const VertexRegion &, const Vertex &,
                                 const Edge &);

  VertexVEPlane(const VertexRegion &region, const Vertex &vertex,
                const Edge &edge)
      : VEPlane<Edge, VertexRegion>(region, vertex, edge, edge,
                                    &Edge::getHead) {}

public:
  static UPtr<VertexVEPlane> createPlane(const VertexRegion &region,
                                         const Vertex &vertex,
                                         const Edge &edge) {
    return std::make_unique<VertexVEPlane>(region, vertex, edge);
  }
};
export class EdgeVEPlane : public VEPlane<Vertex, EdgeRegion> {
  friend UPtr<EdgeVEPlane>
  std::make_unique<EdgeVEPlane, const EdgeRegion &, const Vertex &,
                   const Edge &>(const EdgeRegion &, const Vertex &,
                                 const Edge &);

  EdgeVEPlane(const EdgeRegion &region, const Vertex &vertex, const Edge &edge)
      : VEPlane<Vertex, EdgeRegion>(region, vertex, vertex, edge,
                                    &Edge::getTail) {}

public:
  static UPtr<EdgeVEPlane> createTailPlane(const EdgeRegion &region,
                                           const Edge &edge) {
    return std::make_unique<EdgeVEPlane>(region, edge.getTail(), edge);
  }
  static UPtr<EdgeVEPlane> createHeadPlane(const EdgeRegion &region,
                                           const Edge &edge) {
    return std::make_unique<EdgeVEPlane>(region, edge.getHead(), edge);
  }
};