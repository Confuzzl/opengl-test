export module world.game_object;

export class Polyhedron;
export class Renderable;

import world.transformable;
import util.memory;

export class GameObject : public Transformable {
  UPtr<Polyhedron> collider;
  UPtr<Renderable> render;

public:
  GameObject(UPtr<Polyhedron> collider, UPtr<Renderable> render);
  GameObject(const GameObject &) = delete;
  GameObject(GameObject &&) = delete;
  ~GameObject();

  const UPtr<Polyhedron> &getCollider();
  const UPtr<Renderable> &getRender();
};