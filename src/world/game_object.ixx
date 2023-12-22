export module world.game_object;

import world.physics.physics_object;
import world.collision.collider;
import rendering.base;
import rendering.shaders;
import rendering.shaders.global;

import util.memory;
import util.polyhedron;

import <map>;

export namespace GameObject {
class Base;

struct System {
  static std::map<unsigned int, UPtr<Base>> objects;
};

class Base : public PhysicsObject {
public:
  static unsigned int COUNT;
  const unsigned int ID;

  Base(CollPtr collider, UPtr<Renderable::Base> render);

  Collider &getCollider();
  const Collider &getCollider() const;

private:
  CollPtr collider;
  UPtr<Renderable::Base> render;
};
} // namespace GameObject
