module world.collision.vclip.plane.planes:support;

SPtr<Face> SupportPlane::getFace() { return face; }

Vec3 SupportPlane::getNormal() { return face->getNormal(); }