export module world.game_object;

// import world.transform.transformable;
import world.physics.physics_object;
import world.collision.collider;
// import rendering.renderable;
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
};

// template <typename VertexFormat, typename... Attributes>
class Specialized : public Base {
  static unsigned int COUNT;
  // const Shaders::Specialized<VertexFormat, Attributes...> &program;
  Shaders::Base &program;

  // RendPtr render;

  // friend GObjPtr std::make_unique<GameObject, CollPtr, RendPtr>(CollPtr &&,
  //                                                               RendPtr &&);

  Specialized(CollPtr collider);

  // static GameObject &from(const BaseFactory &factory,
  //                         const Vec3List &coordinates);
};

// template <> Specialized from<Shaders::_2D::FontProgram>() {}
// template <> Specialized from<Shaders::_3D::ColProgram>() {}
// template <> Specialized from<Shaders::_3D::TexProgram>() {}
// template <> Specialized from<Shaders::_3D::ColTexProgram>() {}
} // namespace GameObject
