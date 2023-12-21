module world.game_object;

GameObject::Base::Base(CollPtr collider, UPtr<Renderable::Base> render)
    : PhysicsObject(1), ID{COUNT++}, collider{std::move(collider)},
      render{std::move(render)} {}

Collider &GameObject::Base::getCollider() { return *collider; }
const Collider &GameObject::Base::getCollider() const { return *collider; }