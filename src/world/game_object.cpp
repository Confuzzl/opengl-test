module world.game_object;

std::map<unsigned int, GameObject::Base *> GameObject::System::objects{};

unsigned int GameObject::Base::COUNT = 0;

GameObject::Base::Base(CollPtr collider, UPtr<Renderable::Polyhedron> render)
    : PhysicsObject(1), ID{COUNT++}, collider{std::move(collider)},
      render{std::move(render)} {
  System::objects.emplace(ID, this);
}
Collider &GameObject::Base::getCollider() { return *collider; }
const Collider &GameObject::Base::getCollider() const { return *collider; }
