module;

#include <utility>

module world.game_object;

import app.app;
import util.debug;

unsigned int GameObject::COUNT = 0;

GameObject::GameObject(CollPtr collider, RendPtr render)
    : collider{std::move(collider)}, render{std::move(render)}, ID{COUNT++} {
  appScene.gameObjects.insert(this);
}
GameObject::~GameObject() {
  appScene.gameObjects.erase(this);
  std::cout << std::format("gameobject {} destroyed\n", ID);
}

const CollPtr &GameObject::getCollider() { return collider; }
const RendPtr &GameObject::getRender() { return render; }

GObjPtr GameObject::createGameObject(CollPtr collider, RendPtr render) {
  return std::make_unique<GameObject>(std::forward<CollPtr>(collider),
                                      std::forward<RendPtr>(render));
}
GObjPtr &GameObject::createGameObject2(CollPtr collider, RendPtr render) {
  GObjPtr ptr{std::make_unique<GameObject>(std::forward<CollPtr>(collider),
                                           std::forward<RendPtr>(render))};
  unsigned short ID = ptr->ID;
  appScene.objectMap.emplace(std::make_pair(ID, std::move(ptr)));
  return appScene.objectMap.at(ID);
}