export module world.game_object;

import world.transformable;
import world.collision.collider;
import world.render.renderable;
import util.memory;

class GameObject;

export using GObjPtr = UPtr<GameObject>;

export class GameObject : public Transformable {
  static unsigned int COUNT;

  CollPtr collider;
  RendPtr render;

  friend GObjPtr std::make_unique<GameObject, CollPtr, RendPtr>(CollPtr &&,
                                                                RendPtr &&);
  GameObject(CollPtr collider, RendPtr render);

  GameObject(const GameObject &) = delete;
  GameObject(GameObject &&) = delete;
  GameObject &operator=(const GameObject &) = delete;
  GameObject &operator=(GameObject &&) = delete;

public:
  const unsigned int ID;

  ~GameObject();

  const CollPtr &getCollider();
  const RendPtr &getRender();

  Collider &getCollider2();
  Renderable &getRenderable2();

  static GObjPtr &createGameObject2(CollPtr collider, RendPtr render);
  static GameObject &createGameObject3(CollPtr collider, RendPtr render);
};
