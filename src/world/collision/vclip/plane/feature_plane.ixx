export module world.collision.vclip.plane.feature_plane;

import world.collision.vclip.plane.voronoi_plane;
import util.memory;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;

export template <IsFeature NeighborType, IsVoronoiRegion RegionType>
class FeaturePlane : public VoronoiPlane<RegionType> {
  SPtr<NeighborType> neighbor;
};