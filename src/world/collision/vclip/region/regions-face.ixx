export module world.collision.vclip.region.regions:face;

import world.collision.feature.face;
import world.collision.vclip.region.voronoi_region;

class FaceFEPlane;
class SupportPlane;

export class FaceRegion : public VoronoiRegion<Face> {
  UPtrVector<FaceFEPlane> planes;
  UPtr<SupportPlane> supportPlane;

public:
  FaceRegion(const Face &parent);
  ~FaceRegion();
};