module world.collision.vclip.plane.feature_plane;

template <IsFeature NeighborType, IsVoronoiRegion RegionType>
SPtr<NeighborType> FeaturePlane<NeighborType, RegionType>::getNeighbor() {
  return neighbor;
}