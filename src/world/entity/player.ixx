export module world.entity.player;

// import world.transform.transformable;
import world.physics.physics_object;
import util.glm;
import util.memory;

export class Camera;

export class Player : public PhysicsObject {
  UPtr<Camera> camera;
  Vec3 movementForces{};

public:
  float speed;

  Player();
  ~Player();

  Camera &getCamera();
};