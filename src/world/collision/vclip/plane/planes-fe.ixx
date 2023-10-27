export module world.collision.vclip.plane.planes:fe;

import world.collision.vclip.plane.feature_plane;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;

import world.collision.feature.edge;
import world.collision.feature.face;
import world.collision.vclip.region.regions;

export template <IsFeature NeighborType, IsVoronoiRegion RegionType>
class FEPlane : public FeaturePlane<NeighborType, RegionType> {};

export class EdgeFEPlane : public FEPlane<Face, EdgeRegion> {};
export class FaceFEPlane : public FEPlane<Edge, FaceRegion> {};