export module world.entity.player;

import world.transform.transformable;
import util.memory;

export class Camera;

export class Player : public Transformable {
  UPtr<Camera> camera{};

public:
  Player();
  ~Player();

  Camera &getCamera();
};