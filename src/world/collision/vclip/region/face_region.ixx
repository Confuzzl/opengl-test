export module world.collision.vclip.region.face_region;

import world.collision.vclip.region.voronoi_region;
// import world.collision.feature.face;
import util.memory;

export class Face;
export class FaceFEPlane;
export class SupportPlane;

export class FaceRegion : public VoronoiRegion<Face> {
  UPtrVector<FaceFEPlane> planes;
  const UPtr<SupportPlane> supportPlane;

public:
  FaceRegion(const Face &parent);
  ~FaceRegion();
};