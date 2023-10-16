module world.game_object;

import app.app;
import world.collision.polyhedron;
import world.render.renderable;
import util.debug;

unsigned int GameObject::COUNT = 0;

GameObject::GameObject(UPtr<Collider> collider, UPtr<Renderable> render)
    : collider{std::move(collider)}, render{std::move(render)}, ID{COUNT++} {
  app.scene.gameObjects.insert(this);
}
GameObject::~GameObject() {
  app.scene.gameObjects.erase(this);
  std::cout << std::format("gameobject {} destroyed\n", ID);
}

const UPtr<Collider> &GameObject::getCollider() { return collider; }
const UPtr<Renderable> &GameObject::getRender() { return render; }