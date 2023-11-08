export module world.collision.vclip.plane.fe_plane;

import world.collision.vclip.plane.feature_plane;
// import world.collision.feature.feature;
// import world.collision.vclip.region.voronoi_region;
import world.collision.feature.edge;
import world.collision.feature.face;
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