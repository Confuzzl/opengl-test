module world.game_object;

// std::map<unsigned int, UPtr<Base>> GameObject::System::objects{};

unsigned int GameObject::Base::COUNT = 0;

GameObject::Base::Base(CollPtr collider, UPtr<Renderable::Base> render)
    : PhysicsObject(1), ID{COUNT++}, collider{std::move(collider)},
      render{std::move(render)} {}

Collider &GameObject::Base::getCollider() { return *collider; }
const Collider &GameObject::Base::getCollider() const { return *collider; }