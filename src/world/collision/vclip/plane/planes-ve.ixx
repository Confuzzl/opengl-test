export module world.collision.vclip.plane.planes:ve;

import world.collision.vclip.plane.feature_plane;
import world.collision.feature.feature;
import world.collision.vclip.region.voronoi_region;

import world.collision.feature.vertex;
import world.collision.feature.edge;
import world.collision.vclip.region.regions;

export template <IsFeature NeighborType, IsVoronoiRegion RegionType>
class VEPlane : public FeaturePlane<NeighborType, RegionType> {};

export class VertexVEPlane : public VEPlane<Edge, VertexRegion> {};
export class EdgeVEPlane : public VEPlane<Vertex, EdgeRegion> {};