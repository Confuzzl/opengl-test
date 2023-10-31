module;

#include <utility>

module world.game_object;

import app.app;
import world.collision.collider;
import world.render.renderable;
import util.debug;

unsigned int GameObject::COUNT = 0;

GameObject::GameObject(UPtr<Collider> collider, UPtr<Renderable> render)
    : collider{std::move(collider)}, render{std::move(render)}, ID{COUNT++} {
  appScene.gameObjects.insert(this);
}
GameObject::~GameObject() {
  appScene.gameObjects.erase(this);
  std::cout << std::format("gameobject {} destroyed\n", ID);
}

const UPtr<Collider> &GameObject::getCollider() { return collider; }
const UPtr<Renderable> &GameObject::getRender() { return render; }

UPtr<GameObject> GameObject::createGameObject(UPtr<Collider> collider,
                                              UPtr<Renderable> render) {
  return std::make_unique<GameObject>(std::forward<UPtr<Collider>>(collider),
                                      std::forward<UPtr<Renderable>>(render));
}
UPtr<GameObject> &GameObject::createGameObject2(UPtr<Collider> collider,
                                                UPtr<Renderable> render) {
  UPtr<GameObject> ptr{
      std::make_unique<GameObject>(std::forward<UPtr<Collider>>(collider),
                                   std::forward<UPtr<Renderable>>(render))};
  unsigned short ID = ptr->ID;
  appScene.objectMap.emplace(std::make_pair(ID, std::move(ptr)));
  return appScene.objectMap.at(ID);
}