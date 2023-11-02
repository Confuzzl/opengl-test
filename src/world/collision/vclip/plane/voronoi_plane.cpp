module world.collision.vclip.plane.voronoi_plane;

template <IsVoronoiRegion RegionType>
VoronoiPlane<RegionType>::VoronoiPlane(const SPtr<RegionType> &region,
                                       const SPtr<Vertex> &referencePoint)
    : region{region}, referencePoint{referencePoint} {}

template <IsVoronoiRegion RegionType>
SPtr<RegionType> VoronoiPlane<RegionType>::getRegion() {
  return region;
}

template <IsVoronoiRegion RegionType>
SPtr<Vertex> VoronoiPlane<RegionType>::getPoint() {
  return referencePoint;
}

template <IsVoronoiRegion RegionType>
double VoronoiPlane<RegionType>::signedDistance(Vec3 &v) {
  return glm::dot(getNormal(), v - *referencePoint);
}