#include "game_object.h"
#include "collision/polyhedron.h"
#include "render/renderable.h"

GameObject::GameObject(UPtr<Polyhedron> &&collider, UPtr<Renderable> &&render)
    : collider{std::move(collider)}, render{std::move(render)} {}

const UPtr<Polyhedron> &GameObject::getCollider() { return collider; }
const UPtr<Renderable> &GameObject::getRender() { return render; }