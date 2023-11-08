export module world.collision.vclip.plane.feature_plane;

import world.collision.vclip.plane.voronoi_plane;

// import world.collision.feature.feature;
// import world.collision.vclip.region.voronoi_region;

import world.collision.feature.vertex;
import world.collision.feature.edge;

export template </*IsFeature*/ typename NeighborType,
                 /*IsVoronoiRegion*/ typename RegionType>
class FeaturePlane : public VoronoiPlane<RegionType> {
protected:
  const NeighborType &neighbor;
  const Edge &edge;

  FeaturePlane(const RegionType &region, const Vertex &referencePoint,
               const NeighborType &neighbor, const Edge &edge)
      : VoronoiPlane<RegionType>(region, referencePoint), neighbor{neighbor},
        edge{edge} {}

public:
  const NeighborType &getNeighbor() const { return neighbor; }
};