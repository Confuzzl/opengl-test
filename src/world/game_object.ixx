export module world.game_object;

// import world.transform.transformable;
import world.physics.physics_object;
import world.collision.collider;
// import rendering.renderable;
import rendering.shaders;
import util.memory;
import util.polyhedron;

import <map>;

export class BaseFactory;

class BaseGameObject;

export struct GameObjectSystem {
  static unsigned int COUNT;
  std::map<unsigned int, UPtr<BaseGameObject>> objects;
};

class BaseGameObject : public PhysicsObject {
public:
  static unsigned int COUNT;
  const unsigned int ID;

  BaseGameObject(CollPtr collider)
      : PhysicsObject(1), ID{COUNT++}, collider{std::move(collider)} {}

  Collider &getCollider();
  const Collider &getCollider() const;

private:
  CollPtr collider;
};

export template <typename VertexFormat, typename... Attributes>
class GameObject : public BaseGameObject {
  static unsigned int COUNT;
  const Shaders::Specialized<VertexFormat, Attributes...> &program;

  // RendPtr render;

  // friend GObjPtr std::make_unique<GameObject, CollPtr, RendPtr>(CollPtr &&,
  //                                                               RendPtr &&);

  GameObject(CollPtr collider, RendPtr render);
  ;

  // static GameObject &from(const BaseFactory &factory,
  //                         const Vec3List &coordinates);
};
