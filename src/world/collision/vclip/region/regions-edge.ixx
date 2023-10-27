export module world.collision.vclip.region.regions:edge;

import world.collision.feature.edge;
import world.collision.vclip.region.voronoi_region;

export class EdgeRegion : public VoronoiRegion<Edge> {};