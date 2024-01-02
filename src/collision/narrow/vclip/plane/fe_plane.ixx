export module collision.vclip.plane.fe_plane;

import collision.vclip.plane.feature_plane;
// import collision.feature.feature;
// import collision.vclip.region.voronoi_region;
import collision.feature.edge;
import collision.feature.face;
// import util.glm;

export template </*IsFeature*/ typename NeighborType,
                 /*IsVoronoiRegion*/ typename RegionType>
class FEPlane : public FeaturePlane<NeighborType, RegionType> {
protected:
  const Face &face;

  FEPlane(const RegionType &region, const NeighborType &neighbor,
          const Edge &edge, const Face &face)
      : FeaturePlane<NeighborType, RegionType>(region, edge.getTail(), neighbor,
                                               edge),
        face{face} {}
};