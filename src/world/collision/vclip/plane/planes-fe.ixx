export module world.collision.vclip.plane.planes:fe;

import util.glm;

import world.collision.vclip.plane.feature_plane;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;

import world.collision.feature.edge;
import world.collision.feature.face;
import world.collision.vclip.region.regions;

export template <IsFeature NeighborType, IsVoronoiRegion RegionType>
class FEPlane : public FeaturePlane<NeighborType, RegionType> {
protected:
  const Face &face;

  FEPlane(const RegionType &region, const NeighborType &neighbor,
          const Edge &edge, const Face &face)
      : FeaturePlane<NeighborType, RegionType>(region, edge.getTail(), neighbor,
                                               edge),
        face{face} {}
};

export class EdgeFEPlane : public FEPlane<Face, EdgeRegion> {
  friend UPtr<EdgeFEPlane>
  std::make_unique<EdgeFEPlane, const EdgeRegion &, const Edge &, const Face &,
                   bool>(const EdgeRegion &, const Edge &, const Face &,
                         bool &&);

  bool reversed;

  EdgeFEPlane(const EdgeRegion &region, const Edge &edge, const Face &face,
              const bool reversed)
      : FEPlane<Face, EdgeRegion>(region, face, edge, face),
        reversed{reversed} {}

public:
  Vec3 getNormal() const override {
    return glm::cross((reversed ? -1.0f : +1.0f) * static_cast<Vec3>(edge),
                      face.getNormal());
  }

  static UPtr<EdgeFEPlane> createLeftPlane(const EdgeRegion &region,
                                           const Edge &edge) {
    return std::make_unique<EdgeFEPlane>(region, edge, edge.getLeft(), false);
  }
  static UPtr<EdgeFEPlane> createRightPlane(const EdgeRegion &region,
                                            const Edge &edge) {
    return std::make_unique<EdgeFEPlane>(region, edge, edge.getRight(), true);
  }
};
export class FaceFEPlane : public FEPlane<Edge, FaceRegion> {
public:
  FaceFEPlane(const FaceRegion &region, const Edge &edge, const Face &face)
      : FEPlane<Edge, FaceRegion>(region, edge, edge, face) {}

  Vec3 getNormal() const override {
    return glm::cross(face.getNormal(), edge.getProperDirectionFrom(face));
  }
};