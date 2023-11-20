export module world.physics.physics_object;

import world.transform.transformable;
import util.glm;

export class PhysicsObject : public Transformable {
  double mass;
  Vec3 velocity{};
  // double acceleration;
  Vec3 force{};

public:
  PhysicsObject(const double mass);

  void update(const double dt);

  void setForce(const double n, const Vec3 &d);
  void applyForce(const double n, const Vec3 &d);
  void resetForce();

  void setVelocity(const Vec3 &v);
  void addVelocity(const Vec3 &v);
  void resetVelocity();
};