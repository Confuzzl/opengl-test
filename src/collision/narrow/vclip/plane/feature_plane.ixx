export module collision.vclip.plane.feature_plane;

import collision.vclip.plane.voronoi_plane;

// import collision.feature.feature;
// import collision.vclip.region.voronoi_region;

import collision.feature.vertex;
import collision.feature.edge;

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