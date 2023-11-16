export module world.entity.player;

import world.transform.transformable;
import util.memory;

export class Camera;

export class Player : public Transformable {
public:
  UPtr<Camera> camera{std::make_unique<Camera>(45.0f)};

  float speed = 2;

  Player();
  ~Player();

  Camera &getCamera();
};