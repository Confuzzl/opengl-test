module world.game_object;

import world.collision.polyhedron;
import world.render.renderable;

GameObject::GameObject(UPtr<Collider> collider, UPtr<Renderable> render)
    : collider{std::move(collider)}, render{std::move(render)} {}
GameObject::~GameObject() = default;

const UPtr<Collider> &GameObject::getCollider() { return collider; }
const UPtr<Renderable> &GameObject::getRender() { return render; }