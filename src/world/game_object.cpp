#include "game_object.h"

const UPtr<Polyhedron> &GameObject::getCollider() { return collider; }
const UPtr<Renderable> &GameObject::getRender() { return render; }