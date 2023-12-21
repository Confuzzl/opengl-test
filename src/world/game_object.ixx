export module world.game_object;

// import world.transform.transformable;
import world.physics.physics_object;
import world.collision.collider;
// import rendering.renderable;
import rendering.base;
import rendering.shaders;
import rendering.shaders.global;

import util.memory;
import util.polyhedron;

import <map>;

// export class BaseFactory;

export namespace GameObject {
class Base;

struct System {
  static unsigned int COUNT;
  std::map<unsigned int, UPtr<Base>> objects;
};

class Base : public PhysicsObject {
public:
  static unsigned int COUNT;
  const unsigned int ID;

  Base(CollPtr collider)
      : PhysicsObject(1), ID{COUNT++}, collider{std::move(collider)} {};

  Collider &getCollider() { return *collider; };
  const Collider &getCollider() const { return *collider; };

private:
  CollPtr collider;
  UPtr<Renderable::Base> render;
};
} // namespace GameObject
