export module world.game_object;

export class Collider;
export class Renderable;

import world.transformable;
import util.memory;

export class GameObject : public Transformable {
  UPtr<Collider> collider;
  UPtr<Renderable> render;

public:
  GameObject(UPtr<Collider> collider, UPtr<Renderable> render);
  GameObject(const GameObject &) = delete;
  GameObject(GameObject &&) = delete;
  ~GameObject();

  const UPtr<Collider> &getCollider();
  const UPtr<Renderable> &getRender();
};