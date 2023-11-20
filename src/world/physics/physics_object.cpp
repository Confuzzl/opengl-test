module world.physics.physics_object;

PhysicsObject::PhysicsObject(const double mass) : mass{mass} {}

void PhysicsObject::update(const double dt) {
  Vec3 acceleration{force / static_cast<float>(mass)};
  velocity += acceleration * static_cast<float>(dt);
  translate(velocity);
}

void PhysicsObject::setForce(const double n, const Vec3 &d) {
  force = glm::normalize(d) * static_cast<float>(n);
}
void PhysicsObject::applyForce(const double n, const Vec3 &d) {
  force += glm::normalize(d) * static_cast<float>(n);
}
void PhysicsObject::resetForce() { force = {}; }