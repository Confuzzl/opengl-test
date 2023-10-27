export module world.collision.vclip.plane.planes:support;

import world.collision.vclip.plane.voronoi_plane;

import world.collision.vclip.region.regions;

export class SupportPlane : public VoronoiPlane<FaceRegion> {};