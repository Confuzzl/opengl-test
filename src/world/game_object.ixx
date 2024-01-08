export module world.game_object;

import world.physics.physics_object;
import collision.collider;
import rendering.base;
import rendering.shaders;
import rendering.shaders.global;

import util.memory;
import util.polyhedron;

import <map>;

import factory.base_factory;
import collision.factory;
import rendering.factory;
import rendering.vertex_formats.types;

export namespace GameObject {
class Base;

struct System {
  static std::map<unsigned int, Base *> objects;
};

class Base : public PhysicsObject {
public:
  static unsigned int COUNT;
  const unsigned int ID;

  Base(CollPtr collider, RendPtr render);
  ~Base();

  Collider &getCollider();
  const Collider &getCollider() const;

private:
  CollPtr collider;
  RendPtr render;
};

template <VertexFormats::writable VertexFormat>
Base &from(const Factory::Base &factory, const Vec3List &coordinates) {
  UPtr<Base> object = std::make_unique<Base>(
      Factory::createCollidable(factory, coordinates),
      Factory::createRenderable<VertexFormat>(factory, coordinates));
  return *object;
}
} // namespace GameObject
