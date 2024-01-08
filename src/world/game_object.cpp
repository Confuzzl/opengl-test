module world.game_object;

std::map<unsigned int, GameObject::Base *> GameObject::System::objects{};

unsigned int GameObject::Base::COUNT = 0;

GameObject::Base::Base(CollPtr collider, RendPtr render)
    : PhysicsObject(1), ID{COUNT++}, collider{std::move(collider)},
      render{std::move(render)} {
  System::objects.emplace(ID, this);
}
GameObject::Base::~Base() { System::objects.erase(ID); }

Collider &GameObject::Base::getCollider() { return *collider; }
const Collider &GameObject::Base::getCollider() const { return *collider; }
