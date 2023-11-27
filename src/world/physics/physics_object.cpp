module world.physics.physics_object;

PhysicsObject::PhysicsObject(const double mass) : mass{mass} {}

void PhysicsObject::update(const double dt) {
  Vec3 acceleration{force / mass};
  addVelocity(acceleration);
  translate(velocity * static_cast<float>(dt));
}

void PhysicsObject::setForce(const double n, const Vec3 &d) {
  force = glm::normalize(d) * static_cast<float>(n);
}
void PhysicsObject::applyForce(const double n, const Vec3 &d) {
  force += glm::normalize(d) * static_cast<float>(n);
}
void PhysicsObject::resetForce() { force = {}; }

void PhysicsObject::setVelocity(const Vec3 &v) { velocity = v; }
void PhysicsObject::addVelocity(const Vec3 &v) { velocity += v; }
void PhysicsObject::resetVelocity() { velocity = {}; }