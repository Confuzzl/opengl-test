export module world.base_polyhedron;

import world.transformable;
import util.polyhedron;

export class BasePolyhedron : public Transformable {
protected:
  const Vec3List coordinates;

  BasePolyhedron(const Vec3List &coordinates);
};