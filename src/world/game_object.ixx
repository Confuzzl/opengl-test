export module world.game_object;

// import world.transform.transformable;
import world.physics.physics_object;
import world.collision.collider;
import rendering.renderable;
import util.memory;
import util.polyhedron;

class GameObject;

export using GObjPtr = UPtr<GameObject>;

export class BaseFactory;

export class GameObject : public PhysicsObject {
  static unsigned int COUNT;

  CollPtr collider;
  RendPtr render;

  friend GObjPtr
  std::make_unique<GameObject /*, CollPtr, RendPtr*/>(CollPtr &&, RendPtr &&);
  GameObject(CollPtr collider, RendPtr render);

  GameObject(const GameObject &) = delete;
  GameObject(GameObject &&) = delete;
  GameObject &operator=(const GameObject &) = delete;
  GameObject &operator=(GameObject &&) = delete;

public:
  const unsigned int ID;

  ~GameObject();

  Collider &getCollider();
  const Collider &getCollider() const;
  Renderable &getRenderable();
  const Renderable &getRenderable() const;

  static GameObject &from(const BaseFactory &factory,
                          const Vec3List &coordinates);
  static GameObject &from(CollPtr collider, RendPtr render);
  // static GameObject &copy(GameObject &object);
};
