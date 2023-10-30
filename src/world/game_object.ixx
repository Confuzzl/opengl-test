export module world.game_object;

export class Collider;
export class Renderable;

import world.transformable;
import util.memory;

export class GameObject : public Transformable {
  static unsigned int COUNT;

  UPtr<Collider> collider;
  UPtr<Renderable> render;

  friend UPtr<GameObject>
  std::make_unique<GameObject, UPtr<Collider>, UPtr<Renderable>>(
      UPtr<Collider> &&, UPtr<Renderable> &&);
  GameObject(UPtr<Collider> collider, UPtr<Renderable> render);

public:
  const unsigned int ID;

  GameObject(const GameObject &) = delete;
  GameObject(GameObject &&) = delete;
  ~GameObject();

  GameObject &operator=(const GameObject &) = delete;
  GameObject &operator=(GameObject &&) = delete;

  const UPtr<Collider> &getCollider();
  const UPtr<Renderable> &getRender();

  static UPtr<GameObject> createGameObject(UPtr<Collider> collider,
                                           UPtr<Renderable> render);
  static UPtr<GameObject> &createGameObject2(UPtr<Collider> collider,
                                             UPtr<Renderable> render);
};