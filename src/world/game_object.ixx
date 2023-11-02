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

public:
  const unsigned int ID;

  GameObject(const GameObject &) = delete;
  GameObject(GameObject &&) = delete;
  ~GameObject();

  GameObject &operator=(const GameObject &) = delete;
  GameObject &operator=(GameObject &&) = delete;

  const CollPtr &getCollider();
  const RendPtr &getRender();

  static GObjPtr createGameObject(CollPtr collider, RendPtr render);
  static GObjPtr &createGameObject2(CollPtr collider, RendPtr render);
};
