module world.collision.vclip.plane.planes:ve;

template <IsFeature NeighborType, IsVoronoiRegion RegionType>
VEPlane<NeighborType, RegionType>::VEPlane(const SPtr<RegionType> &region,
                                           const SPtr<Vertex> &vertex,
                                           const SPtr<Edge> &edge)
    : FeaturePlane(region, vertex), edge{edge} {}

template <IsFeature NeighborType, IsVoronoiRegion RegionType>
SPtr<Edge> VEPlane<NeighborType, RegionType>::getEdge() {
  return edge;
}

Vec3 VEPlane::getNormal() {
  const Vec3 e{*edge};
  return *referencePoint == *(endComparator()) ? e : -e;
}

// Vec3 VertexVEPlane::getNormal() {
//   const Vec3 e{*edge};
//   return *referencePoint == *(edge->getTail()) ? e : -e;
// }
//
// Vec3 EdgeVEVPlane::getNormal() {
//   const Vec3 e{*edge};
//   return *referencePoint == *(edge->getHead()) ? e : -e;
// }