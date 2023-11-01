export module world.game_object;

export class Collider;
export class Renderable;
export class GameObject;

import world.transformable;
import util.memory;
import util.game;

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